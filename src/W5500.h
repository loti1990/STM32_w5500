/*
 * W5500.h
 */

#include "SPI.h"

#ifndef W5500_H_
#define W5500_H_

//Control phase parameter definitrion
#define W5500_CP_BSB_CR 		0X00 		//

#define TEST_ADDRES 			0x000f
#define MSB(x)					((uint8_t)x>>8)
#define LSB(x)					((uint8_t)x)

void W5500Init(void);


#endif /* W5500_H_ */
