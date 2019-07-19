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
/////----OFFSET ADDRESS FOR COMMON REGISTER BLOCK----/////[R/W]
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
//GAR - gateway IP address register//[R/W]
/////////////////////////////////////

#define W5500_CRB_GAR_0			0x0001 			//Gateway IP Address Register 0 offset address
#define W5500_CRB_GAR_1			0x0002 			//Gateway IP Address Register 1 offset address
#define W5500_CRB_GAR_2			0x0003 			//Gateway IP Address Register 2 offset address
#define W5500_CRB_GAR_3			0x0004 			//Gateway IP Address Register 3 offset address

///////////////////////////////
//SUBR - subnet mask register//[R/W]
///////////////////////////////

#define W5500_CRB_SUBR_0 		0x0005 			//Subnet mask register 0 offset address
#define W5500_CRB_SUBR_1 		0x0006 			//Subnet mask register 1 offset address
#define W5500_CRB_SUBR_2 		0x0007 			//Subnet mask register 2 offset address
#define W5500_CRB_SUBR_3 		0x0008 			//Subnet mask register 3 offset address

///////////////////////////////////////////
//SHAR - Source hardware address register//[R/W]
///////////////////////////////////////////

#define W5500_CRB_SHAR_0 		0x0009 			//Source hardware register 0 offset address
#define W5500_CRB_SHAR_1 		0x000a 			//Source hardware register 1 offset address
#define W5500_CRB_SHAR_2 		0x000b 			//Source hardware register 2 offset address
#define W5500_CRB_SHAR_3 		0x000c 			//Source hardware register 3 offset address
#define W5500_CRB_SHAR_4 		0x000d 			//Source hardware register 4 offset address
#define W5500_CRB_SHAR_5 		0x000e 			//Source hardware register 5 offset address

/////////////////////////////////////
//SIPR - source IP address register//[R/W]
/////////////////////////////////////

#define W5500_CRB_SIPR_0 		0x000f 			//Source IP address register 0 offset address
#define W5500_CRB_SIPR_1 		0x0010 			//Source IP address register 1 offset address
#define W5500_CRB_SIPR_2 		0x0011 			//Source IP address register 2 offset address
#define W5500_CRB_SIPR_3 		0x0012 			//Source IP address register 3 offset address

////////////////////////////////////////////////
//INTLEVEL - interrupt low level time register//[R/W]
////////////////////////////////////////////////

#define W5500_CRB_INTLEVEL_0	0x0013 			//Interrupt low level timer register 0 offset address
#define W5500_CRB_INTLEVEL_1	0x0014 			//Interrupt low level timer register 1 offset address

///////////////////////////
//IR - interrupt register//[R/W]
///////////////////////////

#define W5500_CRB_IR 			0x0015 			//Interrupt register offset address

//Bit number		|    7   |   6   |  5  |4 |    3   |    2   |    1   |   0    |
//Bit designator	|CONFLICT|UNREACH|PPPoE|MP|Reserved|Reserved|Reserved|Reserved|

#define W5500_CRB_IR_CONFLICT 	0x80			//IP conflict
#define W5500_CRB_IR_UNREACH 	0x40			//Destination unreachable
#define W5500_CRB_IR_PPPOE 		0x20			//PPPoE connection close
#define W5500_CRB_IR_MP 		0x10			//Magic packet


/////////////////////////////////
//IMR - interrupt mask register//[R/W]
/////////////////////////////////

#define W5500_CRB_IMR 			0x0016 			//Interrupt mask register offset address

//Bit number		|  7   |  6   |   5  |  4   |    3   |    2   |    1   |   0    |
//Bit designator	|IM_IR7|IM_IR6|IM_IR5|IM_IR4|Reserved|Reserved|Reserved|Reserved|

