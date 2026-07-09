/**
  ******************************************************************************
  * @file    MEMS_integration.c
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
#include "custom_motion_sensors_ex.h"
#include "MEMS_integration.h"

extern void *MotionCompObj[CUSTOM_MOTION_INSTANCES_NBR];

/**
 * @brief  Set FIFO BDR value
 * @param  Instance the device instance
 * @param  Function Motion sensor function
 * @param  Odr FIFO BDR value
 * @retval BSP status
 */
int32_t MY_CUSTOM_MOTION_SENSOR_FIFO_Set_BDR(uint32_t Instance, uint32_t Function, float Bdr)
{
	int32_t ret;

	switch(Instance)
	{
#if (USE_MOTION_SENSOR_IIS3DWB_0 == 1)
	case IIS3DWB_0:
		if(IIS3DWB_FIFO_Set_BDR(MotionCompObj[Instance], Bdr) != BSP_ERROR_NONE)
		{
			ret = BSP_ERROR_COMPONENT_FAILURE;
		}
		else
		{
			ret = BSP_ERROR_NONE;
		}
		break;
#endif

#if (USE_CUSTOM_MOTION_SENSOR_ISM330DHCX_0 == 1)
	case CUSTOM_ISM330DHCX_0:
		if((Function & MOTION_ACCELERO) == MOTION_ACCELERO)
		{
			if(ISM330DHCX_FIFO_ACC_Set_BDR(MotionCompObj[Instance], Bdr) != BSP_ERROR_NONE)
			{
				ret = BSP_ERROR_COMPONENT_FAILURE;
			}
			else
			{
				ret = BSP_ERROR_NONE;
			}
		}
		else if((Function & MOTION_GYRO) == MOTION_GYRO)
		{
			if(ISM330DHCX_FIFO_GYRO_Set_BDR(MotionCompObj[Instance], Bdr) != BSP_ERROR_NONE)
			{
				ret = BSP_ERROR_COMPONENT_FAILURE;
			}
			else
			{
				ret = BSP_ERROR_NONE;
			}
		}
		else
		{
			ret = BSP_ERROR_WRONG_PARAM;
		}
		break;
#endif

#if (USE_CUSTOM_MOTION_SENSOR_LSM6DSO32X_0 == 1)
	case CUSTOM_LSM6DSO32X_0:
		if((Function & MOTION_ACCELERO) == MOTION_ACCELERO)
		{
			if(LSM6DSO32X_FIFO_ACC_Set_BDR(MotionCompObj[Instance], Bdr) != BSP_ERROR_NONE)
			{
				ret = BSP_ERROR_COMPONENT_FAILURE;
			}
			else
			{
				ret = BSP_ERROR_NONE;
			}
		}
		else if((Function & MOTION_GYRO) == MOTION_GYRO)
		{
			if(LSM6DSO32X_FIFO_GYRO_Set_BDR(MotionCompObj[Instance], Bdr) != BSP_ERROR_NONE)
			{
				ret = BSP_ERROR_COMPONENT_FAILURE;
			}
			else
			{
				ret = BSP_ERROR_NONE;
			}
		}
		else
		{
			ret = BSP_ERROR_WRONG_PARAM;
		}
		break;
#endif

#if (USE_CUSTOM_MOTION_SENSOR_ISM6HG256X_0 == 1)
	case CUSTOM_ISM6HG256X_0:
		if((Function & MOTION_ACCELERO) == MOTION_ACCELERO)
		{
			if(ISM6HG256X_FIFO_ACC_Set_BDR(MotionCompObj[Instance], Bdr) != BSP_ERROR_NONE)
			{
				ret = BSP_ERROR_COMPONENT_FAILURE;
			}
			else
			{
				ret = BSP_ERROR_NONE;
			}
		}
		else if((Function & MOTION_GYRO) == MOTION_GYRO)
		{
			if(ISM6HG256X_FIFO_GYRO_Set_BDR(MotionCompObj[Instance], Bdr) != BSP_ERROR_NONE)
			{
				ret = BSP_ERROR_COMPONENT_FAILURE;
			}
			else
			{
				ret = BSP_ERROR_NONE;
			}
		}
		else
		{
			ret = BSP_ERROR_WRONG_PARAM;
		}
		break;
#endif

	default:
		ret = BSP_ERROR_WRONG_PARAM;
		break;
	}

	return ret;
}

/**
 * @brief  Set FIFO full interrupt on INT1 pin
 * @param  Instance the device instance
 * @param  Status FIFO full interrupt on INT1 pin
 * @retval BSP status
 */
