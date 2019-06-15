/*
 * SPI.c
 */

#include "SPI.h"

//SPI1 inicialization
void SPI1Init(){

	//Configure NSS hardware pin
	SPI1 -> CR1 	&= ~(SPI_CR1_SSM);
	SPI1 -> CR2 	|= SPI_CR2_SSOE;

	//Configure clock polarity sample at positive clock edge
	SPI1 -> CR1 	&= ~(SPI_CR1_CPHA);
	SPI1 -> CR1 	&= ~(SPI_CR1_CPOL);

	//MSB bit first out
	SPI1 -> CR1 	&= ~(SPI_CR1_LSBFIRST);

	//2-line SPI mode (MISO & MOSI)
	SPI1 -> CR1 	&= ~(SPI_CR1_BIDIMODE);

	//SPI full duplex mode
	SPI1 -> CR1 	&= ~(SPI_CR1_RXONLY);

	//SPI 8-bit data frame format
	SPI1 -> CR1 	&= ~(SPI_CR1_DFF);

	//SPI baud rate without prescaler the sclk clock would be 42 MHz
	//SPI1 -> CR1 	|= ~(SPI_CR1_BR); 	// 84 MHz / 2 = 42 MHz
	SPI1 -> CR1 	|= (SPI_CR1_BR_1 |  SPI_CR1_BR_0); 	// 84 MHz / 16 = 5.25 MHz
	//SPI1 -> CR1 	|= SPI_CR1_BR; 		// 84 MHz / 256 = 328 kHz (only in test version)

	//SPI in master mode configuration
	SPI1 -> CR1 	|= SPI_CR1_MSTR;

	//SPI enable
	SPI1 -> CR1 	|= SPI_CR1_SPE;
}

//SPI1 send 8-bit data
void SPI1Send8Bit(uint8_t *data){

	 //SPI1 CS enable (output low logical level)
	 GPIOA -> ODR 		&= ~(GPIO_ODR_ODR_4);

	 //Write 8 bit data in to SPI1 data buffer register
	 SPI1 -> DR 	= *data;

	 //wait till SPI1 are sending data "busy state"
	 while(SPI1 -> SR & SPI_SR_BSY);

	 //SPI1 CS disable (output high logical level)
	 GPIOA -> ODR 		|= GPIO_ODR_ODR_4;
}

//SPI3 send n-byte
void SPI1SendNByte(uint8_t *data,uint8_t data_len){

	 uint8_t i = 0;

	 //SPI1 CS enable (output low logical level)
	 GPIOA -> ODR 		&= ~(GPIO_ODR_ODR_4);

	 for(i = 0;i < data_len;i++){

		 //Write 8 bit data in to SPI1 data buffer register
		 SPI1 -> DR 	= *(data+i);

		 //Wait until SPI1 data buffer register is empty
		 while(!(SPI1 -> SR & SPI_SR_TXE));

	 }
	 //wait till SPI1 are sending data "busy state"
	 while(SPI1 -> SR & SPI_SR_BSY);

	 //SPI1 CS disable (output high logical level)
	 GPIOA -> ODR 		|= GPIO_ODR_ODR_4;

}

//SPI3 initialization
void SPI3Init(){

	//Configure NSS hardware pin
	SPI3 -> CR1 	&= ~(SPI_CR1_SSM); 		//Use hardware controlled chip select line
	SPI3 -> CR2		|= SPI_CR2_SSOE; 		//Use hardware output chip select that was active in low state

	//Configure clock polarity sample at positive edge of clock
	SPI3 -> CR1 	&= ~(SPI_CR1_CPHA);
	SPI3 -> CR1 	|= SPI_CR1_CPOL;

	//MSB bit first out
	SPI3 -> CR1 	&= ~(SPI_CR1_LSBFIRST);

	//2-line SPI mode (MISO & MOSI)
	SPI3 -> CR1 	&= ~(SPI_CR1_BIDIMODE);

	//SPI full duplex mode
	SPI3 -> CR1 	&= ~(SPI_CR1_RXONLY);

	//SPI 8-bit data frame format
	SPI3 -> CR1 	&= ~(SPI_CR1_DFF);

	//SPI baud rate without prescaler the sclk clock would be 42 MHz
	SPI3 -> CR1 	|= SPI_CR1_BR_0; 	// 42 MHz / 4 = 10,5 MHz

	//SPI in master mode configuration
	SPI3 -> CR1 	|= SPI_CR1_MSTR;

	//SPI enable
	//SPI3 -> CR1 	|= SPI_CR1_SPE;

}
