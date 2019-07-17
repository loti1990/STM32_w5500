/*
 * W5500.h
 */

#include "SPI.h"

#ifndef W5500_H_
#define W5500_H_

//////////////////////////////////////////////////////////
/////-----------------CONTROL PHASE------------------/////
//////////////////////////////////////////////////////////
//Bit number		|   7-3  | 2 |  1-0  |
//Bit designator	|BSB[4:0]|RWB|OM[1:0]|
///////
//BSB//
///////
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

///////////////////////////////////////
//RWB- Read/Write operation mode Bits//
///////////////////////////////////////
//Read/write operation
#define W5500_CP_READ 			0x0000 			//Read from W5500
#define W5500_CP_WRITE 			0x0004 			//Write in to W5500

//////////////////////////
//OM-Operation mode bits//
//////////////////////////
//SPI operation mode bits
#define W5500_CP_OM_VDLM 		0x0000 			//Variable data length mode N-Bytes data phase
#define W5500_CP_OM_FDLM_1 		0x0001			//Fixed data length mode 1 Byte data length
#define W5500_CP_OM_FDLM_2 		0x0002 			//Fixed data length mode 2 Byte data length
#define W5500_CP_OM_FDLM_4 		0x0003 			//Fixed data length mode 4 Byte data length


//////////////////////////////////////////////////////////
/////----OFFSET ADDRESS FOR COMMON REGISTER BLOCK----/////
//////////////////////////////////////////////////////////
//////////////////////
//MR - mode register//
//////////////////////

#define W5500_CRB_MR 			0x0000			//Mode register offset address

//Bit number		| 7 | 6      | 5 |4 |  3  |    2   |  1 |   0    |
//Bit designator	|RST|Reserved|WOL|PB|PPPoE|Reserved|FARP|Reserved|

#define W5500_CRB_MR_RST 		0x80 			//Reset the external peripheral W5500
#define W5500_CRB_MR_WOL 		0x20 			//Wake on LAN
#define W5500_CRB_MR_PB 		0x10 			//Ping block mode
#define W5500_CRB_MR_PPPOE 		0x08 			//PPP0E mode
#define W5500_CRB_MR_FARP 		0x02 			//Force ARP


/////////////////////////////////////
//GAR - gateway IP address register//
/////////////////////////////////////
#define W5500_CRB_GAR_0			0x0001 			//Gateway IP Address Register 0 offset address
#define W5500_CRB_GAR_1			0x0002 			//Gateway IP Address Register 1 offset address
#define W5500_CRB_GAR_2			0x0003 			//Gateway IP Address Register 2 offset address
#define W5500_CRB_GAR_3			0x0004 			//Gateway IP Address Register 3 offset address

///////////////////////////////
//SUBR - subnet mask register//
///////////////////////////////
#define W5500_CRB_SUBR_0 		0x0005 			//Subnet mask register 0 offset address
#define W5500_CRB_SUBR_1 		0x0006 			//Subnet mask register 1 offset address
#define W5500_CRB_SUBR_2 		0x0007 			//Subnet mask register 2 offset address
#define W5500_CRB_SUBR_3 		0x0008 			//Subnet mask register 3 offset address

///////////////////////////////////////////
//SHAR - Source hardware address register//
///////////////////////////////////////////
#define W5500_CRB_SHAR_0 		0x0009 			//Source hardware register 0 offset address
#define W5500_CRB_SHAR_1 		0x000a 			//Source hardware register 1 offset address
#define W5500_CRB_SHAR_2 		0x000b 			//Source hardware register 2 offset address
#define W5500_CRB_SHAR_3 		0x000c 			//Source hardware register 3 offset address
#define W5500_CRB_SHAR_4 		0x000d 			//Source hardware register 4 offset address
#define W5500_CRB_SHAR_5 		0x000e 			//Source hardware register 5 offset address

/////////////////////////////////////
//SIPR - source IP address register//
/////////////////////////////////////
#define W5500_CRB_SIPR_0 		0x000f 			//Source IP address register 0 offset address
#define W5500_CRB_SIPR_1 		0x0010 			//Source IP address register 1 offset address
#define W5500_CRB_SIPR_2 		0x0011 			//Source IP address register 2 offset address
#define W5500_CRB_SIPR_3 		0x0012 			//Source IP address register 3 offset address

////////////////////////////////////////////////
//INTLEVEL - interrupt low level time register//
////////////////////////////////////////////////
#define W5500_CRB_INTLEVEL_0	0x0013 			//Interrupt low level timer register 0 offset address
#define W5500_CRB_INTLEVEL_1	0x0014 			//Interrupt low level timer register 1 offset address

