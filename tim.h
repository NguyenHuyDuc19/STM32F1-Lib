/*
 * tim.h
 *
 *  Created on: Jan 7, 2022
 *      Author: Nguyen Huy Duc
 */

#ifndef INC_TIM_H_
#define INC_TIM_H_

#include "stm32f1xx.h"

/**
 *  @brief	TIM Initialization
 */
void TIM_DelayInit(void);

/**
 *  @brief Milli Second Delay - TIM4
 */
void TIM_DelayMs(uint32_t ms);

/**
 * @brief Micro Second Delay - TIM4
 */
void TIM_DelayUs(uint32_t us);

#endif /* INC_TIM_H_ */