int32_t MY_CUSTOM_MOTION_SENSOR_FIFO_Set_INT1_FIFO_Full(uint32_t Instance, uint8_t Status)
{
	int32_t ret;

	switch(Instance)
	{
#if (USE_MOTION_SENSOR_IIS3DWB_0 == 1)
	case IIS3DWB_0:
		if(IIS3DWB_INT1_Set_FIFO_Full(MotionCompObj[Instance], Status) != BSP_ERROR_NONE)
		{
			ret = BSP_ERROR_COMPONENT_FAILURE;
		}
		else
		{
			ret = BSP_ERROR_NONE;
		}
		break;
#endif

#if (USE_CUSTOM_MOTION_SENSOR_ISM330DHCX_0 == 1)
	case CUSTOM_ISM330DHCX_0:
		if(ISM330DHCX_FIFO_Set_INT1_FIFO_Full(MotionCompObj[Instance], Status) != BSP_ERROR_NONE)
		{
			ret = BSP_ERROR_COMPONENT_FAILURE;
		}
		else
		{
			ret = BSP_ERROR_NONE;
		}
		break;
#endif

#if (USE_CUSTOM_MOTION_SENSOR_LSM6DSO32X_0 == 1)
	case CUSTOM_LSM6DSO32X_0:
		if(LSM6DSO32X_FIFO_Set_INT1_FIFO_Full(MotionCompObj[Instance], Status) != BSP_ERROR_NONE)
		{
			ret = BSP_ERROR_COMPONENT_FAILURE;
		}
		else
		{
			ret = BSP_ERROR_NONE;
		}
		break;
#endif

#if (USE_CUSTOM_MOTION_SENSOR_ISM6HG256X_0 == 1)
	case CUSTOM_ISM6HG256X_0:
		if(ISM6HG256X_FIFO_Set_INT1_FIFO_Full(MotionCompObj[Instance], Status) != BSP_ERROR_NONE)
		{
			ret = BSP_ERROR_COMPONENT_FAILURE;
		}
		else
		{
			ret = BSP_ERROR_NONE;
		}
		break;
#endif

	default:
		ret = BSP_ERROR_WRONG_PARAM;
		break;
	}

	return ret;
}

/**
 * @brief  Set FIFO full interrupt on INT2 pin
 * @param  Instance the device instance
 * @param  Status FIFO full interrupt on INT2 pin
 * @retval BSP status
 */
int32_t MY_CUSTOM_MOTION_SENSOR_FIFO_Set_INT2_FIFO_Full(uint32_t Instance, uint8_t Status)
{
	int32_t ret;

	switch(Instance)
	{
#if (USE_MOTION_SENSOR_IIS3DWB_0 == 1)
	case IIS3DWB_0:
		if(IIS3DWB_INT2_Set_FIFO_Full(MotionCompObj[Instance], Status) != BSP_ERROR_NONE)
		{
			ret = BSP_ERROR_COMPONENT_FAILURE;
		}
		else
		{
			ret = BSP_ERROR_NONE;
		}
		break;
#endif

#if (USE_CUSTOM_MOTION_SENSOR_ISM330DHCX_0 == 1)
	case CUSTOM_ISM330DHCX_0:
		if(ISM330DHCX_FIFO_Set_INT2_FIFO_Full(MotionCompObj[Instance], Status) != BSP_ERROR_NONE)
		{
			ret = BSP_ERROR_COMPONENT_FAILURE;
		}
		else
		{
			ret = BSP_ERROR_NONE;
		}
		break;
#endif
#if (USE_CUSTOM_MOTION_SENSOR_LSM6DSO32X_0 == 1)
	case CUSTOM_LSM6DSO32X_0:
		if(LSM6DSO32X_FIFO_Set_INT2_FIFO_Full(MotionCompObj[Instance], Status) != BSP_ERROR_NONE)
		{
			ret = BSP_ERROR_COMPONENT_FAILURE;
		}
		else
		{
			ret = BSP_ERROR_NONE;
		}
		break;
#endif

#if (USE_CUSTOM_MOTION_SENSOR_ISM6HG256X_0 == 1)
	case CUSTOM_ISM6HG256X_0:
		if(ISM6HG256X_FIFO_Set_INT2_FIFO_Full(MotionCompObj[Instance], Status) != BSP_ERROR_NONE)
		{
			ret = BSP_ERROR_COMPONENT_FAILURE;
		}
		else
		{
			ret = BSP_ERROR_NONE;
		}
		break;
#endif

	default:
		ret = BSP_ERROR_WRONG_PARAM;
		break;
	}

	return ret;
}

/**
 * @brief  Set FIFO watermark level
 * @param  Instance the device instance
 * @param  Watermark FIFO watermark level
 * @retval BSP status
 */
