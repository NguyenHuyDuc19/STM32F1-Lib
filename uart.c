/*
 * uart.c
 *
 *  Created on: Jan 7, 2022
 *      Author: Nguyen Huy Duc
 */

#include "uart.h"

/**
 * 	@brief UART Initialization
 */
void USART_Init(USART_TypeDef *USARTx, USART_BR_t Baudrate)
{
	if(USARTx == USART1)
	{
		//Enable the USART1 clock
		RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
		//Config pin A9  - TXD
		GPIO_Init(GPIOA, 9, OUT_HIGH, AF_PP);
		//Config pin A10 - RXD
		GPIO_Init(GPIOA, 10, IN, PU_PD);
	}
	else if(USARTx == USART2)
	{
		//Enable the USART2 clock
		RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
		//Config pin A2  - TXD
		GPIO_Init(GPIOA, 2, OUT_HIGH, AF_PP);
		//Config pin A3 - RXD
		GPIO_Init(GPIOA, 3, IN, PU_PD);
	}
	else if(USARTx == USART3)
	{
		//Enable the USART clock
		RCC->APB1ENR |= RCC_APB1ENR_USART3EN;
		//Config pin B10  - TXD
		GPIO_Init(GPIOB, 10, OUT_HIGH, AF_PP);
		//Config pin B11 - RXD
		GPIO_Init(GPIOB, 11, IN, PU_PD);
	}
	//Select the desired baud rate
	USARTx->BRR = Baudrate;

	USARTx->CR1 |= USART_CR1_TE		//Transmitter enable
				| USART_CR1_RE		//Receiver enable
				| USART_CR1_UE;  	//USART enable

}

/**
 *  @brief UART Transmit
 */
bool USART_Transmit(USART_TypeDef *USARTx, uint8_t *data, uint32_t length, uint32_t timeout)
{
	uint32_t i;
	uint32_t startTick = RCC_GetTicks();

	for(i = 0; i < length; i++)
	{
		//Transmit data register empty
		if(USARTx->SR & USART_SR_TXE)
		{
			USARTx->DR = data[i];
		}
		else
		{
			//Manage timeout
			if((RCC_GetTicks() - startTick) > timeout) return  false;
		}
		//Wait for transmission a frame is complete
		while(!(USARTx->SR & USART_SR_TC))
		{
			if((RCC_GetTicks() - startTick) > timeout) return  false;
		}
	}
	return true;
}

/**
 *  @brief UART Receive
 */
bool UART_Receive(USART_TypeDef *USARTx, uint8_t *data, uint32_t length, uint32_t timeout)
{
	uint32_t startTick = RCC_GetTicks();
	uint32_t i;

	//Received data is ready to be read
	if(USARTx->SR & USART_SR_RXNE)
	{
		for(i = 0; i < length; i++)
		{
			data[i] = USARTx->DR;
		}
	}
	else
	{
		if((RCC_GetTicks() - startTick) > timeout) return false;
	}
	return true;
}
