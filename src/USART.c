/*
 * USART.c
 */


#include "USART.h"


//USART3 initialization function
void USART3Init(uint32_t baud_rate){

	//Before calculate baud rate, define OVER8 bit in CR1 (pg. 1011)
	//Define to 16x oversampling
	USART3 -> CR1		&= ~(USART_CR1_OVER8); 		//Oversampling by 16

	//Calculate baud rate for UART comunication
	//Frequency on APB1 bus was equal to 42 MHz
	//Check the oversampling factor and then calculate baud rate
	//Equation for baud rate calculation:
	//Tx/Rx baud = (fclk)/(8*(2-OVER8)*USARTDIV)
	//-fclk - clock of the APB1 bus
	//-OVER8 was bit set or reset in CR1 (value was 1 or 0)
	//USARTDIV was USART divider factor

	//This equatin was only wqalid when oversampling was 16x
	double baud_devider = (42000000.0)/((double)baud_rate) + 0.5; //we add 0.5 because of rounding !!!

	//Write calculate values in to baud rate register
	USART3 -> BRR 		= (uint16_t)baud_devider;

	//Enable TX interrupt
	//USART3 -> CR1 		|= USART_CR1_TXEIE;

	//Enable RX interrupt
	USART3 -> CR1 		|= USART_CR1_RXNEIE;

	//Enable interrupt
	//NVIC_EnableIRQ(USART3_IRQ);
	NVIC -> ISER[1] 				|= (1 << (USART3_IRQn-32)); 	//Enable external interrupt

	//Set priority
	NVIC -> IP[USART3_IRQn] 		= (uint8_t) 0x02;		//set priority of USART3_IRQ to 2 (lower are the number the higher are priority)

	//8-bit data length
	USART3 -> CR1 		&= ~(USART_CR1_M);

	//1-stop bit
	USART3 -> CR2 		&= ~(USART_CR2_STOP);

	//Parety control disable
	USART3 -> CR1 		&= ~(USART_CR1_PCE);

	//Enable reception
	USART3 -> CR1 		|= USART_CR1_RE;

	//Enable transmition
	USART3 -> CR1 		|= USART_CR1_TE;

	//Enable USART3
	USART3 -> CR1 		|= USART_CR1_UE;

}

void USART3SendByte(uint8_t data){

	//Write data in to USART3 data register
	USART3 -> DR 		= data;

	//Wqait until data was transfered in to outpur shift register
	while(!(USART3 -> SR & USART_SR_TXE));

}

void USART3SendText(uint8_t *data, uint32_t length){

	uint32_t i = 0;

	for(i = 0;i < length;i++){
		USART3SendByte(data[i]);
	}
}