int32_t MY_CUSTOM_MOTION_SENSOR_FIFO_Set_Watermark_Level(uint32_t Instance, uint16_t Watermark)
{
	int32_t ret;

	switch(Instance)
	{
#if (USE_MOTION_SENSOR_IIS3DWB_0 == 1)
	case IIS3DWB_0:
		if(IIS3DWB_FIFO_Set_Watermark_Level(MotionCompObj[Instance], Watermark) != BSP_ERROR_NONE)
		{
			ret = BSP_ERROR_COMPONENT_FAILURE;
		}
		else
		{
			ret = BSP_ERROR_NONE;
		}
		break;
#endif

#if (USE_CUSTOM_MOTION_SENSOR_ISM330DHCX_0 == 1)
	case CUSTOM_ISM330DHCX_0:
		if(ISM330DHCX_FIFO_Set_Watermark_Level(MotionCompObj[Instance], Watermark) != BSP_ERROR_NONE)
		{
			ret = BSP_ERROR_COMPONENT_FAILURE;
		}
		else
		{
			ret = BSP_ERROR_NONE;
		}
		break;
#endif

#if (USE_CUSTOM_MOTION_SENSOR_LSM6DSO32X_0 == 1)
	case CUSTOM_LSM6DSO32X_0:
		if(LSM6DSO32X_FIFO_Set_Watermark_Level(MotionCompObj[Instance], Watermark) != BSP_ERROR_NONE)
		{
			ret = BSP_ERROR_COMPONENT_FAILURE;
		}
		else
		{
			ret = BSP_ERROR_NONE;
		}
		break;
#endif

#if (USE_CUSTOM_MOTION_SENSOR_ISM6HG256X_0 == 1)
	case CUSTOM_ISM6HG256X_0:
		if(ISM6HG256X_FIFO_Set_Watermark_Level(MotionCompObj[Instance], Watermark) != BSP_ERROR_NONE)
		{
			ret = BSP_ERROR_COMPONENT_FAILURE;
		}
		else
		{
			ret = BSP_ERROR_NONE;
		}
		break;
#endif

	default:
		ret = BSP_ERROR_WRONG_PARAM;
		break;
	}

	return ret;
}

/**
 * @brief  Set FIFO stop on watermark
 * @param  Instance the device instance
 * @param  Status FIFO stop on watermark status
 * @retval BSP status
 */
int32_t MY_CUSTOM_MOTION_SENSOR_FIFO_Set_Stop_On_Fth(uint32_t Instance, uint8_t Status)
{
	int32_t ret;

	switch(Instance)
	{
#if (USE_MOTION_SENSOR_IIS3DWB_0 == 1)
	case IIS3DWB_0:
		if(IIS3DWB_FIFO_Set_Stop_On_Fth(MotionCompObj[Instance], Status) != BSP_ERROR_NONE)
		{
			ret = BSP_ERROR_COMPONENT_FAILURE;
		}
		else
		{
			ret = BSP_ERROR_NONE;
		}
		break;
#endif

#if (USE_CUSTOM_MOTION_SENSOR_ISM330DHCX_0 == 1)
	case CUSTOM_ISM330DHCX_0:
		if(ISM330DHCX_FIFO_Set_Stop_On_Fth(MotionCompObj[Instance], Status) != BSP_ERROR_NONE)
		{
			ret = BSP_ERROR_COMPONENT_FAILURE;
		}
		else
		{
			ret = BSP_ERROR_NONE;
		}
		break;
#endif

#if (USE_CUSTOM_MOTION_SENSOR_LSM6DSO32X_0 == 1)
	case CUSTOM_LSM6DSO32X_0:
		if(LSM6DSO32X_FIFO_Set_Stop_On_Fth(MotionCompObj[Instance], Status) != BSP_ERROR_NONE)
		{
			ret = BSP_ERROR_COMPONENT_FAILURE;
		}
		else
		{
			ret = BSP_ERROR_NONE;
		}
		break;
#endif

#if (USE_CUSTOM_MOTION_SENSOR_ISM6HG256X_0 == 1)
	case CUSTOM_ISM6HG256X_0:
		if(ISM6HG256X_FIFO_Set_Stop_On_Fth(MotionCompObj[Instance], Status) != BSP_ERROR_NONE)
		{
			ret = BSP_ERROR_COMPONENT_FAILURE;
		}
		else
		{
			ret = BSP_ERROR_NONE;
		}
		break;
#endif

	default:
		ret = BSP_ERROR_WRONG_PARAM;
		break;
	}

	return ret;
}

