/*
 * I2C.c
 *
 */

#include "I2C.h"

//I2C1 initialization function
void I2C1Init(void){

	//APB1 peripheral clock was set to 42 MHz
	I2C1 -> CR2 	|= 42;

	//Enable Fm mode for sclk frequency from 0 to 400 kHz
	I2C1 -> CCR 	|= I2C_CCR_FS;

	//Set up clock control register in Fm/Sm mode
	//Our target frequency was 400 kHz
	//APB1 clk = 42MHz
	//I2C1 clk = 400kHz
	//Tpclk1 = 1/APB1 clk
	//Ton = CCR * Tpclk1
	//Toff = 2*CCR*Tpclk1
	//For our data 1/I2C1 clk = Ton+Toff (period tau)
	//CCR = 1/(I2C clk * (Tpclk1 + 2*Tpclk1))
	//CCR for our data is 35 or 0x23
	I2C1 -> CCR 	|= 0x23;

	//Set up maximum rise time in Fm/Sm mode
	//For Sm mode the max rise time was 1000 ns (max freq. 100kHz) so for Fm mode with 400kHz these was 4x lower
	//From that the maximum rise time will be 250 ns
	//Based on that the TRISE filter value will be calculated as:
	//APB1 clk = 42 MHz
	//Max rise time = 250 ns
	//TRISE = 250ns/(1/42MHz) + 1 = 12 = 0x0C
	I2C1 -> TRISE 	= 0x0C;

	//Enable I2C1 do these in te end of inicialization
	I2C1 ->	CR1 	|= I2C_CR1_PE;

}

void I2C1TestSend(void){

	//Start frame
	I2C1 -> CR1 	|= I2C_CR1_START;

	//Wait on start to be send
	while(!(I2C1 -> SR1 & I2C_SR1_SB));

	//Send data
	I2C1 -> DR 		= 0xFA;

	//Wait to on data to be send
	while(!(I2C1 -> SR1 & I2C_SR1_TXE));

	//Send stop bit
	I2C1 -> CR1 	|= I2C_CR1_STOP;


}