#define W5500_CRB_IMR_IR7 		0x80			//IP conflict interrupt mask
#define W5500_CRB_IMR_IR6		0x40			//Destination unreachable interrupt mask
#define W5500_CRB_IMR_IR5		0x20			//PPPoE close interrupt mask
#define W5500_CRB_IMR_IR4		0x10			//Magic packet interrupt mask

///////////////////////////////////
//SIR - socket interrupt register//[R/W]
///////////////////////////////////

#define W5500_CRB_SIR 			0x0017 			//Socket interrupt register offset address

//Bit number		|  7   |  6   |   5  |  4   |   3  |   2  |   1  |  0   |
//Bit designator	|S7_INT|S6_INT|S5_INT|S4_INT|S3_INT|S2_INT|S1_INT|S0_INT|

#define W5500_CRB_SIR_S7 		0x80 			//Socket 7 interrupt
#define W5500_CRB_SIR_S6		0x40			//Socket 6 interrupt
#define W5500_CRB_SIR_S5		0x20			//Socket 5 interrupt
#define W5500_CRB_SIR_S4		0x10			//Socket 4 interrupt
#define W5500_CRB_SIR_S3		0x08			//Socket 3 interrupt
#define W5500_CRB_SIR_S2		0x04			//Socket 2 interrupt
#define W5500_CRB_SIR_S1		0x02			//Socket 1 interrupt
#define W5500_CRB_SIR_S0		0x01			//Socket 0 interrupt

/////////////////////////////////////////
//SIMR - socket interrupt mask register//[R/W]
/////////////////////////////////////////

#define W5500_CRB_SIMR 			0x0018 			//Socket interrupt mask register offset address

//Bit number		|  7   |  6   |   5  |  4   |   3  |   2  |   1  |  0   |
//Bit designator	|S7_IMR|S6_IMR|S5_IMR|S4_IMR|S3_IMR|S2_IMR|S1_IMR|S0_IMR|

#define W5500_CRB_SIMR_S7 		0x80 			//Socket 7 interrupt mask
#define W5500_CRB_SIMR_S6		0x40			//Socket 6 interrupt mask
#define W5500_CRB_SIMR_S5		0x20			//Socket 5 interrupt mask
#define W5500_CRB_SIMR_S4		0x10			//Socket 4 interrupt mask
#define W5500_CRB_SIMR_S3		0x08			//Socket 3 interrupt mask
#define W5500_CRB_SIMR_S2		0x04			//Socket 2 interrupt mask
#define W5500_CRB_SIMR_S1		0x02			//Socket 1 interrupt mask
#define W5500_CRB_SIMR_S0		0x01			//Socket 0 interrupt mask

///////////////////////////////////
//RTR - retry time value register//[R/W]
///////////////////////////////////

#define W5500_CRB_RTR_0			0x0019  		//Retry time value register 0 offset address
#define W5500_CRB_RTR_1 		0x001a 			//Retry time value register 1 offset address

//////////////////////////////
//RCR - retry count register//[R/W]
//////////////////////////////

#define W5500_CRB_RCR			0x001b  		//Retry count register offset address

/////////////////////////////////////////////////////////////
//PTIMER - PPP link control protocol request timer register//[R/W]
/////////////////////////////////////////////////////////////

#define W5500_CRB_PTIMER 		0x001c 			//PPP link control protocol request timer register offset address

////////////////////////////////////////////////////////////
//PMAGIC - PPP link control protocol magic number register//[R/W]
////////////////////////////////////////////////////////////

#define W5500_CRB_PMAGIC 		0x001d 			//PPP link control protocol magic number register offset address

//////////////////////////////////////////////////////////////
//PHAR - destination hardware address register in PPPoE mode//[R/W]
//////////////////////////////////////////////////////////////

