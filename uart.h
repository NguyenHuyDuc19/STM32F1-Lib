#ifndef _UART_H_
#define _UART_H_

#include "stm32f10x.h"
#include "gpio.h"
#include "systick_delay.h"

typedef enum 
{
	BR_USART1_2400 	=		0x753,
	BR_USART1_9600 	= 	0x1D4C,
	BR_USART1_115200 = 	0x271,
	
	BR_USART2_2400	 	=		0x3A98,
	BR_USART2_9600 	= 	0xEA6,
	BR_USART2_115200 = 	0x138,
	
	BR_USART3_2400		=		0x3A98,
	BR_USART3_9600 	= 	0xEA6,
	BR_USART3_115200 = 	0x138
	
} Baudrate_t;

void USART_Init(USART_TypeDef *USART_num, Baudrate_t Baudrate);
void USART_Transmit(USART_TypeDef *USART_num, uint8_t *data, uint32_t length);
void USART_Receive(USART_TypeDef *USART_num, uint8_t *data, uint32_t length);

#endif
