/*
 * uart.h
 *
 *  Created on: Jan 7, 2022
 *      Author: Nguyen Huy Duc
 */

#ifndef INC_UART_H_
#define INC_UART_H_

#include "stm32f1xx.h"
#include "stdint.h"
#include "stdbool.h"

#include "gpio.h"
#include "rcc.h"

/**
 *  @brief UART Baudrate
 */
typedef enum
{
	USART1_BR_2400		=	0x753,
	USART1_BR_9600 		= 	0x1D4C,
	USART1_BR_115200		= 	0x271,

	USART2_BR_2400	 	=	0x3A98,
	USART2_BR_9600 		= 	0xEA6,
	USART2_BR_115200 	= 	0x138,

	USART3_BR_2400		=	0x3A98,
	USART3_BR_9600 		= 	0xEA6,
	USART3_BR_115200 	=	0x138
}USART_BR_t;

/**
 *  @brief UART Peripheral Initialization
 */
void USART_Init(USART_TypeDef *USARTx, USART_BR_t Baudrate);

/**
 *  @brief UART Transmit
 */
bool USART_Transmit(USART_TypeDef *USARTx, uint8_t *data, uint32_t length, uint32_t timeout);

/**
 *  @brief UART Receive
 */
bool USART_Receive(USART_TypeDef *USARTx, uint8_t *data, uint32_t length, uint32_t timeout);

#endif /* INC_UART_H_ */

