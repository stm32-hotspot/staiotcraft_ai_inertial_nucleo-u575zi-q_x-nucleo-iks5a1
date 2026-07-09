/**
 ******************************************************************************
 * File Name          : app_ai_inertial.c
 * Description        : This file provides code for the configuration
 *                      of the STMicroelectronics.STAIOTCRAFT.1.2.0 instances.
 ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
 ******************************************************************************
 */

/**
  * @mainpage
  * @section Introduction
  * STAIOTCRAFT  is a function pack for STM32Cube.
  * The key features of STAIOTCRAFT are:
  *   - PnPL library for the communication language via commands and telemetries
  *   - X-CUBE-MEMS1 for the sensing part through the inertial sensors and processing with embedded MLC
  *   - Sample applications for each one of the targeted boards.
  *
  * This software provides a porting of the STAIOTCRAFT for the STM32 platform, in the STM32Cube and STM32CubeMX
  * software environment.
  * The package also includes three sample applications, one for each board that the developer can use to start
  * experimenting with the code.
  *
  */

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "app_ai_inertial.h"
#include "main.h"
#include <stdio.h>
#include <stdint.h>
#include <ctype.h>

/* Definitions ---------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Sensor. */
volatile uint8_t mems_event_detected;                               /* Set to "1" upon interrupt from FIFO. */
volatile uint8_t ism6hg256x_mlc_event_detected;                     /* Set to "1" upon interrupt from ISM6HG256X_MLC. */

/* Processing variables. */
char command_buffer_static[COMMAND_BUFFER_SIZE];                    /* Buffer containing the command received from USB. */
char *command_buffer_ptr;                                           /* Pointer to the beginning of the command buffer. */
char *command_buffer_write_ptr;                                     /* Pointer to the current write position in the command buffer. */
char ism6hg256x_mlc_model_filename[50];                             /* Pointer to the ISM6HG256X_MLC Model Filename */
uint32_t command_buffer_size;                                       /* Command buffer size. */
volatile bool command_received;                                     /* Flag when command is received from USB. */
char buffer_to_write[PRINTED_BUFFER_SIZE];                          /* Buffer to be printed (it will contain the telemetries). */
ai_type_t default_ai;                                               /* Selected use-case. */
volatile int ism6hg256x_mlc_inference;                              /* Flag when the application ISM6HG256X_MLC is started. */
volatile int get_identity;                                          /* Flag when board_id and fw_id are requested. */
volatile int get_status;                                            /* Flag when properties are requested. */

/* Time measurement. */
int32_t start_time;
int32_t stop_time;
int32_t time;

/* Timer settings. */
extern TIM_HandleTypeDef htim1;
volatile int tim_interrupt = 0;

/* ISM6HG256X_MLC configuration. */
struct mems_conf_op* current_ism6hg256x_mlc_configuration = (struct mems_conf_op*) ism6hg256x_mlc_conf_0;                     /* ISM6HG256X_MLC configuration in use. */
uint32_t current_ism6hg256x_mlc_configuration_size = sizeof(ism6hg256x_mlc_conf_0)/sizeof(const struct mems_conf_op);         /* ISM6HG256X_MLC configuration size. */

/* Functions -----------------------------------------------------------------*/
static void SystemPower_Config(void);

/*
 * Initialization (sensor, pre-processing pipeline, AI-processing pipeline).
 */
