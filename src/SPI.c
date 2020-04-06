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



	//SPI baud rate for debug purpose
	//SPI1 -> CR1 	|= (SPI_CR1_BR_1 |  SPI_CR1_BR_0); 	// 84 MHz / 16 = 5.25 MHz good for saleale debuging !!
	//SPI1 -> CR1 	|= ( SPI_CR1_BR_0); 				// 84 MHz / 4 = 21 MHz
	SPI1 -> CR1 	&= ~( SPI_CR1_BR_2 | SPI_CR1_BR_1 | SPI_CR1_BR_0); 				// 84 MHz / 2 = 42 MHz
	//SPI1 -> CR1 	|= SPI_CR1_BR; 		// 84 MHz / 256 = 328 kHz (only in test version)

	//SPI baud rate without prescaler the sclk clock would be 42 MHz
	//SPI1 -> CR1 	|= ~(SPI_CR1_BR); 	// 84 MHz / 2 = 42 MHz


	//SPI in master mode configuration
	SPI1 -> CR1 	|= SPI_CR1_MSTR;

	//SPI enable
	SPI1 -> CR1 	|= SPI_CR1_SPE;
}

//SPI1 send 1 byte receive 1 byte
uint8_t SPI1Send1ByteReceive1Byte(uint8_t *data){

	 //send 8 bit data
	 SPI1 -> DR = *data;

	 //Wait until SPI1 data buffer register is empty
	 while(!(SPI1 -> SR & SPI_SR_TXE));

	 //wait until SPI1 receive buffer is not empty
	 while(!(SPI1 -> SR & SPI_SR_RXNE));

	 //wait till SPI1 are sending data "busy state"
	 while(SPI1 -> SR & SPI_SR_BSY);

	 //return received data
	 return SPI1 -> DR;
}

//SPI1 send n-byte
void SPI1SendNByte(uint8_t *data,uint32_t data_len){

	 //variable for count
	 uint32_t i = 0;

	 //SPI1 CS enable (output low logical level)
	 GPIOA -> ODR 		&= ~(GPIO_ODR_ODR_4);

	 for(i = 0;i < data_len;i++){

		 //Write 8 bit data
		 SPI1Send1ByteReceive1Byte(&(data[i]));
	 }

	 //SPI1 CS disable (output high logical level)
	 GPIOA -> ODR 		|= GPIO_ODR_ODR_4;

}

//SPI1 send n bytes and receive 1-Byte
uint8_t SPI1SendNByteReceive1Byte(uint8_t *data_to_send, uint32_t send_data_len){

	 //variable for count
	 uint32_t i = 0;

	 //Received data variable
	 uint8_t received_data = 0x00;

	 //SPI1 CS enable (output low logical level)
	 GPIOA -> ODR 		&= ~(GPIO_ODR_ODR_4);

	 for(i = 0;i < send_data_len;i++){
		 //Send data
		 SPI1Send1ByteReceive1Byte(&data_to_send[i]);
	 }
	 received_data = SPI1Send1ByteReceive1Byte(&data_to_send[i]);

	 //SPI1 CS disable (output high logical level)
	 GPIOA -> ODR 		|= GPIO_ODR_ODR_4;

	 return received_data;
}

//SPI1 send n bytes receive n bytes
void SPI1SendNByteReceiveNByte(uint8_t *data_to_send, uint32_t send_data_len, uint8_t *data_to_read, uint32_t receive_data_len){

	//variable for count
	 uint32_t i = 0;

	 //SPI1 CS enable (output low logical level)
	 GPIOA -> ODR 		&= ~(GPIO_ODR_ODR_4);

	 for(i = 0;i < send_data_len;i++){
		 //Send data
		 SPI1Send1ByteReceive1Byte(&data_to_send[i]);
	 }
	 for(i = 0;i < receive_data_len;i++){
		 //Receive data
		 data_to_read[i] = SPI1Send1ByteReceive1Byte(&data_to_send[0]);
	 }

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
