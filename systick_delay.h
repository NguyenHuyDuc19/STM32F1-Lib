#ifndef _SYSTICK_DELAY_H_
#define _SYSTICK_DELAY_H_

#include <stdint.h>
#include "stm32f10x.h"


void SysTick_Handler(void);
void delayMs(int ms);
void delayUs(int us);
void systick_config(void);


#endif