int32_t MX_AI_INERTIAL_Init(void) {
	int32_t ret = 0;

	/* Configure the System Power. */
	SystemPower_Config();

	/* Initialization of the hardware timer. */
	HAL_TIM_Base_Start_IT(&htim1);

	/* Reset command and print buffers before UART reception starts. */
	memset((char *) command_buffer_static, 0, COMMAND_BUFFER_SIZE);
	memset((char *) buffer_to_write, 0, PRINTED_BUFFER_SIZE);
	command_buffer_ptr = &command_buffer_static[0];
	command_buffer_write_ptr = &command_buffer_static[0];
	command_buffer_size = 0;
	command_received = false;

	/* Initializing ST-LINK VCP transport. */
	STLINK_Transport_Init();

	/* Small startup delay so the host terminal can attach to the ST-LINK VCP. */
	HAL_Delay(500);

	/* Use case default selection (ISM6HG256X_MLC). */
	default_ai = ISM6HG256X_MLC;

	/* Ensure MEMS rail is enabled before probing ISM6HG256X. */
	HAL_GPIO_WritePin(IKS5A1_MEMS_PWR_EN_GPIO_Port, IKS5A1_MEMS_PWR_EN_Pin, GPIO_PIN_SET);
	HAL_Delay(10);

	/* Setting Firmware ID */
	PnPLSetFWID(default_ai == ISM6HG256X_MLC ? 0x0F : 0xFF); /* 0x0F for ISM6HG256X_MLC, 0xFF for unknown */

	/* Initializing sensor. */
	ret = sensor_init();
	if (ret != BSP_ERROR_NONE) {
		PRINT("ERROR: sensor_init failed (%ld)\\r\\n", (long)ret);
		return ret;
	}
	
	/* Initializing PnPL. */
	pnpl_init();

	ism6hg256x_mlc_inference = 0;
	get_identity = 0;
	get_status = 0;

	/* Printing commands format. */
	PRINT("COMMANDS\r\n"
			"ISM6HG256X_MLC: \r\n"
			"Start: {\"ism6hg256x_mlc*start_inference\":\"\"}\r\n"
			"Stop: {\"ism6hg256x_mlc*stop_inference\":\"\"}\r\n"
			"{\"ism6hg256x_mlc*load_model\":{\"arguments\":{\"filename\": \"string_value\", \"size\":<model_file_size_in_bytes>,\"content\":\"<model_file_content>\"}}}\r\n"
			"SET DFU MODE: \r\n"
			"{\"controller*set_dfu_mode\":\"\"}\r\n"
			"SWAP BANK: \r\n"
			"{\"controller*switch_bank\":\"\"}\r\n"
			"Terminate each command with CR+LF characters, you can set them within the client connected to the board.\r\n\r\n");

	/* Copy the names of the original model files */
	strcpy(ism6hg256x_mlc_model_filename, "asset_tracking_ism6hg256x_mlc_model");

	/* Load the default model files. */
	if (default_ai == ISM6HG256X_MLC) {
		/* Acquiring the ISM6HG256X_MLC configuration and load the registers. */
		load_ism6hg256x_mlc_configuration((struct mems_conf_op*) ism6hg256x_mlc_conf_0, current_ism6hg256x_mlc_configuration_size);
		reset_mlc_interrupt_latched();
	}

	/* Start sending the telemetries. */
	if (ism6hg256x_mlc_inference == 0 && default_ai == ISM6HG256X_MLC) {
		/* Starting ISM6HG256X_MLC inference. */
		ism6hg256x_mlc_inference = 1;
	}

	return BSP_ERROR_NONE;
}

/*
 * Processing data (reading commands and sending telemetries via ST-LINK VCP).
 */
int32_t MX_AI_INERTIAL_Process(void) {

	/* Executing command. */
	if (command_received) {                                                     /* Check if command is received. */
		command_received = false;
		*command_buffer_write_ptr = '\0';
		pnpl_process(command_buffer_ptr);                                       /* Serve the command received. */
		/* Resetting command buffer. */
		command_buffer_size = command_buffer_write_ptr - command_buffer_ptr;    /* Size of the last command received. */
		memset((char *) command_buffer_static, 0, command_buffer_size + 1U);    /* Resetting the command buffer including terminator. */
		command_buffer_ptr = &command_buffer_static[0];
		command_buffer_write_ptr = &command_buffer_static[0];                   /* Move the write pointer to the initial position of the command buffer. */
		command_buffer_size = 0;
	}

	/* Sending ISM6HG256X_MLC telemetries. */
	if (ism6hg256x_mlc_inference == 1) {
		send_telemetries_ism6hg256x_mlc();
	}

	if(tim_interrupt){
		tim_interrupt = 0;
	}

	return BSP_ERROR_NONE;
}

/**
 * @brief Power Configuration
 * @retval None
 */
static void SystemPower_Config(void)
{

	HAL_PWREx_EnableVddIO2();
	/*
	 * Disable the internal Pull-Up in Dead Battery pins of UCPD peripheral
	 */
	HAL_PWREx_DisableUCPDDeadBattery();
	/* USER CODE BEGIN PWR */
	/* USER CODE END PWR */
}

/*
 * Callback to serve the interrupt from the FIFO of the sensor.
 */
void HAL_GPIO_EXTI_Rising_Callback(uint16_t GPIO_Pin)
{
	if(GPIO_Pin == GPIO_PIN_11){
		mems_event_detected = 1;
	} else if(GPIO_Pin == GPIO_PIN_4){
		ism6hg256x_mlc_event_detected = 1;
	}
}

/*
 * PnPL initialization function.
 */
void pnpl_init(){

	PnPL_Components_Alloc();
	PnPL_Components_Init();
}

/*
 * PnPL parsing function.
 */