/**
 * @brief  Set FIFO mode
 * @param  Instance the device instance
 * @param  Mode FIFO mode
 * @retval BSP status
 */
int32_t MY_CUSTOM_MOTION_SENSOR_FIFO_Set_Mode(uint32_t Instance, uint8_t Mode)
{
	int32_t ret;

	switch(Instance)
	{

#if (USE_MOTION_SENSOR_IIS3DWB_0 == 1)
	case IIS3DWB_0:
		if(IIS3DWB_FIFO_Set_Mode(MotionCompObj[Instance], (iis3dwb_fifo_mode_t) Mode) != BSP_ERROR_NONE)
		{
			ret = BSP_ERROR_COMPONENT_FAILURE;
		}
		else
		{
			ret = BSP_ERROR_NONE;
		}
		break;
#endif

#if (USE_CUSTOM_MOTION_SENSOR_ISM330DHCX_0 == 1)
	case CUSTOM_ISM330DHCX_0:
		if(ISM330DHCX_FIFO_Set_Mode(MotionCompObj[Instance], Mode) != BSP_ERROR_NONE)
		{
			ret = BSP_ERROR_COMPONENT_FAILURE;
		}
		else
		{
			ret = BSP_ERROR_NONE;
		}
		break;
#endif

#if (USE_CUSTOM_MOTION_SENSOR_LSM6DSO32X_0 == 1)
	case CUSTOM_LSM6DSO32X_0:
		if(LSM6DSO32X_FIFO_Set_Mode(MotionCompObj[Instance], Mode) != BSP_ERROR_NONE)
		{
			ret = BSP_ERROR_COMPONENT_FAILURE;
		}
		else
		{
			ret = BSP_ERROR_NONE;
		}
		break;
#endif

#if (USE_CUSTOM_MOTION_SENSOR_ISM6HG256X_0 == 1)
	case CUSTOM_ISM6HG256X_0:
		if(ISM6HG256X_FIFO_Set_Mode(MotionCompObj[Instance], Mode) != BSP_ERROR_NONE)
		{
			ret = BSP_ERROR_COMPONENT_FAILURE;
		}
		else
		{
			ret = BSP_ERROR_NONE;
		}
		break;
#endif

	default:
		ret = BSP_ERROR_WRONG_PARAM;
		break;
	}

	return ret;
}

/**
  * @brief  Get the ISM6HG256X FIFO accelero single word (16-bit data)
  * @param  pObj the device pObj
  * @param  Acceleration FIFO single data
  * @retval 0 in case of success, an error code otherwise
  */
int32_t ISM6HG256X_FIFO_Get_Data_Word(ISM6HG256X_Object_t *pObj, int16_t *data_raw)
{
  uint8_t data[6];

  if (ISM6HG256X_FIFO_Get_Data(pObj, data) != ISM6HG256X_OK)
  {
    return ISM6HG256X_ERROR;
  }

  data_raw[0] = ((int16_t)data[1] << 8) | data[0];
  data_raw[1] = ((int16_t)data[3] << 8) | data[2];
  data_raw[2] = ((int16_t)data[5] << 8) | data[4];

  return ISM6HG256X_OK;
}

/**
 * @brief  Get FIFO single axis data RAW
 * @param  Instance the device instance
 * @param  Function Motion sensor function. Could be:
 *         - MOTION_GYRO or MOTION_ACCELERO
 * @param  Data FIFO single axis data
 * @retval BSP status
 */
