/*
 * USART.h
 */

#include "stm32f4xx.h"

#ifndef USART_H_
#define USART_H_

void USART3Init(uint32_t baud_rate); 		//USART3 initialization function

void USART3SendByte(uint8_t data); 			//USART3 send byte

void USART3SendText(uint8_t *data, uint32_t length); //USART3 send text

#endif /* USART_H_ */


