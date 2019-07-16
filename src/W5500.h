/*
 * W5500.h
 */

#include "SPI.h"

#ifndef W5500_H_
#define W5500_H_

///////////////////////
/////CONTROL PHASE/////
///////////////////////
//

#define W5500_CP_BSB_CR 		0x0000 			//Select common register
//Socket 0
#define W5500_CP_BSB_S0_R 		0x0008			//Select socket 0 register
#define W5500_CP_BSB_S0_TX		0x000a 			//Select socket 0 TX Buffer
#define W5500_CP_BSB_S0_RX 		0x0018			//Select socket 0 RX Buffer
//Socket 1
#define W5500_CP_BSB_S1_R 		0x0028			//Select socket 1 register
#define W5500_CP_BSB_S1_TX		0x0030 			//Select socket 1 TX Buffer
#define W5500_CP_BSB_S1_RX 		0x0038			//Select socket 1 RX Buffer
//Socket 2
#define W5500_CP_BSB_S2_R 		0x0048			//Select socket 2 register
#define W5500_CP_BSB_S2_TX		0x0050 			//Select socket 2 TX Buffer
#define W5500_CP_BSB_S2_RX 		0x0058			//Select socket 2 RX Buffer
//Socket 3
#define W5500_CP_BSB_S3_R 		0x0068			//Select socket 3 register
#define W5500_CP_BSB_S3_TX		0x0070 			//Select socket 3 TX Buffer
#define W5500_CP_BSB_S3_RX 		0x0078			//Select socket 3 RX Buffer
//Socket 4
#define W5500_CP_BSB_S4_R 		0x0088			//Select socket 4 register
#define W5500_CP_BSB_S4_TX		0x0090 			//Select socket 4 TX Buffer
#define W5500_CP_BSB_S4_RX 		0x0098			//Select socket 4 RX Buffer
//Socket 5
#define W5500_CP_BSB_S5_R 		0x00a8			//Select socket 5 register
#define W5500_CP_BSB_S5_TX		0x00b0 			//Select socket 5 TX Buffer
#define W5500_CP_BSB_S5_RX 		0x00b8			//Select socket 5 RX Buffer
//Socket 6
#define W5500_CP_BSB_S6_R 		0x00c8			//Select socket 6 register
#define W5500_CP_BSB_S6_TX		0x00d0 			//Select socket 6 TX Buffer
#define W5500_CP_BSB_S6_RX 		0x00d8			//Select socket 6 RX Buffer
//Socket 7
#define W5500_CP_BSB_S7_R 		0x00e8			//Select socket 7 register
#define W5500_CP_BSB_S7_TX		0x00f0 			//Select socket 7 TX Buffer
#define W5500_CP_BSB_S7_RX 		0x0018			//Select socket 7 RX Buffer
//Read/write operation
#define W5500_CP_READ 			0x0000 			//Read from W5500
#define W5500_CP_WRITE 			0x0004 			//Write in to W5500
//SPI operation mode bits
#define W5500_CP_OM_VDLM 		0x0000 			//Variable data length mode N-Bytes data phase
#define W5500_CP_OM_FDLM_1 		0x0001			//Fixed data length mode 1 Byte data length
#define W5500_CP_OM_FDLM_2 		0x0002 			//Fixed data length mode 2 Byte data length
#define W5500_CP_OM_FDLM_3 		0x0003 			//Fixed data length mode 4 Byte data length

///////////////////////////////
/////COMMON REGISTER BLOCK/////
///////////////////////////////
#define W5500_CRB_MR



#define TEST_ADDRES 			0x000f
#define MSB(x)					((uint8_t)x>>8)
#define LSB(x)					((uint8_t)x)

void W5500Init(void);


#endif /* W5500_H_ */
