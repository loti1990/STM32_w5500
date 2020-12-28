//
//I2S.h
//

#include "stm32f4xx.h"

#ifndef I2S_H_
#define I2S_H_

void I2S2Init(void);						//Initialize I2S2

uint16_t I2S2ReceiveData(uint8_t *data); 	//Receive data from I2S2 communication protocol

#endif /* I2S_H_ */