#define W5500_CRB_PHAR_0 		0x001e 			//Destination hardware address register in PPPoE mode 0 offset address
#define W5500_CRB_PHAR_1 		0x001f 			//Destination hardware address register in PPPoE mode 1 offset address
#define W5500_CRB_PHAR_2 		0x0020 			//Destination hardware address register in PPPoE mode 2 offset address
#define W5500_CRB_PHAR_3 		0x0021 			//Destination hardware address register in PPPoE mode 3 offset address
#define W5500_CRB_PHAR_4 		0x0022 			//Destination hardware address register in PPPoE mode 4 offset address
#define W5500_CRB_PHAR_5 		0x0023 			//Destination hardware address register in PPPoE mode 5 offset address

////////////////////////////////////////////
//PSID - session ID register in PPPoE mode//[R/W]
////////////////////////////////////////////

#define W5500_CRB_PSID_0 		0x0024 			//Session ID register in PPPoE mode 0 offset address
#define W5500_CRB_PSID_1		0x0025 			//Session ID register in PPPoE mode 1 offset address

////////////////////////////////////////////
//PMRU - maximum receive unit in PPoE mode//[R/W]
////////////////////////////////////////////

#define W5500_CRB_PMRU_0		0x0026 			//maximum receive unit in PPoE mode 0 offset address
#define W5500_CRB_PMRU_1		0x0027 			//maximum receive unit in PPoE mode 1 offset address

//////////////////////////////////////////
//UIPR - unreachable IP address register//[R]
//////////////////////////////////////////

#define W5500_CRB_UIPR_0		0x0028			//unreachable IP address register 0 offset address
#define W5500_CRB_UIPR_1		0x0029			//unreachable IP address register 0 offset address
#define W5500_CRB_UIPR_2		0x002a			//unreachable IP address register 0 offset address
#define W5500_CRB_UIPR_3		0x002b			//unreachable IP address register 0 offset address

//////////////////////////////////////
//UPORTR - unreachable port register//[R]
//////////////////////////////////////

#define W5500_CRB_UPORT_0 		0x002c 			//unreachable port register 0 offset address
#define W5500_CRB_UPORT_1 		0x002d 			//unreachable port register 1 offset address

////////////////////////////////////////
//PHYCFGR - PHY configuration register//[R/W]
////////////////////////////////////////

#define W5500_CRB_PHYCFGR 		0x002e 			//W5500 PHY configuration register offset address

//Bit number		| 7 |  6 |   5  | 5-3 | 2 | 1 | 0 |
//Bit designator	|RST|OPMD|S5_IMR|OPMDC|DPX|SPD|LNK|

#define W5500_CRB_PHYCFGR_RST 	0x80 			//Internal PHY reset
#define W5500_CRB_PHYCFGR_OPMD 	0x40			//Configure PHY operation mode
//Operation mode configuration bits
#define W5500_CRB_PHYCFGR_OPMDC_10HD		0x00	//10BT half-duplex, auto negotiation disable
#define W5500_CRB_PHYCFGR_OPMDC_10FD		0x08	//10BT full-duplex, auto negotiation disable
#define W5500_CRB_PHYCFGR_OPMDC_100HD		0x10	//100BT half-duplex, auto negotiation disable
#define W5500_CRB_PHYCFGR_OPMDC_100FD		0x18	//100BT full-duplex, auto negotiation disable
#define W5500_CRB_PHYCFGR_OPMDC_100HD_AN	0x20	//100BT half-duplex, auto negotiation enabled
#define W5500_CRB_PHYCFGR_OPMDC_PD			0x30	//Power down mode
#define W5500_CRB_PHYCFGR_OPMDC_AC_AN		0x48	//All capable, auto negotiation enabled

#define W5500_CRB_PHYCFGR_DPX 	0x04 			//Duplex status read only
#define W5500_CRB_PHYCFGR_SPD 	0x02 			//Speed status 	read only
#define W5500_CRB_PHYCFGR_LNK 	0x01 			//Link status 	read only

////////////////////////////////////
//VERSIONR - chip version register//[R]
////////////////////////////////////

#define W5500_CBR_VERSIONR 		0x0039 			//W5500 chip version register offset address
//Constant sign value
#define W5500_CBR_VERSIONR_CON	0x04 			//W5500 cheap version constant read only as 0x04


