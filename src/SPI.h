//
//SPI.h
//

#include "stm32f4xx.h"

#ifndef SPI_H_
#define SPI_H_

void SPI1Init(void);							//SPI1 inicialization

void SPI3Init(void);							//SPI3 inicialization

void SPI1Send8Bit(uint8_t *data);				//SPI1 send 8 bit data

void SPI1SendNByte(uint8_t *data,uint8_t data_len); //SPI1 send n-byte

uint8_t SPI1SendNByteReceive1Byte(uint8_t *data_to_send, uint8_t send_data_len); //SPI1 send n-byte receive 1-byte

#endif /* SPI_H_ */
