/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    usart.c
  * @brief   This file provides code for the configuration
  *          of the USART instances.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "usart.h"

/* USER CODE BEGIN 0 */


void uart2_pin_conf()
{
						/****************************GPIO*****************************/

	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;		//Enable GPIOD Clock  PD5/PD6

	GPIOB->MODER |= (2<<20);			//Bits (21:20) = 1:0 --> Alternate function for Pin PB10
	GPIOB->MODER |= (2<<22);			//Bits (23:22) = 1:0 --> Alternate function for Pin PB11

	GPIOB->OSPEEDR |= (3<<20) | (3<<22);   //Bits (21:20)=(1:1) & Bits(23:22)=(1:1) -->> High speed for PIN PB10 & PB11

	GPIOB->AFR[0] |= (7<<8);	//Bytes (11:10:09:08) = 0:1:1:1 --> AF7 Alternate function for USART2 at pin PB10
	GPIOB->AFR[0] |= (7<<12);	//Bytes (15:14:13:12) = 0:1:1:1 --> AF7 Alternate function for USART2 at pin PB11

							/******************* USART ***********************/

	RCC->APB1ENR |= RCC_APB1ENR_USART3EN;		//Enable UART2 Clock

	//Program for 8bit	(M Word length)
	USART3->CR1 |= ~(1<<12);

	//Program for BaudRate 115200,PCLK 45Mhz
	USART3->BRR = (7<<0) | (24<<4);

	//	uart_set_baudrate(USART2,APB1_CLK,UART_BAUDRATE);

	//Enable the Tx/Rx
	USART3->CR1 = (1<<2);	//Recevier Enable	PD6
	USART3->CR1 = (1<<3);	//Transmiter Enable	PD5

	//Enable the USART
	USART3->CR1 = 0x00;	//Clear All
	USART3->CR1 = (1<<13);	//UE = 1  Enable USART

}


void UART2_SendChar(USART_TypeDef* USARTx, uint8_t ch)
{
  while(!(USARTx->SR & USART_SR_TXE));
  USARTx->DR = ch;
}

void UART2_SendChar_float(USART_TypeDef* USARTx, float ch)
{
  while(!(USARTx->SR & USART_SR_TXE));
  USARTx->DR = ch;
}

uint32_t HART_USART_IsActiveFlag_TXE(USART_TypeDef *USARTx)
{
  return (READ_BIT(USARTx->SR, USART_SR_TXE) == (USART_SR_TXE));
}

void HART_USART_TransmitData8(USART_TypeDef *USARTx, uint32_t Value)
{
  USARTx->DR = Value;
}

uint32_t HART_USART_IsActiveFlag_TC(USART_TypeDef *USARTx)
{
  return (READ_BIT(USARTx->SR, USART_SR_TC) == (USART_SR_TC));
}

/* USER CODE END 0 */

UART_HandleTypeDef huart3;

/* USART3 init function */

void MX_USART3_UART_Init(void)
{

  /* USER CODE BEGIN USART3_Init 0 */

  /* USER CODE END USART3_Init 0 */

  /* USER CODE BEGIN USART3_Init 1 */

  /* USER CODE END USART3_Init 1 */
  huart3.Instance = USART3;
  huart3.Init.BaudRate = 115200;
  huart3.Init.WordLength = UART_WORDLENGTH_8B;
  huart3.Init.StopBits = UART_STOPBITS_1;
  huart3.Init.Parity = UART_PARITY_NONE;
  huart3.Init.Mode = UART_MODE_TX_RX;
  huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart3.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART3_Init 2 */

  /* USER CODE END USART3_Init 2 */

}

void HAL_UART_MspInit(UART_HandleTypeDef* uartHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(uartHandle->Instance==USART3)
  {
  /* USER CODE BEGIN USART3_MspInit 0 */

  /* USER CODE END USART3_MspInit 0 */
    /* USART3 clock enable */
    __HAL_RCC_USART3_CLK_ENABLE();

    __HAL_RCC_GPIOD_CLK_ENABLE();
    /**USART3 GPIO Configuration
    PD8     ------> USART3_TX
    PD9     ------> USART3_RX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_9;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF7_USART3;
    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /* USER CODE BEGIN USART3_MspInit 1 */

  /* USER CODE END USART3_MspInit 1 */
  }
}

void HAL_UART_MspDeInit(UART_HandleTypeDef* uartHandle)
{

  if(uartHandle->Instance==USART3)
  {
  /* USER CODE BEGIN USART3_MspDeInit 0 */

  /* USER CODE END USART3_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART3_CLK_DISABLE();

    /**USART3 GPIO Configuration
    PD8     ------> USART3_TX
    PD9     ------> USART3_RX
    */
    HAL_GPIO_DeInit(GPIOD, GPIO_PIN_8|GPIO_PIN_9);

  /* USER CODE BEGIN USART3_MspDeInit 1 */

  /* USER CODE END USART3_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
