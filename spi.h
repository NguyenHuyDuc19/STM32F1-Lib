#ifndef _SPI_H_
#define _SPI_H_

#include "stm32f1xx.h"
#include "gpio.h"


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
} BR_SPI_t;

void SPI_Init(SPI_TypeDef *SPIx, BR_SPI_t Baudrate);

//void SPI_Receive(SPI_TypeDef *SPIx, uint8_t *data, uint32_t length);
void SPI_Transmit(SPI_TypeDef *SPIx, uint8_t *data, uint32_t length);
void SPI_CS(SPI_TypeDef *SPIx, uint8_t LOW_HIGH);
char SPI_RX(SPI_TypeDef *SPIx, char value);
#endif
