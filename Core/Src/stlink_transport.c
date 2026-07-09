/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : stlink_transport.c
  * @brief          : source file
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

#include "stlink_transport.h"

#include "app_ai_inertial.h"
#include "main.h"

UART_HandleTypeDef hstlink_uart;

static uint8_t stlink_rx_byte;

static void STLINK_RecoverReception(UART_HandleTypeDef *huart)
{
  __HAL_UART_CLEAR_FLAG(huart, UART_CLEAR_PEF | UART_CLEAR_FEF | UART_CLEAR_NEF | UART_CLEAR_OREF);
  __HAL_UART_SEND_REQ(huart, UART_RXDATA_FLUSH_REQUEST);
  huart->ErrorCode = HAL_UART_ERROR_NONE;
  huart->RxState = HAL_UART_STATE_READY;
}

static void STLINK_StartReception(void)
{
  HAL_StatusTypeDef status = HAL_UART_Receive_IT(&hstlink_uart, &stlink_rx_byte, 1);

  if (status == HAL_OK || status == HAL_BUSY)
  {
    return;
  }

  STLINK_RecoverReception(&hstlink_uart);
  (void)HAL_UART_Receive_IT(&hstlink_uart, &stlink_rx_byte, 1);
}

static void STLINK_ProcessReceivedByte(uint8_t byte)
{
  static uint8_t terminator_detected = 0U;
  uint32_t command_length;

  if (command_buffer_ptr == NULL || command_buffer_write_ptr == NULL)
  {
    return;
  }

  command_length = (uint32_t)(command_buffer_write_ptr - command_buffer_ptr);

  if (terminator_detected == 0U)
  {
    if (byte == '\r')
    {
      if (command_length == 0U)
      {
        return;
      }

      terminator_detected = 1U;
      return;
    }

    if (command_length == 0U)
    {
      if (byte != '{')
      {
        return;
      }

      *command_buffer_ptr = '\0';
      command_buffer_write_ptr = command_buffer_ptr;
    }

    if (command_length < (COMMAND_BUFFER_SIZE - 1U))
    {
      *command_buffer_write_ptr++ = (char)byte;
      *command_buffer_write_ptr = '\0';
    }
    return;
  }

  terminator_detected = 0U;
  if (byte == '\n')
  {
    if ((uint32_t)(command_buffer_write_ptr - command_buffer_ptr) > 0U)
    {
      command_received = true;
    }
  }
}

void STLINK_Transport_Init(void)
{
  hstlink_uart.Instance = USART1;
  hstlink_uart.Init.BaudRate = 9600;
  hstlink_uart.Init.WordLength = UART_WORDLENGTH_8B;
  hstlink_uart.Init.StopBits = UART_STOPBITS_1;
  hstlink_uart.Init.Parity = UART_PARITY_NONE;
  hstlink_uart.Init.Mode = UART_MODE_TX_RX;
  hstlink_uart.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  hstlink_uart.Init.OverSampling = UART_OVERSAMPLING_16;
  hstlink_uart.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  hstlink_uart.Init.ClockPrescaler = UART_PRESCALER_DIV1;
  hstlink_uart.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;

  if (HAL_UART_Init(&hstlink_uart) != HAL_OK)
  {
    Error_Handler();
  }

  STLINK_StartReception();
}

uint8_t STLINK_Transport_Transmit(uint8_t *buf, uint16_t len)
{
  return (HAL_UART_Transmit(&hstlink_uart, buf, len, HAL_MAX_DELAY) == HAL_OK) ? 0U : 1U;
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  if (huart == &hstlink_uart)
  {
    STLINK_ProcessReceivedByte(stlink_rx_byte);
    STLINK_StartReception();
  }
}

void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart)
{
  if (huart == &hstlink_uart)
  {
    STLINK_RecoverReception(huart);
    STLINK_StartReception();
  }
}

int __io_putchar(int ch)
{
  uint8_t c = (uint8_t)ch;
  return (HAL_UART_Transmit(&hstlink_uart, &c, 1U, HAL_MAX_DELAY) == HAL_OK) ? ch : EOF;
}

int __io_getchar(void)
{
  uint8_t c = 0U;
  return (HAL_UART_Receive(&hstlink_uart, &c, 1U, HAL_MAX_DELAY) == HAL_OK) ? (int)c : EOF;
}