void pnpl_process(char *command) {

	/* Parse/Serialize PnPL messages */
	PnPLCommand_t PnPLCommand;
	char *SerializedJSON;
	uint32_t size;

	/* Parsing PnPL commands. */
	if(PnPLParseCommand(command, &PnPLCommand) == PNPL_NO_ERROR_CODE){
	   if(PnPLCommand.comm_type == PNPL_CMD_GET || PnPLCommand.comm_type == PNPL_CMD_SYSTEM_CONFIG || PnPLCommand.comm_type == PNPL_CMD_SYSTEM_INFO|| PnPLCommand.comm_type == PNPL_CMD_UPDATE_DEVICE){
			PnPLSerializeResponse(&PnPLCommand, &SerializedJSON, &size,0);
			identify_get_cmd(&PnPLCommand,&SerializedJSON);
			if(get_status){
				send_status(&SerializedJSON);
			}else if(get_identity){
				send_identity(&SerializedJSON);
			}
			json_free_serialized_string(SerializedJSON);
	    }
	}
}

/*
 * Sending ISM6HG256X_MLC register outputs.
 */
int32_t send_telemetries_ism6hg256x_mlc() {
	uint8_t status = 0;
	uint8_t ism6hg256x_mlc_output_reg[8] = {0};
	static uint8_t result = 0; // Keep previous value

	/* Creating PnPL telemetry message. */
	uint32_t size;
	char *telemetry = NULL;

	if(ism6hg256x_mlc_event_detected || tim_interrupt){
		ism6hg256x_mlc_event_detected = 0;

		/* Reading ISM6HG256X_MLC output. */
		read_ism6hg256x_mlc_output(ism6hg256x_mlc_output_reg);

		/* Reading ISM6HG256X_MLC status register. */
		(void)CUSTOM_MOTION_SENSOR_Read_Register(SENSOR_0, SENSOR_0_MLC_STATUS_MAINPAGE, &status);

		/* Determining which output is active based on status register. */
		switch (status & 0x0F) {
		case 0x01:
			result = ism6hg256x_mlc_output_reg[0];
			break;
		case 0x02:
			result = ism6hg256x_mlc_output_reg[1];
			break;
		case 0x04:
			result = ism6hg256x_mlc_output_reg[2];
			break;
		case 0x08:
			result = ism6hg256x_mlc_output_reg[3];
			break;
		default:
			// Keep previous value
			break;
		}

		// Create PnPL telemetry message for each active output
		ism6hg256x_mlc_create_telemetry((int)result, &telemetry, &size);

		/* Checking null pointer exception. */
		if(telemetry){
			/* Appending the new line character to the telemetry message. */
			const char *ch = "\r\n";
			size_t new_size = size + strlen(ch) + 1; /* +1 for the null terminator */
			telemetry = (char *)realloc(telemetry, new_size);
			if (telemetry){
				strcat(telemetry, ch);
				/* Printing telemetry message if ISM6HG256X_MLC output value is changed. */
				PRINT("%s", telemetry);
				/* Clearing telemetry message. */
				json_free_serialized_string(telemetry);
			}
		}
	}

	return BSP_ERROR_NONE;
}

/*
 * Programming the registers inside the ISM6HG256X_MLC.
 */
void load_ism6hg256x_mlc_configuration(struct mems_conf_op* ism6hg256x_mlc_conf_0, uint32_t model_number_of_lines) {
	/* Iterating over each line in the configuration until NULL is reached. */
	for (uint32_t i = 0; i < model_number_of_lines; i++) {
		CUSTOM_MOTION_SENSOR_Write_Register(SENSOR_0, ism6hg256x_mlc_conf_0[i].address, ism6hg256x_mlc_conf_0[i].data);
	}
}

/*
 * Reading the content of the ISM6HG256X_MLC output registers.
 */
void read_ism6hg256x_mlc_output(uint8_t* ism6hg256x_mlc_output_reg){

	(void)CUSTOM_MOTION_SENSOR_Write_Register(SENSOR_0, SENSOR_0_FUNC_CFG_ACCESS, 0x80);
	(void)CUSTOM_MOTION_SENSOR_Read_Register(SENSOR_0, SENSOR_0_MLC1_SRC, &ism6hg256x_mlc_output_reg[0]);
	(void)CUSTOM_MOTION_SENSOR_Read_Register(SENSOR_0, SENSOR_0_MLC2_SRC, &ism6hg256x_mlc_output_reg[1]);
	(void)CUSTOM_MOTION_SENSOR_Read_Register(SENSOR_0, SENSOR_0_MLC3_SRC, &ism6hg256x_mlc_output_reg[2]);
	(void)CUSTOM_MOTION_SENSOR_Read_Register(SENSOR_0, SENSOR_0_MLC4_SRC, &ism6hg256x_mlc_output_reg[3]);
	(void)CUSTOM_MOTION_SENSOR_Write_Register(SENSOR_0, SENSOR_0_FUNC_CFG_ACCESS, 0x00);
}