int32_t MY_CUSTOM_MOTION_SENSOR_FIFO_Get_Data_Word(uint32_t Instance, uint32_t Function, int16_t *Data)
{
	int32_t ret = 0;

	switch(Instance)
	{
#if (USE_CUSTOM_MOTION_SENSOR_ISM330DHCX_0 == 1)
	case CUSTOM_ISM330DHCX_0:
		if((Function & MOTION_ACCELERO) == MOTION_ACCELERO)
		{
			if(ISM330DHCX_FIFO_Get_Data_Word(MotionCompObj[Instance], Data) != BSP_ERROR_NONE)
			{
				ret = BSP_ERROR_COMPONENT_FAILURE;
			}
			else
			{
				ret = BSP_ERROR_NONE;
			}
		}
		else if((Function & MOTION_GYRO) == MOTION_GYRO)
		{
			/*if(ISM330DHCX_FIFO_GYRO_Get_Axes(MotionCompObj[Instance], Data) != BSP_ERROR_NONE)
			{
				ret = BSP_ERROR_COMPONENT_FAILURE;
			}
			else
			{
				ret = BSP_ERROR_NONE;
			}*/
		}
		else
		{
			ret = BSP_ERROR_WRONG_PARAM;
		}
		break;
#endif

#if (USE_CUSTOM_MOTION_SENSOR_LSM6DSO32X_0 == 1)
	case CUSTOM_LSM6DSO32X_0:
		if((Function & MOTION_ACCELERO) == MOTION_ACCELERO)
		{
			if(LSM6DSO32X_FIFO_Get_Data_Word(MotionCompObj[Instance], Data) != BSP_ERROR_NONE)
			{
				ret = BSP_ERROR_COMPONENT_FAILURE;
			}
			else
			{
				ret = BSP_ERROR_NONE;
			}
		}
		else if((Function & MOTION_GYRO) == MOTION_GYRO)
		{
			/*if(LSM6DSO32X_FIFO_GYRO_Get_Axes(MotionCompObj[Instance], Data) != BSP_ERROR_NONE)
			{
				ret = BSP_ERROR_COMPONENT_FAILURE;
			}
			else
			{
				ret = BSP_ERROR_NONE;
			}*/
		}
		else
		{
			ret = BSP_ERROR_WRONG_PARAM;
		}
		break;
#endif

#if (USE_CUSTOM_MOTION_SENSOR_ISM6HG256X_0 == 1)
	case CUSTOM_ISM6HG256X_0:
		if((Function & MOTION_ACCELERO) == MOTION_ACCELERO)
		{
			if(ISM6HG256X_FIFO_Get_Data_Word(MotionCompObj[Instance], Data) != BSP_ERROR_NONE)
			{
				ret = BSP_ERROR_COMPONENT_FAILURE;
			}
			else
			{
				ret = BSP_ERROR_NONE;
			}
		}
		else if((Function & MOTION_GYRO) == MOTION_GYRO)
		{
			/*if(ISM6HG256X_FIFO_GYRO_Get_Axes(MotionCompObj[Instance], Data) != BSP_ERROR_NONE)
			{
				ret = BSP_ERROR_COMPONENT_FAILURE;
			}
			else
			{
				ret = BSP_ERROR_NONE;
			}*/
		}
		else
		{
			ret = BSP_ERROR_WRONG_PARAM;
		}
		break;
#endif

	default:
		ret = BSP_ERROR_WRONG_PARAM;
		break;
	}

	return ret;
}

int32_t MY_CUSTOM_MOTION_SENSOR_FIFO_Overrun_Set_INT1(uint32_t Instance, uint8_t Status)
{
	int32_t ret;

	switch(Instance)
	{
#if (USE_CUSTOM_MOTION_SENSOR_ISM330DHCX_0 == 1)
	case CUSTOM_ISM330DHCX_0:
		if(ISM330DHCX_FIFO_Overrun_Set_INT1(MotionCompObj[Instance], Status) != BSP_ERROR_NONE)
		{
			ret = BSP_ERROR_COMPONENT_FAILURE;
		}
		else
		{
			ret = BSP_ERROR_NONE;
		}
		break;
#endif

#if (USE_CUSTOM_MOTION_SENSOR_LSM6DSO32X_0 == 1)
	case CUSTOM_LSM6DSO32X_0:
		if(LSM6DSO32X_FIFO_Overrun_Set_INT1(MotionCompObj[Instance], Status) != BSP_ERROR_NONE)
		{
			ret = BSP_ERROR_COMPONENT_FAILURE;
		}
		else
		{
			ret = BSP_ERROR_NONE;
		}
		break;
#endif

#if (USE_CUSTOM_MOTION_SENSOR_ISM6HG256X_0 == 1)
	case CUSTOM_ISM6HG256X_0:
		if(ISM6HG256X_FIFO_Overrun_Set_INT1(MotionCompObj[Instance], Status) != BSP_ERROR_NONE)
		{
			ret = BSP_ERROR_COMPONENT_FAILURE;
		}
		else
		{
			ret = BSP_ERROR_NONE;
		}
		break;
#endif

	default:
		ret = BSP_ERROR_WRONG_PARAM;
		break;
	}

	return ret;
}

