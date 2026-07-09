/**
  ******************************************************************************
  * File Name          : app_ai_inertial.h
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __APP_AI_INERTIAL_H
#define __APP_AI_INERTIAL_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "custom_motion_sensors_ex.h"
#include "arm_math.h"
#include "MEMS_integration.h"
#include "custom_bus.h"
#include "App_model.h"
#include "stlink_transport.h"
#include "ism6hg256x_mlc.h"

#include "PnPL_init.h"
#include "Ism6hg256x_Mlc_PnPL.h"
#include "Controller_PnPL.h"
#include "PnPLCompManager.h"

/* Exported defines ----------------------------------------------------------*/
#define     SENSOR_INTERNAL_FREQ  ISM6HG256X_INTERNAL_FREQ
#define     SENSOR_0       CUSTOM_ISM6HG256X_0                        /* Sensor used */
#define     SENSOR_0_FUNC_CFG_ACCESS    ISM6HG256X_FUNC_CFG_ACCESS
#define     SENSOR_0_PAGE_RW                 ISM6HG256X_PAGE_RW
#define     SENSOR_0_MLC1_SRC     ISM6HG256X_MLC1_SRC
#define     SENSOR_0_MLC2_SRC     ISM6HG256X_MLC2_SRC
#define     SENSOR_0_MLC3_SRC     ISM6HG256X_MLC3_SRC
#define     SENSOR_0_MLC4_SRC     ISM6HG256X_MLC4_SRC
#define     SENSOR_0_MLC_STATUS_MAINPAGE     ISM6HG256X_MLC_STATUS_MAINPAGE
#define     SENSOR_0_BYPASS_MODE  ISM6HG256X_BYPASS_MODE
#define     SENSOR_0_STREAM_MODE  ISM6HG256X_STREAM_MODE
#define     COMMAND_BUFFER_SIZE  (256*1024)                           /* 256KB */
#define     PRINTED_BUFFER_SIZE  (8*1024)

#define CHECK_BSP_FUNCTION(function) \
		{ \
	if ((ret = function) != BSP_ERROR_NONE) { \
		return ret; \
	} \
		}

#define RESET_STRING(string) \
		{ \
	memset(string, 0, strlen(string)); \
		}

#define PRINT(message, ...) \
		{ \
	RESET_STRING(buffer_to_write); \
	uint32_t n = snprintf(buffer_to_write, PRINTED_BUFFER_SIZE, message, ##__VA_ARGS__); \
	STLINK_Transport_Transmit((uint8_t*) buffer_to_write, n); \
		}

typedef enum {
	ISM6HG256X_MLC
} ai_type_t;

/* Public variables   --------------------------------------------------------*/
extern char *command_buffer_ptr;               /* Pointer to the beginning of the command buffer. */
extern char *command_buffer_write_ptr;         /* Pointer to the current write position in the command buffer. */
extern char ism6hg256x_mlc_model_filename[50];            /* Pointer to the ISM6HG256X_MLC Model Filename */
extern volatile int ism6hg256x_mlc_inference;             /* Flag when the application ISM6HG256X_MLC is started. */
extern uint32_t ism6hg256x_mlc_register;                  /* ISM6HG256X_MLC Output Register number. */
extern struct mems_conf_op* current_ism6hg256x_mlc_configuration;         /* ISM6HG256X_MLC configuration in use. */
extern uint32_t current_ism6hg256x_mlc_configuration_size;                 /* ISM6HG256X_MLC configuration size. */
extern volatile bool command_received;            /* Flag when command is received from ST-LINK VCP. */
extern char buffer_to_write[PRINTED_BUFFER_SIZE]; /* Buffer to be printed (it will contain the telemetries). */
extern ai_type_t default_ai;                      /* Selected use-case. */

/* Exported functions --------------------------------------------------------*/
int32_t MX_AI_INERTIAL_Init(void);                  /* Initialization function. */
int32_t MX_AI_INERTIAL_Process(void);               /* Processing function. */
/* Send the telemetries for the ISM6HG256X_MLC use case. */
int32_t send_telemetries_ism6hg256x_mlc();
/* Reading the content of the ISM6HG256X_MLC output registers. */
void read_ism6hg256x_mlc_output(uint8_t* ism6hg256x_mlc_output_reg);
/* Programming the registers inside the ISM6HG256X_MLC. */
void load_ism6hg256x_mlc_configuration(struct mems_conf_op* ism6hg256x_mlc_configuration,
									   uint32_t model_number_of_lines);
/* Filling ISM6HG256X_MLC configuration structure from MODEL file. */
void fill_ism6hg256x_mlc_configuration(const char *config_start,
									   const char *config_end,
									   struct mems_conf_op* ism6hg256x_mlc_configuration);
int32_t debug_fifo_status();               /* Debugging FIFO status. */
int32_t sensor_init();                     /* Initializing sensor. */
void pnpl_init();                          /* PnPL initialization function. */
void pnpl_process(char *command);          /* PnPL processing function. */
void send_identity(char **serializedJSON); /* Sending Board-ID and Firmware-ID. */
void send_status(char **serializedJSON);   /* Sending the Properties Status. */
void identify_get_cmd(PnPLCommand_t *command, char **serializedJSON);      /* Identify the type of get command. */
float32_t compute_actual_odr();             /* Function to compute actual sensor ODR, without drift. */
void jump_to_bootloader();                  /* Set the DFU mode. */
uint8_t hex_char_to_int(char character);    /* Function to convert a single hex character to its integer value. */
uint8_t hex_to_int(const char *hex);        /* Function to convert a two-character hex string to an integer. */
/* Extracting the number of lines from the _model file. */
uint32_t get_model_number_of_lines(int32_t model_content_size, const char *model_content);
void reset_mlc_interrupt_latched();

#ifdef __cplusplus
}
#endif

#endif /*__APP_AI_INERTIAL_H */