/*
 * Initialization (sensor).
 */
int32_t sensor_init() {
	int32_t ret = 0;

	CHECK_BSP_FUNCTION(CUSTOM_MOTION_SENSOR_Init(SENSOR_0, MOTION_ACCELERO | MOTION_GYRO));                         /* Sensor initialization */

	return BSP_ERROR_NONE;
}

/*
 * Extracting the number of lines from the model file.
 */
uint32_t get_model_number_of_lines(int32_t size, const char *content) {
	uint32_t model_number_of_lines = 0;
	uint32_t i;

	for (i = 0; i < size-model_number_of_lines; i++) {
		if(content[i]=='\n'){
			model_number_of_lines++;
		}
	}

	return model_number_of_lines;
}

/*
 * Filling ISM6HG256X_MLC configuration structure from JSON file.
 */
void fill_ism6hg256x_mlc_configuration(const char *config_start, const char *config_end, struct mems_conf_op* ism6hg256x_mlc_conf_0) {
	const char *config_ptr = config_start;
	size_t i = 0;

	while (config_ptr < config_end) {
		const char *type_start = strstr(config_ptr, "\"type\": \"");
		if (!type_start) {
			break; /* No more configurations */
		}
		type_start += strlen("\"type\": \"");

		const char *type_end = strchr(type_start, '"');
		if (!type_end) {
			break; /* Malformed JSON */
		}

		if (strncmp(type_start, "write", type_end - type_start) == 0) {
			const char *address_start = strstr(type_end, "\"address\": \"");
			if (!address_start) {
				break; /* Malformed JSON */
			}
			address_start += strlen("\"address\": \"");

			const char *address_end = strchr(address_start, '"');
			if (!address_end) {
				break; /* Malformed JSON */
			}

			const char *data_start = strstr(address_end, "\"data\": \"");
			if (!data_start) {
				break; /* Malformed JSON */
			}
			data_start += strlen("\"data\": \"");

			const char *data_end = strchr(data_start, '"');
			if (!data_end) {
				break; /* Malformed JSON */
			}

			ism6hg256x_mlc_conf_0[i].address = (uint8_t) strtol(address_start, NULL, 16);
			ism6hg256x_mlc_conf_0[i].data = (uint8_t) strtol(data_start, NULL, 16);
			i++;
		}

		config_ptr = strchr(type_end, '}');
		if (!config_ptr) {
			break; /* Malformed JSON */
		}
		config_ptr++;
	}
}


/*
 * Sending Board-ID and Firmware-ID.
 */
void send_identity(char **serializedJSON) {
    get_identity = 0;

    /* Appending the new line character to the identity message. */
    const char *ch = "\r\n";
    size_t identity_len = strlen(*serializedJSON);
    size_t ch_len = strlen(ch);
    size_t new_size = identity_len + ch_len + 1; /* +1 for the null terminator */

    if (new_size >= identity_len) {
        strcat(*serializedJSON, ch);
        PRINT("%s", *serializedJSON);
    } else {
        /* Handle buffer overflow */
    	PRINT("%s", "Buffer overflow: identity string is too long\n");
    }
}

/*
 * Sending the Properties Status.
 */
void send_status(char **serializedJSON) {
    get_status = 0;

    /* Appending the new line character to the status message. */
    const char *ch = "\r\n";
    size_t status_len = strlen(*serializedJSON);
    size_t ch_len = strlen(ch);
    size_t new_size = status_len + ch_len + 1; /* +1 for the null terminator */

    if (new_size >= status_len) {
        strcat(*serializedJSON, ch);
        PRINT("%s", *serializedJSON);
    } else {
        /* Handle buffer overflow */
    	PRINT("%s", "Buffer overflow: status string is too long\n");
    }
}

/*
 * Identify the type of get command.
 */
void identify_get_cmd(PnPLCommand_t *command, char **serializedJSON){

	if(command->comm_type == PNPL_CMD_SYSTEM_INFO){
		get_identity = 1;
	}
	else if(command->comm_type == PNPL_CMD_GET){
		get_status = 1;
	}
}

/*
 * Periodic interrupt for MLC use-cases.
 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == TIM1) {
        tim_interrupt = 1;
    }
}

/*
 * Set the DFU Mode.
 */