int32_t MY_CUSTOM_MOTION_SENSOR_FIFO_Overrun_Set_INT2(uint32_t Instance, uint8_t Status)
{
	int32_t ret;

	switch(Instance)
	{
#if (USE_CUSTOM_MOTION_SENSOR_ISM330DHCX_0 == 1)
	case CUSTOM_ISM330DHCX_0:
		if(ISM330DHCX_FIFO_Overrun_Set_INT2(MotionCompObj[Instance], Status) != BSP_ERROR_NONE)
		{
			ret = BSP_ERROR_COMPONENT_FAILURE;
		}
		else
		{
			ret = BSP_ERROR_NONE;
		}
		break;
#endif

#if (USE_CUSTOM_MOTION_SENSOR_LSM6DSO32X_0 == 1)
	case CUSTOM_LSM6DSO32X_0:
		if(LSM6DSO32X_FIFO_Overrun_Set_INT2(MotionCompObj[Instance], Status) != BSP_ERROR_NONE)
		{
			ret = BSP_ERROR_COMPONENT_FAILURE;
		}
		else
		{
			ret = BSP_ERROR_NONE;
		}
		break;
#endif

#if (USE_CUSTOM_MOTION_SENSOR_ISM6HG256X_0 == 1)
	case CUSTOM_ISM6HG256X_0:
		if(ISM6HG256X_FIFO_Overrun_Set_INT2(MotionCompObj[Instance], Status) != BSP_ERROR_NONE)
		{
			ret = BSP_ERROR_COMPONENT_FAILURE;
		}
		else
		{
			ret = BSP_ERROR_NONE;
		}
		break;
#endif

	default:
		ret = BSP_ERROR_WRONG_PARAM;
		break;
	}

	return ret;
}

/**
* @brief  Set the ISM6HG256X FIFO overrun interrupt on INT1 pin
* @param  pObj the device pObj
* @param  Status FIFO overrun interrupt on INT1 pin status
* @retval 0 in case of success, an error code otherwise
*/
int32_t ISM6HG256X_FIFO_Overrun_Set_INT1(ISM6HG256X_Object_t *pObj, uint8_t Status)
{
  ism6hg256x_reg_t reg;

  if (ism6hg256x_read_reg(&(pObj->Ctx), ISM6HG256X_INT1_CTRL, &reg.byte, 1) != ISM6HG256X_OK)
  {
    return ISM6HG256X_ERROR;
  }

  reg.int1_ctrl.int1_fifo_ovr = Status;

  if (ism6hg256x_write_reg(&(pObj->Ctx), ISM6HG256X_INT1_CTRL, &reg.byte, 1) != ISM6HG256X_OK)
  {
    return ISM6HG256X_ERROR;
  }

  return ISM6HG256X_OK;
}

/**
* @brief  Set the ISM6HG256X FIFO overrun interrupt on INT2 pin
* @param  pObj the device pObj
* @param  Status FIFO overrun interrupt on INT2 pin status
* @retval 0 in case of success, an error code otherwise
*/
int32_t ISM6HG256X_FIFO_Overrun_Set_INT2(ISM6HG256X_Object_t *pObj, uint8_t Status)
{
  ism6hg256x_reg_t reg;

  if (ism6hg256x_read_reg(&(pObj->Ctx), ISM6HG256X_INT2_CTRL, &reg.byte, 1) != ISM6HG256X_OK)
  {
    return ISM6HG256X_ERROR;
  }

  reg.int2_ctrl.int2_fifo_ovr = Status;

  if (ism6hg256x_write_reg(&(pObj->Ctx), ISM6HG256X_INT2_CTRL, &reg.byte, 1) != ISM6HG256X_OK)
  {
    return ISM6HG256X_ERROR;
  }

  return ISM6HG256X_OK;
}

int32_t MY_CUSTOM_MOTION_SENSOR_FIFO_Watermark_Set_INT1(uint32_t Instance, uint8_t Status)
{
	int32_t ret;

	switch(Instance)
	{
#if (USE_CUSTOM_MOTION_SENSOR_ISM330DHCX_0 == 1)
	case CUSTOM_ISM330DHCX_0:
		if(ISM330DHCX_FIFO_Watermark_Set_INT1(MotionCompObj[Instance], Status) != BSP_ERROR_NONE)
		{
			ret = BSP_ERROR_COMPONENT_FAILURE;
		}
		else
		{
			ret = BSP_ERROR_NONE;
		}
		break;
#endif

#if (USE_CUSTOM_MOTION_SENSOR_LSM6DSO32X_0 == 1)
	case CUSTOM_LSM6DSO32X_0:
		if(LSM6DSO32X_FIFO_Watermark_Set_INT1(MotionCompObj[Instance], Status) != BSP_ERROR_NONE)
		{
			ret = BSP_ERROR_COMPONENT_FAILURE;
		}
		else
		{
			ret = BSP_ERROR_NONE;
		}
		break;
#endif

#if (USE_CUSTOM_MOTION_SENSOR_ISM6HG256X_0 == 1)
	case CUSTOM_ISM6HG256X_0:
		if(ISM6HG256X_FIFO_Watermark_Set_INT1(MotionCompObj[Instance], Status) != BSP_ERROR_NONE)
		{
			ret = BSP_ERROR_COMPONENT_FAILURE;
		}
		else
		{
			ret = BSP_ERROR_NONE;
		}
		break;
#endif

	default:
		ret = BSP_ERROR_WRONG_PARAM;
		break;
	}

	return ret;
}

