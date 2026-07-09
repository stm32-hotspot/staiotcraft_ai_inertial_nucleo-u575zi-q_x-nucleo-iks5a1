/**
  ******************************************************************************
  * @file    App_model_Controller.c
  * @author  SRA
  * @brief   Controller PnPL Components APIs
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
  * dtmi:appconfig:nucleo_u575zi_q:STAIOTCRAFT_AI_Inertial:applications:controller;1
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

/* Controller PnPL Component -------------------------------------------------*/
extern AppModel_t app_model;

uint8_t controller_comp_init(void)
{
  app_model.controller_model.comp_name = controller_get_key();

  /* USER Component initialization code */
  return PNPL_NO_ERROR_CODE;
}

char *controller_get_key(void)
{
  return "controller";
}




uint8_t controller_set_dfu_mode(void)
{
  jump_to_bootloader();
  /* USER Code */
  return PNPL_NO_ERROR_CODE;
}

uint8_t controller_switch_bank(void)
{
  ToggleFlashBank();
  /* USER Code */
  return PNPL_NO_ERROR_CODE;
}


