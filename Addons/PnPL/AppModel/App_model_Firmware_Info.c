/**
  ******************************************************************************
  * @file    App_model_Firmware_Info.c
  * @author  SRA
  * @brief   Firmware_Info PnPL Components APIs
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
  * dtmi:appconfig:other:firmware_info;3
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

/* Firmware Information PnPL Component ---------------------------------------*/
extern AppModel_t app_model;

uint8_t firmware_info_comp_init(void)
{
  app_model.firmware_info_model.comp_name = firmware_info_get_key();

  /* USER Component initialization code */
  return PNPL_NO_ERROR_CODE;
}

char *firmware_info_get_key(void)
{
  return "firmware_info";
}


uint8_t firmware_info_get_alias(char **value)
{
  *value = "NUCLEO_U575ZI_Q_IKS5A1_001";
  /* USER Code */
  return PNPL_NO_ERROR_CODE;
}

uint8_t firmware_info_get_fw_name(char **value)
{
  if(default_ai == ISM6HG256X_MLC){
		*value = "STAIOTCRAFT_AI_Inertial_NUCLEO-U575ZI-Q_X-NUCLEO-IKS5A1";
	}
  /* USER Code */
  return PNPL_NO_ERROR_CODE;
}

uint8_t firmware_info_get_fw_version(char **value)
{
  *value = "1.0.0";
  /* USER Code */
  return PNPL_NO_ERROR_CODE;
}

uint8_t firmware_info_get_part_number(char **value)
{
  *value = "STAIOTCRAFT_AI_Inertial";
  /* USER Code */
  return PNPL_NO_ERROR_CODE;
}

uint8_t firmware_info_get_device_url(char **value)
{
  *value = "www.st.com/en/evaluation-tools/nucleo-u575zi-q";
  /* USER Code */
  return PNPL_NO_ERROR_CODE;
}

uint8_t firmware_info_get_fw_url(char **value)
{
  *value = "";
  /* USER Code */
  return PNPL_NO_ERROR_CODE;
}

uint8_t firmware_info_get_mac_address(char **value)
{
  *value = "";
  /* USER Code */
  return PNPL_NO_ERROR_CODE;
}


uint8_t firmware_info_set_alias(const char *value)
{
  /* USER Code */
  return PNPL_NO_ERROR_CODE;
}



