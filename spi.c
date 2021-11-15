#include "spi.h"

void SPI_Init(SPI_TypeDef *SPI_num, Baudrate_t Baudrate)
{
	if(SPI_num == SPI1)
	{
		RCC->APB2ENR |= RCC_APB2ENR_SPI1EN; //SPI1 clock enable
		
		//GPIO Config
		GPIO_Init(GPIOA, 4, OUT_HIGH, GP_PP); 	//PA4 - SPI1_NSS
		GPIO_Init(GPIOA, 5, OUT_HIGH, AF_PP); 	//PA5 - SPI1_SCK
		GPIO_Init(GPIOA, 6, IN, PU_PD); 				//PA6 - SPI1_MISO
		GPIO_Init(GPIOA, 7, OUT_HIGH, AF_PP);		//PA7 - SPI1_MOSI
		GPIO_WritePin(GPIOA, 4, 1); 						//Pull up chip select pin - PA4
	}
	else if(SPI_num == SPI2)
	{
		RCC->APB1ENR |= RCC_APB1ENR_SPI2EN; //SPI2 clock enable
		
		//GPIO Config
		GPIO_Init(GPIOB, 12, OUT_HIGH, GP_PP); 	//PA4 - SPI1_NSS
		GPIO_Init(GPIOB, 13, OUT_HIGH, AF_PP); 	//PA5 - SPI1_SCK
		GPIO_Init(GPIOB, 14, IN, PU_PD); 				//PA6 - SPI1_MISO
		GPIO_Init(GPIOB, 15, OUT_HIGH, AF_PP);	//PA7 - SPI1_MOSI
		GPIO_WritePin(GPIOB, 12, 1); 						//Pull up chip select pin - PA4
	}
	SPI_num->CR1 |= Baudrate<<3	//Baund rate
						| SPI_CR1_SSM //Software slave management
						| SPI_CR1_SSI //Internal slave select
						| SPI_CR1_MSTR; //Master configuration
	SPI_num->CR1 &= ~(1 | 1<<1);
	SPI_num->CR2 |= SPI_CR2_SSOE; //SS output enable
	SPI_num->CR1 |= SPI_CR1_SPE;
}

void Start_Transmitting(SPI_TypeDef *SPI_num)
{
	if(SPI_num == SPI1)
	{
		GPIO_WritePin(GPIOA, 4, 0);
	}
	else if(SPI_num == SPI2)
	{
		GPIO_WritePin(GPIOB, 12, 0);
	}
}

void Stop_Transmitting(SPI_TypeDef *SPI_num)
{
	while(SPI_num->SR & SPI_SR_BSY);
	while(!(SPI_num->SR & SPI_SR_TXE));
	if(SPI_num == SPI1)
	{
		GPIO_WritePin(GPIOA, 4, 1);
	}
	else if(SPI_num == SPI2)
	{
		GPIO_WritePin(GPIOB, 12, 1);
	}
}


void SPI_Transmit(SPI_TypeDef *SPI_num, uint8_t *data, size_t length)
{
	Start_Transmitting(SPI_num); //Start transmitting
	
	for(size_t i = 0; i < length; i++)
	{
		SPI_num->DR = data[i];
		while(SPI_num->SR & SPI_SR_BSY);
		while(!(SPI_num->SR & SPI_SR_TXE));
	}
	
	Stop_Transmitting(SPI_num); //Stop transmitting
}
void SPI_Receive(SPI_TypeDef *SPI_num, uint8_t *data, size_t length)
{
	while(!(SPI_num->SR & SPI_SR_RXNE)); //Wait till RX buffer not emty
	
	for(size_t i; i<length; i++)
	{
		data[i] = SPI_num->DR;
		while((SPI_num->SR & SPI_SR_RXNE)); //Wait till RX buffer emty
	}
	
}