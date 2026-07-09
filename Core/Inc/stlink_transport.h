/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : stlink_transport.h
  * @brief          : header file
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
/* USER CODE END Header */

#ifndef STLINK_TRANSPORT_H
#define STLINK_TRANSPORT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32u5xx_hal.h"
#include <stdint.h>

extern UART_HandleTypeDef hstlink_uart;

void STLINK_Transport_Init(void);
uint8_t STLINK_Transport_Transmit(uint8_t *buf, uint16_t len);

#ifdef __cplusplus
}
#endif

#endif /* STLINK_TRANSPORT_H */

