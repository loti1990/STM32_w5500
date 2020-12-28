/*
 * I2S.c
 */

#include "I2S.h"

//I2S2 initialization function
void I2S2Init(){

	/* Text from DS pg. 909
	 * 1.Select the I2SDIV[7:0] bits in the SPI_I2SPR register to define the serial clock baud rate to reach the
	 * proper audio sample frequency. The ODD bit in the SPI_I2SPR register also has to be defined.
	 * 2.     Select the CKPOL bit to define the steady level for the communication clock. Set the MCKOE bit
	 * in the SPI_I2SPR register if the master clock MCK needs to be provided to the external DAC/ADC audio
	 * component (the I2SDIV and ODD values should be computed depending on the state of the MCK output,
	 * for more details refer to Section 28.4.4: Clock generator).
	 * 3.     Set the I2SMOD bit in SPI_I2SCFGR to activate the I2S functionalities and choose the I2S standard
	 * through the I2SSTD[1:0] and PCMSYNC bits, the data length through the DATLEN[1:0] bits and the number of
	 *  bits per channel by configuring the CHLEN bit. Select also the I2S master mode and direction (Transmitter
	 *  or Receiver) through the I2SCFG[1:0] bits in the SPI_I2SCFGR register.
	 *  4.     If needed, select all the potential interruption sources and the DMA capabilities by writing the
	 *  SPI_CR2 register.
	 *  5.     The I2SE bit in SPI_I2SCFGR register must be set.WS and CK are configured in output mode. MCK is
	 *   also an output, if the MCKOE bit in SPI_I2SPR is set.
	 */

	//Sampling clock configuration see DS pg. 908 FS = I2SxCLK / [(16*2)*((2*I2SDIV)+ODD)*8)] (when the channel frame is 16-bit wide)
	//I2SxCLK is defined in system_stm32f4xx.c
	//I2SxCLK = (HSE/PLL_M)*(PLLI2S_N/PLLI2S_R) = (8MHz / 4) * (129/3) = 86 MHz
	//If we want to have 48 kHz sampling rate then ODD = 1 and I2SDIV have to be 3

	//I2S ODD factor for the prescaler
	SPI2 -> I2SPR 		|= SPI_I2SPR_ODD; 		//Real divider value is enabled (I2SDIV * 2)+1

	//I2S DIV linear prescaler
	SPI2 -> I2SPR 		|= (0x03); 				//linear prescaler was set to 3

	//I2S master clock output enable
	SPI2 -> I2SPR 		|= SPI_I2SPR_MCKOE; 	//Master clock output enable

	//Data length
	SPI2 -> I2SCFGR 	&= ~(SPI_I2SCFGR_DATLEN_0 | SPI_I2SCFGR_DATLEN_1); 	//16- bit data length

	//Channel length
	SPI2 -> I2SCFGR 	&= ~(SPI_I2SCFGR_CHLEN); 	//16- bit channel length

	//I2S clock polarity
	SPI2 -> I2SCFGR 	&= ~(SPI_I2SCFGR_CKPOL); 	//Clock steady state is low level

	//I2S standard select
	SPI2 -> I2SCFGR 	|=	(SPI_I2SCFGR_I2SSTD_0 | SPI_I2SCFGR_I2SSTD_1); 	//PCM standard

	//I2S master - receive
	SPI2 -> I2SCFGR 	|= (SPI_I2SCFGR_I2SCFG_0 | SPI_I2SCFGR_I2SCFG_1);

	//I2S mode select
	SPI2 -> I2SCFGR 	|= SPI_I2SCFGR_I2SMOD; 	//I2S mode is enabled

	//I2S Enable
	SPI2 -> I2SCFGR 	|= SPI_I2SCFGR_I2SE;


}

//Receive 16 bit data from I2S2 communication protocol
uint16_t I2S2ReceiveData(uint8_t *data){

	 SPI2 -> I2SPR 		|= SPI_I2SPR_MCKOE; 	//Master clock output enable

	 //send 8 bit data
	 SPI2 -> DR = *data;

	 //Wait until SPI1 data buffer register is empty
	 while(!(SPI2 -> SR & SPI_SR_TXE));

	 //wait until SPI1 receive buffer is not empty
	 while(!(SPI2 -> SR & SPI_SR_RXNE));

	 //wait till SPI1 are sending data "busy state"
	 while(SPI2 -> SR & SPI_SR_BSY);

	 SPI2 -> I2SPR 		&= ~(SPI_I2SPR_MCKOE); 	//Master clock output disable

	 //return received data
	 return SPI2 -> DR;

}