///////////////////////////
//IR - interrupt register//
///////////////////////////
#define W5500_CRB_IR 			0x0015 			//Interrupt register offset address

/////////////////////////////////
//IMR - interrupt mask register//
/////////////////////////////////
#define W5500_CRB_IMR 			0x0016 			//Interrupt mask register offset address

///////////////////////////////////
//SIR - socket interrupt register//
///////////////////////////////////
#define W5500_CRB_SIR 			0x0017 			//Socket interrupt register offset address

////////////////////////////////////
//SIMR - socket interrupt register//
////////////////////////////////////
#define W5500_CRB_SIMR 			0x0018 			//Socket interrupt mask register offset address

///////////////////////////////////
//RTR - retry time value register//
///////////////////////////////////
#define W5500_CRB_RTR_0			0x0019  		//Retry time value register 0 offset address
#define W5500_CRB_RTR_1 		0x001a 			//Retry time value register 1 offset address

//////////////////////////////
//RCR - retry count register//
//////////////////////////////
#define W5500_CRB_RCR			0x001b  		//Retry count register offset address

/////////////////////////////////////////////////////////////
//PTIMER - PPP link control protocol request timer register//
/////////////////////////////////////////////////////////////
#define W5500_CRB_PTIMER 		0x001c 			//PPP link control protocol request timer register offset address

////////////////////////////////////////////////////////////
//PMAGIC - PPP link control protocol magic number register//
////////////////////////////////////////////////////////////
#define W5500_CRB_PMAGIC 		0x001d 			//PPP link control protocol magic number register offset address

//////////////////////////////////////////////////////////////
//PHAR - destination hardware address register in PPPoE mode//
//////////////////////////////////////////////////////////////
#define W5500_CRB_PHAR_0 		0x001e 			//Destination hardware address register in PPPoE mode 0 offset address
#define W5500_CRB_PHAR_1 		0x001f 			//Destination hardware address register in PPPoE mode 1 offset address
#define W5500_CRB_PHAR_2 		0x0020 			//Destination hardware address register in PPPoE mode 2 offset address
#define W5500_CRB_PHAR_3 		0x0021 			//Destination hardware address register in PPPoE mode 3 offset address
#define W5500_CRB_PHAR_4 		0x0022 			//Destination hardware address register in PPPoE mode 4 offset address
#define W5500_CRB_PHAR_5 		0x0023 			//Destination hardware address register in PPPoE mode 5 offset address

////////////////////////////////////////////
//PSID - session ID register in PPPoE mode//
////////////////////////////////////////////
#define W5500_CRB_PSID_0 		0x0024 			//Session ID register in PPPoE mode 0 offset address
#define W5500_CRB_PSID_1		0x0025 			//Session ID register in PPPoE mode 1 offset address

////////////////////////////////////////////
//PMRU - maximum receive unit in PPoE mode//
////////////////////////////////////////////
#define W5500_CRB_PMRU_0		0x0026 			//maximum receive unit in PPoE mode 0 offset address
#define W5500_CRB_PMRU_1		0x0027 			//maximum receive unit in PPoE mode 1 offset address

/////////////////////////////////////////
//UIPR - unreachable IP address register//
/////////////////////////////////////////
#define W5500_CRB_UIPR_0		0x0028			//unreachable IP address register 0 offset address
#define W5500_CRB_UIPR_1		0x0029			//unreachable IP address register 0 offset address
#define W5500_CRB_UIPR_2		0x002a			//unreachable IP address register 0 offset address
#define W5500_CRB_UIPR_3		0x002b			//unreachable IP address register 0 offset address

//////////////////////////////////////
//UPORTR - unreachable port register//
//////////////////////////////////////
#define W5500_CRB_UPORT_0 		0x002c 			//unreachable port register 0 offset address
#define W5500_CRB_UPORT_1 		0x002d 			//unreachable port register 1 offset address

////////////////////////////////////////
//PHYCFGR - PHY configuration register//
////////////////////////////////////////
#define W5500_CRB_PHYCFGR 		0x002e 			//W5500 PHY configuration register offset address

////////////////////////////////////
//VERSIONR - chip version register//
////////////////////////////////////
#define W5500_CBR_VERSIONR 		0x0039 			//W5500 chip version register offset address












#define TEST_ADDRES 			0x000f
#define MSB(x)					((uint8_t)x>>8)
#define LSB(x)					((uint8_t)x)

void W5500Init(void);


#endif /* W5500_H_ */
