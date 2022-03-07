/*
 * gpio.c
 *
 *  Created on: Jan 7, 2022
 *      Author: Nguyen Huy Duc
 */

#include "gpio.h"


void GPIO_Init(GPIO_TypeDef *GPIOx, uint8_t pin, uint8_t mode, uint8_t config)
{
	volatile uint32_t *CR;
	if(pin <= 7)
	{
		CR = &(GPIOx->CRL);
	}
	else
	{
		CR = &(GPIOx->CRH);
		pin -= 8;
	}
	//Enable clock
	if(GPIOx == GPIOA)
	{
		RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	}
	else if(GPIOx == GPIOB)
	{
		RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
	}
	else
	{
		RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
	}
	//Mode and configure
	*CR &= ~(1<< (4*pin + 2)); //Reset all bits
	*CR |= (mode << (4*pin)) | (config << (4*pin + 2));
}

void GPIO_WritePin(GPIO_TypeDef *GPIOx, uint8_t pin, bool state)
{
	if(state)
	{
		GPIOx->ODR |= 1<<pin;
	}
	else
	{
		GPIOx->BRR |= 1<<pin;
	}
}

void GPIO_TogglePin(GPIO_TypeDef *GPIOx, uint8_t pin)
{
	GPIOx->ODR ^= 1<<pin;
}

bool GPIO_ReadPin(GPIO_TypeDef *GPIOx, uint8_t pin)
{
	if((GPIOx->IDR>>pin) & 1)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
