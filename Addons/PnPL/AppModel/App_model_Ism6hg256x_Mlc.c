/**
  ******************************************************************************
  * @file    App_model_Ism6hg256x_Mlc.c
  * @author  SRA
  * @brief   Ism6hg256x_Mlc PnPL Components APIs
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file in
  * the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  *
  ******************************************************************************
  */

/**
  ******************************************************************************
  * This file has been auto generated from the following DTDL Component:
  * dtmi:appconfig:nucleo_u575zi_q:STAIOTCRAFT_AI_Inertial:sensors:ism6hg256x_mlc;1
  *
  * Created by: DTDL2PnPL_cGen version 3.1.0-alpha.2
  *
  * WARNING! All changes made to this file will be lost if this is regenerated
  ******************************************************************************
  */

#include "App_model.h"

/* USER includes -------------------------------------------------------------*/

/* USER private function prototypes ------------------------------------------*/

/* USER defines --------------------------------------------------------------*/

/* ISM6HG256X_MLC PnPL Component ---------------------------------------------*/
static SensorModel_t ism6hg256x_mlc_model;
extern AppModel_t app_model;
uint8_t loaded_flag = 0;

uint8_t ism6hg256x_mlc_comp_init(void)
{
  ism6hg256x_mlc_model.comp_name = ism6hg256x_mlc_get_key();

  uint16_t id;
  if (getNextSensorId(&id) != 0)
  {
    /* Sensor slot not available */
    return PNPL_BASE_ERROR_CODE;
  }
  addSensorToAppModel(id, &ism6hg256x_mlc_model);

  /* USER Component initialization code */
  return PNPL_NO_ERROR_CODE;
}

char *ism6hg256x_mlc_get_key(void)
{
  return "ism6hg256x_mlc";
}


uint8_t ism6hg256x_mlc_get_enable(bool *value)
{
  if(ism6hg256x_mlc_inference){
		*value = true;
	}
	else{
		*value = false;
	}
  /* USER Code */
  return PNPL_NO_ERROR_CODE;
}

uint8_t ism6hg256x_mlc_get_model_filename(char **value)
{
  *value = ism6hg256x_mlc_model_filename;
  /* USER Code */
  return PNPL_NO_ERROR_CODE;
}

uint8_t ism6hg256x_mlc_get_stream_id(int8_t *value)
{
  /* USER Code */
  return PNPL_NO_ERROR_CODE;
}

uint8_t ism6hg256x_mlc_get_ep_id(int8_t *value)
{
  /* USER Code */
  return PNPL_NO_ERROR_CODE;
}

uint8_t ism6hg256x_mlc_load_model(const char *filename, int32_t size, const char *content)
{
    strcpy(ism6hg256x_mlc_model_filename, filename);

    default_ai = ISM6HG256X_MLC;

    /* De-allocating space for the ISM6HG256X_MLC configuration structure. */
    if(loaded_flag != 0){
      free(current_ism6hg256x_mlc_configuration);
      loaded_flag = 1;
    }

    // Each config is 4 chars: AA (address) + BB (data)
    if (size % 4 != 0) {
        return 1; // Error: malformed content length
    }

    uint32_t n_config = size / 4;

    current_ism6hg256x_mlc_configuration = (struct mems_conf_op*) calloc(n_config, sizeof(struct mems_conf_op));
    if (current_ism6hg256x_mlc_configuration == NULL) {
      return 1; // Error: memory allocation failed
    } else {
      loaded_flag = 1;
    }
    current_ism6hg256x_mlc_configuration_size = n_config;

    // Parse each quadruplet
    for (uint32_t i = 0; i < n_config; i++) {
      const char *quad = content + (i * 4);

      // Extract address and data as substrings
      char addr_str[3] = {quad[0], quad[1], '\0'};
      char data_str[3] = {quad[2], quad[3], '\0'};

      // Convert hex strings to int
      int address = (int)strtol(addr_str, NULL, 16);
      int data = (int)strtol(data_str, NULL, 16);

      current_ism6hg256x_mlc_configuration[i].type = 1; // MEMS_CONF_OP_WRITE
      current_ism6hg256x_mlc_configuration[i].address = address;
      current_ism6hg256x_mlc_configuration[i].data = data;
    }

    /* Loading ISM6HG256X_MLC configuration into ISM6HG256X_MLC registers. */
    load_ism6hg256x_mlc_configuration(current_ism6hg256x_mlc_configuration, current_ism6hg256x_mlc_configuration_size);

    /* Reset the interrupt of the mlc to latched mode*/
    reset_mlc_interrupt_latched();

    /* Starting ISM6HG256X_MLC inference. */
    ism6hg256x_mlc_inference = 1;

    /* USER Code */
    return PNPL_NO_ERROR_CODE;
}

uint8_t ism6hg256x_mlc_start_inference(void)
{
  default_ai = ISM6HG256X_MLC;
	load_ism6hg256x_mlc_configuration(current_ism6hg256x_mlc_configuration, current_ism6hg256x_mlc_configuration_size);
	reset_mlc_interrupt_latched();
  ism6hg256x_mlc_inference = 1;
  /* USER Code */
  return PNPL_NO_ERROR_CODE;
}

uint8_t ism6hg256x_mlc_stop_inference(void)
{
  ism6hg256x_mlc_inference = 0;
  /* USER Code */
  return PNPL_NO_ERROR_CODE;
}

uint8_t ism6hg256x_mlc_create_telemetry(int32_t label_id, char **telemetry, uint32_t *size)
{
  PnPLTelemetry_t telemetries[1];
  strcpy(telemetries[0].telemetry_name, "label_id");
  telemetries[0].telemetry_value = (void *)& label_id;
  telemetries[0].telemetry_type = PNPL_INT;
  telemetries[0].n_sub_telemetries = 0;

  PnPLSerializeTelemetry("ism6hg256x_mlc", telemetries, 1, telemetry, size, 0);
  return PNPL_NO_ERROR_CODE;
}
