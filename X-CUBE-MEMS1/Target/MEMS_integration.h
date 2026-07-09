/**
  ******************************************************************************
  * @file    MEMS_integration.h
  * @author  MEMS Software Solutions Team
  * @brief   This file provides BSP Motion Sensors Extended interface for custom boards
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

/* Includes ------------------------------------------------------------------*/
#include "ism6hg256x_reg.h"

typedef struct
{
  unsigned int FifoWatermark : 1;
  unsigned int FifoOverrun : 1;
  unsigned int FifoFull : 1;
  unsigned int CounterBdr : 1;
  unsigned int FifoOverrunLatched : 1;
} MY_ISM6HG256X_Fifo_Status_t;

int32_t ISM6HG256X_FIFO_Overrun_Set_INT1(ISM6HG256X_Object_t *pObj, uint8_t Status);
int32_t ISM6HG256X_FIFO_Overrun_Set_INT2(ISM6HG256X_Object_t *pObj, uint8_t Status);
int32_t ISM6HG256X_FIFO_Watermark_Set_INT1(ISM6HG256X_Object_t *pObj, uint8_t Status);
int32_t ISM6HG256X_FIFO_Watermark_Set_INT2(ISM6HG256X_Object_t *pObj, uint8_t Status);
int32_t ISM6HG256X_FIFO_Get_Data_Word(ISM6HG256X_Object_t *pObj, int16_t *data_raw);
int32_t ISM6HG256X_FIFO_Get_All_Status(ISM6HG256X_Object_t *pObj, MY_ISM6HG256X_Fifo_Status_t *Status);
int32_t MY_CUSTOM_MOTION_SENSOR_FIFO_Get_All_Status(uint32_t Instance, MY_ISM6HG256X_Fifo_Status_t *Status);

int32_t MY_CUSTOM_MOTION_SENSOR_FIFO_Set_BDR(uint32_t Instance, uint32_t Function, float Bdr);
int32_t MY_CUSTOM_MOTION_SENSOR_FIFO_Set_INT1_FIFO_Full(uint32_t Instance, uint8_t Status);
int32_t MY_CUSTOM_MOTION_SENSOR_FIFO_Set_INT2_FIFO_Full(uint32_t Instance, uint8_t Status);
int32_t MY_CUSTOM_MOTION_SENSOR_FIFO_Set_Watermark_Level(uint32_t Instance, uint16_t Watermark);
int32_t MY_CUSTOM_MOTION_SENSOR_FIFO_Set_Stop_On_Fth(uint32_t Instance, uint8_t Status);
int32_t MY_CUSTOM_MOTION_SENSOR_FIFO_Set_Mode(uint32_t Instance, uint8_t Mode);
int32_t MY_CUSTOM_MOTION_SENSOR_FIFO_Get_Data_Word(uint32_t Instance, uint32_t Function, int16_t *Data);
int32_t MY_CUSTOM_MOTION_SENSOR_FIFO_Overrun_Set_INT1(uint32_t Instance, uint8_t Status);
int32_t MY_CUSTOM_MOTION_SENSOR_FIFO_Overrun_Set_INT2(uint32_t Instance, uint8_t Status);
int32_t MY_CUSTOM_MOTION_SENSOR_FIFO_Watermark_Set_INT1(uint32_t Instance, uint8_t Status);
int32_t MY_CUSTOM_MOTION_SENSOR_FIFO_Watermark_Set_INT2(uint32_t Instance, uint8_t Status);
int32_t MY_CUSTOM_MOTION_SENSOR_FIFO_Get_Num_Samples(uint32_t Instance, uint16_t *NumSamples);