int32_t MY_CUSTOM_MOTION_SENSOR_FIFO_Watermark_Set_INT2(uint32_t Instance, uint8_t Status)
{
	int32_t ret;

	switch(Instance)
	{
#if (USE_CUSTOM_MOTION_SENSOR_ISM330DHCX_0 == 1)
	case CUSTOM_ISM330DHCX_0:
		if(ISM330DHCX_FIFO_Watermark_Set_INT2(MotionCompObj[Instance], Status) != BSP_ERROR_NONE)
		{
			ret = BSP_ERROR_COMPONENT_FAILURE;
		}
		else
		{
			ret = BSP_ERROR_NONE;
		}
		break;
#endif

#if (USE_CUSTOM_MOTION_SENSOR_LSM6DSO32X_0 == 1)
	case CUSTOM_LSM6DSO32X_0:
		if(LSM6DSO32X_FIFO_Watermark_Set_INT2(MotionCompObj[Instance], Status) != BSP_ERROR_NONE)
		{
			ret = BSP_ERROR_COMPONENT_FAILURE;
		}
		else
		{
			ret = BSP_ERROR_NONE;
		}
		break;
#endif

#if (USE_CUSTOM_MOTION_SENSOR_ISM6HG256X_0 == 1)
	case CUSTOM_ISM6HG256X_0:
		if(ISM6HG256X_FIFO_Watermark_Set_INT2(MotionCompObj[Instance], Status) != BSP_ERROR_NONE)
		{
			ret = BSP_ERROR_COMPONENT_FAILURE;
		}
		else
		{
			ret = BSP_ERROR_NONE;
		}
		break;
#endif

	default:
		ret = BSP_ERROR_WRONG_PARAM;
		break;
	}

	return ret;
}

/**
* @brief  Set the ISM6HG256X FIFO watermark interrupt on INT1 pin
* @param  pObj the device pObj
* @param  Status FIFO watermark interrupt on INT1 pin status
* @retval 0 in case of success, an error code otherwise
*/
int32_t ISM6HG256X_FIFO_Watermark_Set_INT1(ISM6HG256X_Object_t *pObj, uint8_t Status)
{
  ism6hg256x_reg_t reg;

  if (ism6hg256x_read_reg(&(pObj->Ctx), ISM6HG256X_INT1_CTRL, &reg.byte, 1) != ISM6HG256X_OK)
  {
    return ISM6HG256X_ERROR;
  }

  reg.int1_ctrl.int1_fifo_th = Status;

  if (ism6hg256x_write_reg(&(pObj->Ctx), ISM6HG256X_INT1_CTRL, &reg.byte, 1) != ISM6HG256X_OK)
  {
    return ISM6HG256X_ERROR;
  }

  return ISM6HG256X_OK;
}

/**
* @brief  Set the ISM6HG256X FIFO watermark interrupt on INT2 pin
* @param  pObj the device pObj
* @param  Status FIFO watermark interrupt on INT2 pin status
* @retval 0 in case of success, an error code otherwise
*/
int32_t ISM6HG256X_FIFO_Watermark_Set_INT2(ISM6HG256X_Object_t *pObj, uint8_t Status)
{
  ism6hg256x_reg_t reg;

  if (ism6hg256x_read_reg(&(pObj->Ctx), ISM6HG256X_INT2_CTRL, &reg.byte, 1) != ISM6HG256X_OK)
  {
    return ISM6HG256X_ERROR;
  }

  reg.int2_ctrl.int2_fifo_th = Status;

  if (ism6hg256x_write_reg(&(pObj->Ctx), ISM6HG256X_INT2_CTRL, &reg.byte, 1) != ISM6HG256X_OK)
  {
    return ISM6HG256X_ERROR;
  }

  return ISM6HG256X_OK;
}

/**
 * @brief  Get FIFO all status
 * @param  Instance the device instance
 * @param  Status FIFO all status
 * @retval BSP status
 */
