//
//SPI.h
//

#include "stm32f4xx.h"

#ifndef SPI_H_
#define SPI_H_

void SPI1Init(void);							//SPI1 inicialization

void SPI3Init(void);							//SPI3 inicialization

uint8_t SPI1Send8Bit(uint8_t *data);		//SPI1 send 8 bit data

#endif /* SPI_H_ */
