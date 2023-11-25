/*
 * uart_apc.h
 *
 *  Created on: Nov 7, 2022
 *      Author: rajdeep
 */

#ifndef INC_UART_APC_H_
#define INC_UART_APC_H_

#include "stm32f429xx.h"

//extern UART_HandleTypeDef huart3;

void uart3_pin_conf();
void USART_write(int ch);

#endif /* INC_UART_APC_H_ */
