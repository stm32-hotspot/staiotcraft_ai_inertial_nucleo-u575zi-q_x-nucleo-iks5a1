/**
  ******************************************************************************
  * @file    App_model_Ism6hg256x_Gyro.c
  * @author  SRA
  * @brief   Ism6hg256x_Gyro PnPL Components APIs
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
  * dtmi:appconfig:nucleo_u575zi_q:STAIOTCRAFT_AI_Inertial:sensors:ism6hg256x_gyro;1
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

/* ISM6HG256X_GYRO PnPL Component --------------------------------------------*/
static SensorModel_t ism6hg256x_gyro_model;
extern AppModel_t app_model;

uint8_t ism6hg256x_gyro_comp_init(void)
{
  ism6hg256x_gyro_model.comp_name = ism6hg256x_gyro_get_key();

  uint16_t id;
  if (getNextSensorId(&id) != 0)
  {
    /* Sensor slot not available */
    return PNPL_BASE_ERROR_CODE;
  }
  addSensorToAppModel(id, &ism6hg256x_gyro_model);

  ism6hg256x_gyro_set_odr_initial_value(pnpl_ism6hg256x_gyro_odr_hz7680);
  ism6hg256x_gyro_set_fs_initial_value(pnpl_ism6hg256x_gyro_fs_dps4000);
  /* USER Component initialization code */
  return PNPL_NO_ERROR_CODE;
}

char *ism6hg256x_gyro_get_key(void)
{
  return "ism6hg256x_gyro";
}


uint8_t ism6hg256x_gyro_get_odr(pnpl_ism6hg256x_gyro_odr_t *enum_id)
{
  float_t value;
  CUSTOM_MOTION_SENSOR_GetOutputDataRate(SENSOR_0,MOTION_GYRO,&value);
  if (value == 7.5f)
  {
    *enum_id = pnpl_ism6hg256x_gyro_odr_hz7_5;
  }
  else if (value == 15.0f)
  {
    *enum_id = pnpl_ism6hg256x_gyro_odr_hz15;
  }
  else if (value == 30.0f)
  {
    *enum_id = pnpl_ism6hg256x_gyro_odr_hz30;
  }
  else if (value == 60.0f)
  {
    *enum_id = pnpl_ism6hg256x_gyro_odr_hz60;
  }
  else if (value == 120.0f)
  {
    *enum_id = pnpl_ism6hg256x_gyro_odr_hz120;
  }
  else if (value == 240.0f)
  {
    *enum_id = pnpl_ism6hg256x_gyro_odr_hz240;
  }
  else if (value == 480.0f)
  {
    *enum_id = pnpl_ism6hg256x_gyro_odr_hz480;
  }
  else if (value == 960.0f)
  {
    *enum_id = pnpl_ism6hg256x_gyro_odr_hz960;
  }
  else if (value == 1920.0f)
  {
    *enum_id = pnpl_ism6hg256x_gyro_odr_hz1920;
  }
  else if (value == 3840.0f)
  {
    *enum_id = pnpl_ism6hg256x_gyro_odr_hz3840;
  }
  else if (value == 7680.0f)
  {
    *enum_id = pnpl_ism6hg256x_gyro_odr_hz7680;
  }
  else
  {
    return 1; // Error code for unsupported ODR value
  }
  /* USER Code */
  return PNPL_NO_ERROR_CODE;
}

uint8_t ism6hg256x_gyro_get_fs(pnpl_ism6hg256x_gyro_fs_t *enum_id)
{
  int32_t value;
  CUSTOM_MOTION_SENSOR_GetFullScale(SENSOR_0,MOTION_GYRO,&value);
  if (value == 250)
  {
    *enum_id = pnpl_ism6hg256x_gyro_fs_dps250;
  }
  else if (value == 500)
  {
    *enum_id = pnpl_ism6hg256x_gyro_fs_dps500;
  }
  else if (value == 1000)
  {
    *enum_id = pnpl_ism6hg256x_gyro_fs_dps1000;
  }
  else if (value == 2000)
  {
    *enum_id = pnpl_ism6hg256x_gyro_fs_dps2000;
  }
  else if (value == 4000)
  {
    *enum_id = pnpl_ism6hg256x_gyro_fs_dps4000;
  }
  else
  {
    return 1; // Error code for unsupported FS value
  }
  /* USER Code */
  return PNPL_NO_ERROR_CODE;
}

uint8_t ism6hg256x_gyro_get_stream_id(int8_t *value)
{
  /* USER Code */
  return PNPL_NO_ERROR_CODE;
}

uint8_t ism6hg256x_gyro_get_ep_id(int8_t *value)
{
  /* USER Code */
  return PNPL_NO_ERROR_CODE;
}

uint8_t ism6hg256x_gyro_set_odr_initial_value(pnpl_ism6hg256x_gyro_odr_t enum_id){

  float_t value;
  switch (enum_id)
  {
    case pnpl_ism6hg256x_gyro_odr_hz7_5:
      value = 7.5f;
      break;
    case pnpl_ism6hg256x_gyro_odr_hz15:
      value = 15.0f;
      break;
    case pnpl_ism6hg256x_gyro_odr_hz30:
      value = 30.0f;
      break;
    case pnpl_ism6hg256x_gyro_odr_hz60:
      value = 60.0f;
      break;
    case pnpl_ism6hg256x_gyro_odr_hz120:
      value = 120.0f;
      break;
    case pnpl_ism6hg256x_gyro_odr_hz240:
      value = 240.0f;
      break;
    case pnpl_ism6hg256x_gyro_odr_hz480:
      value = 480.0f;
      break;
    case pnpl_ism6hg256x_gyro_odr_hz960:
      value = 960.0f;
      break;
    case pnpl_ism6hg256x_gyro_odr_hz1920:
      value = 1920.0f;
      break;
    case pnpl_ism6hg256x_gyro_odr_hz3840:
      value = 3840.0f;
      break;
    case pnpl_ism6hg256x_gyro_odr_hz7680:
      value = 7680.0f;
      break;
    default:
      return 1;
  }
	CUSTOM_MOTION_SENSOR_SetOutputDataRate(SENSOR_0,MOTION_GYRO,value);
	/* USER Code */
	return PNPL_NO_ERROR_CODE;
}

uint8_t ism6hg256x_gyro_set_fs_initial_value(pnpl_ism6hg256x_gyro_fs_t enum_id){

  int32_t value;
  switch (enum_id)
  {
    case pnpl_ism6hg256x_gyro_fs_dps250:
      value = 250;
      break;
    case pnpl_ism6hg256x_gyro_fs_dps500:
      value = 500;
      break;
    case pnpl_ism6hg256x_gyro_fs_dps1000:
      value = 1000;
      break;
    case pnpl_ism6hg256x_gyro_fs_dps2000:
      value = 2000;
      break;
    case pnpl_ism6hg256x_gyro_fs_dps4000:
      value = 4000;
      break;
    default:
      return 1;
  }
  CUSTOM_MOTION_SENSOR_SetFullScale(SENSOR_0,MOTION_GYRO,value);
	/* USER Code */
	return PNPL_NO_ERROR_CODE;
}

