#ifndef _SPI_H_
#define _SPI_H_

#include "stm32f10x.h"
#include "gpio.h"
#include "systick_delay.h"


typedef enum
{
	DIV_2 = 0,
	DIV_4,
	DIV_8,
	DIV_16,
	DIV_32,
	DIV_64,
	DIV_128,
	DIV_256
} Baudrate_t;

void SPI_Init(SPI_TypeDef *SPI_num, Baudrate_t Baudrate);

void SPI_Receive(SPI_TypeDef *SPI_num, uint8_t *data, size_t length);
void SPI_Transmit(SPI_TypeDef *SPI_num, uint8_t *data, size_t length);
#endif
