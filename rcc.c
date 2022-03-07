	/*
 * rcc.c
 *
 *  Created on: Jan 7, 2022
 *      Author: Nguyen Huy Duc
 */

#include "rcc.h"

//Milisecond ticks
static __IO uint32_t msTicks=0;

/**
 * @brief HSE System clock configuration
 */
void RCC_HSE_Config(void)
{
  /*
   * Configuration paramters
   *
   * HSE = 8MHz
   * PLL_M = 9
   * USB prescalar = 1.5
   * AHB prescalar = 1
   * Cortex precalar = 1
   * --> 72MHz System Clock
   *
   * APB1 prescalar = 2  --> 36, 72 MHz
   * APB2 prescalar = 1  --> 36, 36 MHz
   * ADC prescalr = 6    --> 12MHz
   */
	//PLL Configuration
	RCC->CFGR |= RCC_CFGR_PLLMULL9; //PLL input clock x 9 (PLL_M = 9)
	//USB prescaler = 1.5
	RCC->CFGR |= RCC_CFGR_USBPRE;
	/*HSE Oscillator*/
	//Enable HSE Oscillator
	RCC->CR |= RCC_CR_HSEON;
	//Wait for it to stabilize
	while((RCC->CR & RCC_CR_HSERDY) == 0);
	//Select HSE as PLL source
	RCC->CFGR |= RCC_CFGR_PLLSRC;
	//Enable PLL
	RCC->CR |= RCC_CR_PLLON;
	//Wait for PLL ready
	while(!(RCC->CR & RCC_CR_PLLRDY));

	/*Flash prefetch and wait state
	 * with SYSCLOCK is 72MHz,if MCU want to access Flash memory, it must wait for Flash response
	 * because clock of FLASH is slower than 72MHz
	 * */
	//SYSCLOCK = 72MHz <-> Two wait states
	FLASH->ACR |= FLASH_ACR_LATENCY_1;
	//Enable prefetch buffer
	FLASH->ACR |= FLASH_ACR_PRFTBE;

	/*Select PLL as main system clock*/
	RCC->CFGR |= RCC_CFGR_SW_PLL;
	//Wait for PLL to be the active clk source
	while((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_1);

	//AHB prescaler = 1
	RCC->CFGR |= RCC_CFGR_HPRE_DIV1;
	//APB1 prescaler = 2
	RCC->CFGR |= RCC_CFGR_PPRE1_DIV2;
	//APB2 prescaler = 1
	RCC->CFGR |= RCC_CFGR_PPRE2_DIV1;
	//ADC prescaler = 6
	RCC->CFGR |= RCC_CFGR_ADCPRE_DIV6;
}

/**
 * @brief SysTick configuration
 */
void RCC_SysTick_Config(uint32_t arr)
{
  SysTick->CTRL = 0;
  SysTick->LOAD = arr-1;
  NVIC_SetPriority(SysTick_IRQn, 0);

  SysTick->VAL = 0;
  SysTick->CTRL |= SysTick_CTRL_CLKSOURCE_Msk;
  SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk;
  SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
}


//static void SysTick_Handler(void)
//{
//  NVIC_ClearPendingIRQ(SysTick_IRQn);
//  msTicks++;
//}

/**
 * @brief Milisecond Delay and Get Ticks
 */
void RCC_DelayMs(uint32_t ms)
{
  uint32_t startTicks = RCC_GetTicks();
  while((RCC_GetTicks() - startTicks) < ms);
}

/**
 *  @brief Get Tick
 */
uint32_t RCC_GetTicks(void)
{
  return msTicks;
}

/**
 * @brief Inc Tick
 */
void IncTick(void)
{
  msTicks++;
}