/////////////////////////////////////////////////////////////
/////-----------------SOCKET REGISTERS------------------/////
/////////////////////////////////////////////////////////////

//////////////////////////////////
//SN_MR - socket n mode register//[R/W]
//////////////////////////////////

#define W5500_SR_MR 			0x0000 			//Socket n mode register address

//Bit number		|     7    |   6  |    5    |      4     |3-0|
//Bit designator	|MULTI/MFEN|BCASTB|ND/MC/MMB|UCASTB MIP6B| P |

#define W5500_SR_MR_MULTI_MFEN 		0x80 			//Multicasting in UDP mode / MAC filter enable in MACRAW mode
#define W5500_SR_MR_BCASTB 			0x40 			//Broadcast blocking in MACRAW and UDP mode
#define W5500_SR_MR_ND_MC_MMB 		0x20 			//Use no delayed ACK / multicast / multicast blocking in MACRAW mode
#define W5500_SR_MR_UCASTB_MIP6B	0x10 			//Unicast clocking in UDP mode / IPv6 paacket in MACRAW mode

//Protocol
#define W5500_SR_MR_CLOSED 			0x00 			//Protocol mode in closed
#define W5500_SR_MR_TCP 			0x01 			//Protocol mode in TCP
#define W5500_SR_MR_UDP 			0x02 			//Protocol mode in UDP
#define W5500_SR_MR_MACRAW 			0x04 			//Protocol mode in MACRAW

/////////////////////////////////////
//SN_CR - socket n command register//[R/W]
/////////////////////////////////////

#define W5500_SR_CR 			0x0001 			//Socket n command register address

//Commands
#define W5500_SR_CR_OPEN 		0x01 			//Socket n open 		command
#define W5500_SR_CR_LISTEN 		0x02 			//Socket n listen 		command
#define W5500_SR_CR_CONNECT 	0x04 			//Socket n connect 		command
#define W5500_SR_CR_DISCON 		0x08 			//Socket n disconnect 	command
#define W5500_SR_CR_CLOSE 		0x10 			//Socket n close 		command
#define W5500_SR_CR_SEND 		0x20 			//Socket n send 		command
#define W5500_SR_CR_SEND_MAC 	0x21 			//Socket n send mac 	command
#define W5500_SR_CR_SEND_KEEP 	0x22 			//Socket n send keep 	command
#define W5500_SR_CR_RECV 		0x40 			//Socket n receive 		command

///////////////////////////////////////
//SN_IR - socket n interrupt register//[R]
///////////////////////////////////////

#define W5500_SR_IR 			0x0002 			//Socket n interrupt register address

//Bit number		|    7   |    6   |    5   |   4   |   3   |  2 |  1   | 0 |
//Bit designator	|Reserved|Reserved|Reserved|SEND_OK|TIMEOUT|RECV|DISCON|CON|

#define W5500_SR_IR_SEND_OK		0x10			//Socket n send ok 	interrupt
#define W5500_SR_IR_TIMEOUT		0x08			//Socket n timeout 	interrupt
#define W5500_SR_IR_RECV		0x04			//Socket n recv 	interrupt
#define W5500_SR_IR_DISCON		0x02			//Socket n discon 	interrupt
#define W5500_SR_IR_CON			0x01			//Socket n con 		interrupt

////////////////////////////////////
//SN_SR - socket n status register//[R]
////////////////////////////////////

#define W5500_SR_SR 			0x0003 			//Socket n starus register address

