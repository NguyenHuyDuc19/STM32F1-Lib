/*
 * rcc.h
 *
 *  Created on: Jan 7, 2022
 *      Author: Nguyen Huy Duc
 */

#ifndef INC_RCC_H_
#define INC_RCC_H_

#include "stm32f1xx.h"

/**
 * @brief HSE System clock configuration
 */
void RCC_HSE_Config(void);

/**
 * @brief SysTick configuration
 */
void RCC_SysTick_Config(uint32_t arr);

/**
 * @brief Milisecond Delay and Get Ticks
 */
void RCC_DelayMs(uint32_t ms);
uint32_t RCC_GetTicks(void);

/**
 * @brief Increase Tick
 */
void IncTick(void);

#endif /* INC_RCC_H_ */