int32_t MY_CUSTOM_MOTION_SENSOR_FIFO_Get_All_Status(uint32_t Instance, MY_ISM6HG256X_Fifo_Status_t *Status)
{
  int32_t ret;

  switch (Instance)
  {
#if (USE_CUSTOM_MOTION_SENSOR_ISM330DHCX_0 == 1)
    case CUSTOM_ISM330DHCX_0:
      if (ISM330DHCX_FIFO_Get_All_Status(MotionCompObj[Instance], Status) != BSP_ERROR_NONE)
      {
        ret = BSP_ERROR_COMPONENT_FAILURE;
      }
      else
      {
        ret = BSP_ERROR_NONE;
      }
      break;
#endif

#if (USE_CUSTOM_MOTION_SENSOR_LSM6DSO32X_0 == 1)
    case CUSTOM_LSM6DSO32X_0:
      if (LSM6DSO32X_FIFO_Get_All_Status(MotionCompObj[Instance], Status) != BSP_ERROR_NONE)
      {
        ret = BSP_ERROR_COMPONENT_FAILURE;
      }
      else
      {
        ret = BSP_ERROR_NONE;
      }
      break;
#endif

#if (USE_CUSTOM_MOTION_SENSOR_ISM6HG256X_0 == 1)
    case CUSTOM_ISM6HG256X_0:
      if (ISM6HG256X_FIFO_Get_All_Status(MotionCompObj[Instance], Status) != BSP_ERROR_NONE)
      {
        ret = BSP_ERROR_COMPONENT_FAILURE;
      }
      else
      {
        ret = BSP_ERROR_NONE;
      }
      break;
#endif

    default:
      ret = BSP_ERROR_WRONG_PARAM;
      break;
  }

  return ret;
}

/**
  * @brief  Get the ISM6HG256X FIFO all status
  * @param  pObj the device pObj
  * @param  Status FIFO register content
  * @retval 0 in case of success, an error code otherwise
  */
int32_t ISM6HG256X_FIFO_Get_All_Status(ISM6HG256X_Object_t *pObj, MY_ISM6HG256X_Fifo_Status_t *Status)
{
  ism6hg256x_reg_t reg;

  if (ism6hg256x_read_reg(&(pObj->Ctx), ISM6HG256X_FIFO_STATUS1, &reg.byte, 1) != ISM6HG256X_OK)
  {
    return ISM6HG256X_ERROR;
  }

  if (ism6hg256x_read_reg(&(pObj->Ctx), ISM6HG256X_FIFO_STATUS2, &reg.byte, 1) != ISM6HG256X_OK)
  {
    return ISM6HG256X_ERROR;
  }

  Status->FifoWatermark = reg.fifo_status2.fifo_wtm_ia;
  Status->FifoFull = reg.fifo_status2.fifo_full_ia;
  Status->FifoOverrun = reg.fifo_status2.fifo_ovr_ia;
  Status->CounterBdr = reg.fifo_status2.counter_bdr_ia;
  Status->FifoOverrunLatched = reg.fifo_status2.fifo_ovr_latched;

  return ISM6HG256X_OK;
}

/**
 * @brief  Get number of unread FIFO samples
 * @param  Instance the device instance
 * @param  NumSamples number of unread FIFO samples
 * @retval BSP status
 */
int32_t MY_CUSTOM_MOTION_SENSOR_FIFO_Get_Num_Samples(uint32_t Instance, uint16_t *NumSamples)
{
  int32_t ret;

  switch (Instance)
  {
#if (USE_CUSTOM_MOTION_SENSOR_ISM330DHCX_0 == 1)
    case CUSTOM_ISM330DHCX_0:
      if (ISM330DHCX_FIFO_Get_Num_Samples(MotionCompObj[Instance], NumSamples) != BSP_ERROR_NONE)
      {
        ret = BSP_ERROR_COMPONENT_FAILURE;
      }
      else
      {
        ret = BSP_ERROR_NONE;
      }
      break;
#endif

#if (USE_CUSTOM_MOTION_SENSOR_LSM6DSO32X_0 == 1)
    case CUSTOM_LSM6DSO32X_0:
      if (LSM6DSO32X_FIFO_Get_Num_Samples(MotionCompObj[Instance], NumSamples) != BSP_ERROR_NONE)
      {
        ret = BSP_ERROR_COMPONENT_FAILURE;
      }
      else
      {
        ret = BSP_ERROR_NONE;
      }
      break;
#endif

#if (USE_CUSTOM_MOTION_SENSOR_ISM6HG256X_0 == 1)
    case CUSTOM_ISM6HG256X_0:
      if (ISM6HG256X_FIFO_Get_Num_Samples(MotionCompObj[Instance], NumSamples) != BSP_ERROR_NONE)
      {
        ret = BSP_ERROR_COMPONENT_FAILURE;
      }
      else
      {
        ret = BSP_ERROR_NONE;
      }
      break;
#endif

    default:
      ret = BSP_ERROR_WRONG_PARAM;
      break;
  }

  return ret;
}