//Status register values which was corelated to
//SN_CR - control register or some special control
//packet as SYN, FIN packet in TCP
#define W5500_SR_SR_SOCK_CLOSED 		0x00	//Socket n close 				status register value
#define W5500_SR_SR_SOCK_INIT 			0x13	//Socket n initialization 		status register value
#define W5500_SR_SR_SOCK_LISTEN 		0x14	//Socket n listen 				status register value
#define W5500_SR_SR_SOCK_ESTABLISHED	0x17 	//Socket n established 			status register value
#define W5500_SR_SR_SOCK_CLOSE_WAIT 	0x1c 	//Socket n wait on close 		status register value
#define W5500_SR_SR_SOCK_UDP 			0x22 	//Socket n is opened as UDP 	status register value
#define W5500_SR_SR_SOCK_MACRAW 		0x42 	//Socket n is opened as MACRAW 	status register value

//Temporary status indicator during changing the status of Socket n
#define W5500_SR_SR_SOCK_SYNSENT 		0x15 	//Socket n send connect request 	status register value
#define W5500_SR_SR_SOCK_SYNRECV 		0x16 	//Socket n receive connect request  status register value
#define W5500_SR_SR_SOCK_FIN_WAIT 		0x18 	//Socket n wait on FIN packet 		status register value
#define W5500_SR_SR_SOCK_CLOSING 		0x1a 	//Socket n active-close 			status register value
#define W5500_SR_SR_SOCK_TIME_WAIT 		0x1b 	//Socket n passive-close 			status register value
#define W5500_SR_SR_SOCK_LAST_ACK 		0x1d 	//Socket n wait on FIN/ACK packet 	status register value

///////////////////////////////////////////
//SN_PORT - socket n source port register//[R/W]
///////////////////////////////////////////

#define W5500_SR_PORT_0 		0x0004 		//Socket n source port register 0 address
#define W5500_SR_PORT_1 		0x0005 		//Socket n source port register 1 address

////////////////////////////////////////////////////////////
//SN_DHAR - socket n destination hardware address register//[R/W]
////////////////////////////////////////////////////////////

#define W5500_SR_DHAR_0 		0x0006 		//Socket n hardware address register 0 address
#define W5500_SR_DHAR_1 		0x0007 		//Socket n hardware address register 1 address
#define W5500_SR_DHAR_2 		0x0008 		//Socket n hardware address register 2 address
#define W5500_SR_DHAR_3 		0x0009 		//Socket n hardware address register 3 address
#define W5500_SR_DHAR_4 		0x000a 		//Socket n hardware address register 4 address
#define W5500_SR_DHAR_5 		0x000b 		//Socket n hardware address register 5 address

//////////////////////////////////////////////////////
//SN_DIPR - socket n destination IP address register//[R/W]
//////////////////////////////////////////////////////

#define W5500_SR_DIPR_0 		0x000c 		//Socket n destination IP address register 0 address
#define W5500_SR_DIPR_1 		0x000e 		//Socket n destination IP address register 1 address
#define W5500_SR_DIPR_2 		0x000e 		//Socket n destination IP address register 2 address
#define W5500_SR_DIPR_3 		0x000f 		//Socket n destination IP address register 3 address

/////////////////////////////////////////////////
//SN_DPORT - socket n destination port register//[R/W]
/////////////////////////////////////////////////

#define W5500_SR_DPORT_0 		0x0010 		//Socket n destination port register 0 address
#define W5500_SR_DPORT_1 		0x0011 		//Socket n destination port register 1 address

////////////////////////////////////////////////////
//SN_MSSR - socket n maximum segment size register//[R/W]
////////////////////////////////////////////////////

#define W5500_SR_MSSR_0			0x0012 		//Socket n maximum segment size register 0 address
#define W5500_SR_MSSR_1			0x0013 		//Socket n maximum segment size register 1 address

/////////////////////////////////////////////////
//SN_TOS - socket n IP type of service register//[R/W]
/////////////////////////////////////////////////

#define W5500_SR_TOS 			0x0015 		//Socket n IP type of service register address



#define TEST_ADDRES 			0x000f
#define MSB(x)					((uint8_t)x>>8)
#define LSB(x)					((uint8_t)x)

void W5500Init(void);


#endif /* W5500_H_ */
