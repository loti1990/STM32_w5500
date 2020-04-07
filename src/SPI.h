//
//SPI.h
//

#include "stm32f4xx.h"

#ifndef SPI_H_
#define SPI_H_

void SPI1Init(void);																//SPI1 inicialization

void SPI3Init(void);																//SPI3 inicialization

void SPI1SendNByte(uint8_t *data,uint32_t data_len); 								//SPI1 send n-byte

uint8_t SPI1SendNByteReceive1Byte(uint8_t *data_to_send, uint32_t send_data_len); 	//SPI1 send n-byte receive 1-byte

uint8_t SPI1Send1ByteReceive1Byte(uint8_t *data); 									//SPI1 send 1 byte receive 1 byte

void SPI1SendNByteReceiveNByte(uint8_t *data_to_send, uint32_t send_data_len, uint8_t *data_to_read, uint32_t receive_data_len); //SPI1 send n byte receive n byte

void SPI1SendNByteControlAndOther(uint8_t *control_data,uint32_t c_data_len,uint8_t *data,uint32_t data_len); //SPI1 send n-byte with control data first and other data second

#endif /* SPI_H_ */