void jump_to_bootloader( void )
{
	static const uint32_t system_memory_base = 0x0BF90000UL;
	typedef void (*pFunction)(void);
	pFunction JumpToBootloader;
	uint32_t JumpAddress;

	/*
	 * STM32U5 blocks system-memory bootloader communication interfaces when TZEN=1.
	 * In this configuration, DFU/USART/SPI/I2C/CAN bootloader entry is not usable.
	 */
	if ((FLASH->OPTR & FLASH_OPTR_TZEN) == FLASH_OPTR_TZEN) {
		PRINT("ERROR: TZEN=1 blocks system-memory bootloader interfaces. Use SWD/JTAG for provisioning.\r\n");
		return;
	}

	/* Stop application timing sources before changing execution context. */
	HAL_TIM_Base_Stop_IT(&htim1);
	HAL_NVIC_DisableIRQ(TIM1_UP_IRQn);

	/* Disable ICACHE before jumping to ROM. */
	HAL_ICACHE_DeInit();

	JumpAddress = *(__IO uint32_t *)(system_memory_base + 4U);
	if ((JumpAddress == 0x00000000UL) || (JumpAddress == 0xFFFFFFFFUL)) {
		PRINT("ERROR: invalid system-memory bootloader vector.\r\n");
		return;
	}

	__disable_irq();
	JumpToBootloader = (pFunction)JumpAddress;

	/* Initialize bootloader Stack Pointer and branch to its reset handler. */
	__set_MSP(*(__IO uint32_t *)system_memory_base);
	JumpToBootloader();

}

/* Function to convert a single hex character to its integer value */
uint8_t hex_char_to_int(char character) {
	if (isdigit(character)) {
		return character - '0';
	} else if (isxdigit(character)) {
		return tolower(character) - 'a' + 10;
	}
	return 0; /* Handle invalid input gracefully */
}

/* Function to convert a two-character hex string to an integer */
uint8_t hex_to_int(const char *hex) {
	return (hex_char_to_int(hex[0]) << 4) | hex_char_to_int(hex[1]);
}

/* Function to program the MLC interrupt in latched mode (EMB_FUNC_LIR=1) as per datasheet */
void reset_mlc_interrupt_latched(){
	(void)CUSTOM_MOTION_SENSOR_Write_Register(SENSOR_0, SENSOR_0_FUNC_CFG_ACCESS, 0x80);
	(void)CUSTOM_MOTION_SENSOR_Write_Register(SENSOR_0, SENSOR_0_PAGE_RW , 0x80);
	(void)CUSTOM_MOTION_SENSOR_Write_Register(SENSOR_0, SENSOR_0_FUNC_CFG_ACCESS, 0x00);
}

void ToggleFlashBank(void)
{
	FLASH_OBProgramInitTypeDef    OBInit;
	/* Set BFB2 bit to enable boot from Flash Bank2 */
	/* Allow Access to Flash control registers and user Flash */
	HAL_FLASH_Unlock();

	/* Allow Access to option bytes sector */
	HAL_FLASH_OB_Unlock();

	/* Get the Dual boot configuration status */
	HAL_FLASHEx_OBGetConfig(&OBInit);

	/* Enable/Disable dual boot feature */
	OBInit.OptionType = OPTIONBYTE_USER;
	OBInit.USERType   = OB_USER_SWAP_BANK;

	if (((OBInit.USERConfig) & (FLASH_OPTR_SWAP_BANK)) == FLASH_OPTR_SWAP_BANK)
	{
		OBInit.USERConfig &= ~FLASH_OPTR_SWAP_BANK;
	}
	else
	{
		OBInit.USERConfig = FLASH_OPTR_SWAP_BANK;
	}

	/* SYS_DEBUGF(SYS_DBG_LEVEL_WARNING, ("HW: Switching Bank\r\n")); */
	if(HAL_FLASHEx_OBProgram (&OBInit) != HAL_OK)
	{
		/*
	    Error occurred while setting option bytes configuration.
	    User can add here some code to deal with this error.
	    To know the code error, user can call function 'HAL_FLASH_GetError()'
		 */
		while(1);
	}

	/* Start the Option Bytes programming process */
	if (HAL_FLASH_OB_Launch() != HAL_OK) {
		/*
	    Error occurred while reloading option bytes configuration.
	    User can add here some code to deal with this error.
	    To know the code error, user can call function 'HAL_FLASH_GetError()'
		 */
		while(1);
	}
	HAL_FLASH_OB_Lock();
	HAL_FLASH_Lock();
}

