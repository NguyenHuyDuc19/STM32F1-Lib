#include "systick_delay.h"

uint32_t tick;



void SysTick_Handler(void)
{
	tick++;
}

void delayMs(int ms)
{
	SysTick_Config(SystemCoreClock /1000); //Configure SysTick to generate an interrupt every millisecond
	tick = 0;
	while(tick < ms);
}


void delayUs(int us)
{
	SysTick_Config(SystemCoreClock /1000000); //Configure SysTick to generate an interrupt every microsecond
	tick = 0;
	while(tick < us);
}


