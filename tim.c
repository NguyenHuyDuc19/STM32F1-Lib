/*
 * tim.c
 *
 *  Created on: Jan 7, 2022
 *      Author: Nguyen Huy Duc
 */

#include "tim.h"

/**
 *  @brief	TIM Initialization
 */
void TIM_DelayInit(void)
{
	//Enable TIM4 clock
	RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;
	//Set prescaler value
	TIM4->PSC = 0;
	//Set ARR value
	TIM4->ARR = 7200-1;
	//One-pulse mode
	TIM4->CR1 |= TIM_CR1_OPM; //Counter stops counting at the next update event (clearing the bit CEN)
	//Update registers on event
	TIM4->EGR |= TIM_EGR_UG;
	//Start timer
	TIM4->CR1 |= TIM_CR1_CEN;
}

/**
 *  @brief Milli Second Delay - TIM4
 */
void TIM_DelayMs(uint32_t ms)
{
	//Set the PSC value
	TIM4->PSC = (ms*10) - 1;
	//Start TIM4
	TIM4->CR1 |= TIM_CR1_CEN;
	//Wait for delay to elapse
	while(!(TIM4->SR & TIM_SR_UIF));
	//Clear TIM flag
	TIM4->SR &= ~TIM_SR_UIF;
}

/**
 * @brief Micro Second Delay - TIM4
 */
void TIM_DelayUs(uint32_t us)
{
	//Set ARR value
	TIM4->ARR = 72-1;
	//Set the PSC value
	TIM4->PSC = us - 1;
	//Start TIM4
	TIM4->CR1 |= TIM_CR1_CEN;
	//Wait for delay to elapse
	while(!(TIM4->SR & TIM_SR_UIF));
	//Clear TIM flag
	TIM4->SR &= ~TIM_SR_UIF;
}
