/*
 * W5500.c
 */

#include "W5500.h"


//common register - setup mode register
//enable Ping response
uint8_t CR_MR_W5500[4] = {0x00,0x00,0x04,0x00};

//common register - setup gateway IP adress
//gateway ip address = 192(0xc0).168(0xa8).1(0x01).1(0x01)
uint8_t CR_GAR_W5500[7] = {0x00,0x01,0x04,0xc0,0xa8,0x01,0x01};

//common register -setup subnet mask register
//subnet mask IP address = 255(0xff).255(0xff).255(0xff).0(0x00)
uint8_t CR_SUBR_W5500[7] = {0x00,0x05,0x04,0xff,0xff,0xff,0x00};

//common register -setup source hardware address register
//source hardware address = 00(0x00).08(0x08).dc(0xdc).01(0x01).02(0x02).03(0x03)
uint8_t CR_SHAR_W5500[9] = {0x00,0x09,0x04,0x00,0x08,0xdc,0x01,0x02,0x03};

//common register - setup source IP address register
//source IP address = 192(0xc0).168(0xa8).1(0x01).100(0x64)
uint8_t CR_SIPR_W5500[7] = {0x00,0x0f,0x04,192,168,1,100};

//common register - PHY configuration register PHYCFGR
//no reset
//PHY operation mode configure with OPMDC[2:0]avi
//Operation mode: 100BT Full- duplex, auto negotiation disabled
uint8_t CR_PHYCFGR_W5500[4] = {0x00,0x2e,0x04,0xd8};

//common register - socket interrupt mask register
//enable interrupt for socket 0
uint8_t CR_SIMR_W5500[4] = {0x00,0x18,0x04,0x01};

////////////
//SOCKET 0//
////////////

//Socket 0 RX and TX buffer size register
//RX memory allocation size 2kBytes
//TX memory allocation size 2kBytes
uint8_t S0_RX_TX_BUF_SIZE_W5500[5] = {0x00,0x1e,0x0c,0x02,0x02};

//Socket 0 mode register
//Socket 0 used TCP protocol
uint8_t S0_MR_W5500[4] = {0x00,0x00,0x0c,0x01};

//Socket 0 source port
//Configure source port as 1024
uint8_t S0_PORT_W5500[5] = {0x00,0x04,0x0c,0x04,0x00};

//Socket 0 open
//OPEN
uint8_t S0_CR_OPEN_W5500[4] = {0x00,0x01,0x0c,0x01};

//Socket 0 listen
//LISTEN
uint8_t S0_CR_LISTEN_W5500[4] = {0x00,0x01,0x0c,0x02};

//Socket 0 read status register
uint8_t S0_SR_W5500[3] = {0x00,0x03,0x08};

//write data in to socket 0 TX regster
//write from offset address 0x0000
uint8_t S0_TX_BUFFER[259]={0x00,0x00,0x14};

//send data to client
uint8_t S0_SEND_TX_BUFFER[4]={0x00,0x01,0x0c,0x20};

//close connection
uint8_t S0_CLOSE[4] = {0x00,0x01,0x0c,0x10};

//Socket 0 TX read pointer most significant bit in register [read only]
uint8_t S0_TX_RD_MSB[3] = {0x00,0x22,0x08};

//Socket 0 TX read pointer last significant bit in register [read only]
uint8_t S0_TX_RD_LSB[3] = {0x00,0x23,0x08};

//Socket 0 TX write pointer register [read/write]
uint8_t S0_TX_WR[5] = {0x00,0x24,0x0C};

//Initialize W5500 ethernet module
void W5500Init(void){

	//enable ping
	SPI1SendNByte(CR_MR_W5500,4);

	//setup gateway IP address
	SPI1SendNByte(CR_GAR_W5500,7);

	//setup subnet mask register
	SPI1SendNByte(CR_SUBR_W5500,7);

	//setup hardware address register
	SPI1SendNByte(CR_SHAR_W5500,9);

	CR_SIPR_W5500[0]=MSB(W5500_CRB_SIPR_0);
	CR_SIPR_W5500[1]=LSB(W5500_CRB_SIPR_0);
	//setup source IP address register
	SPI1SendNByte(CR_SIPR_W5500,7);

	//setup PHY configuration register
	SPI1SendNByte(CR_PHYCFGR_W5500,4);

	//enable interrupt for socket 0
	SPI1SendNByte(CR_SIMR_W5500,4);

	//setup Socket 0 RX and TX memory allocation
	SPI1SendNByte(S0_RX_TX_BUF_SIZE_W5500,5);

	//setup Socket 0 Protocol
	SPI1SendNByte(S0_MR_W5500,4);

	//setup Socket 0 port number
	SPI1SendNByte(S0_PORT_W5500,5);

	//open Socket 0
	SPI1SendNByte(S0_CR_OPEN_W5500,4);

	//wait on Socket 0 SOCK_INIT flag
	while(!(SPI1SendNByteReceive1Byte(S0_SR_W5500,3) == 0x13));

	//listen Socket 0
	SPI1SendNByte(S0_CR_LISTEN_W5500,4);

	//wait on Socket 0 SOCK_LISTEN flag
	while(!(SPI1SendNByteReceive1Byte(S0_SR_W5500,3) == 0x14));

	//wait on socket establishe flag
	while(!(SPI1SendNByteReceive1Byte(S0_SR_W5500,3)==0x17));

	//create variables for Socket0 TX buffer start and end pointer which define data length
	uint16_t start_pointer = 0;
	uint16_t end_pointer = 0;

	//read Socket 0 TX read pointer register
	start_pointer = SPI1SendNByteReceive1Byte(S0_TX_RD_MSB,3);
	start_pointer = start_pointer << 8;
	start_pointer = start_pointer | SPI1SendNByteReceive1Byte(S0_TX_RD_LSB,3);

	//calculate value of Socket0 write pointer register for length of data available for send
	end_pointer = start_pointer + 256;

	//manage LSB and MSB bits
	S0_TX_WR[3] =(uint8_t)(end_pointer>>8);
	S0_TX_WR[4] =(uint8_t)end_pointer;

	//write value in to Socket0 TX write pointer register
	SPI1SendNByte(S0_TX_WR,5);


	//generate data for sending
	int i=0;
	for(i=3;i<259;i++){

		S0_TX_BUFFER[i]=i;
	}

	//configure Socket0 TX buffer start address
	S0_TX_BUFFER[0] = SPI1SendNByteReceive1Byte(S0_TX_RD_MSB,3);
	S0_TX_BUFFER[1] = SPI1SendNByteReceive1Byte(S0_TX_RD_LSB,3);

	//write data in to TX buffer
	SPI1SendNByte(S0_TX_BUFFER,259);

	//send TX data to the client
	SPI1SendNByte(S0_SEND_TX_BUFFER,4);

	//wait on last ACK flag from client
	//while(!(SPI1SendNByteReceive1Byte(S0_SR_W5500,3)==0x1d));

	//close the connection
	SPI1SendNByteReceive1Byte(S0_CLOSE,3);

}

void W5500InitV2(uint8_t *ip, uint8_t *gateway, uint8_t *submask, uint8_t *mac){

	//temporary register, necessary to initialize to initial state
	uint8_t temp_array[10] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};

	//w5500 enable ping response
	temp_array[0] 		= MSB(W5500_CRB_MR);			//set address for common mode register MSB
	temp_array[1] 		= LSB(W5500_CRB_MR);			//set address for common mode register LSB
	temp_array[2] 		|= (W5500_CP_BSB_CR
						| W5500_CP_WRITE
						| W5500_CP_OM_VDLM); 			//set byte for write in to common register
	temp_array[3] 		&= ~(W5500_CRB_MR_RST
						| W5500_CRB_MR_WOL
						| W5500_CRB_MR_PB
						| W5500_CRB_MR_PPPOE
						| W5500_CRB_MR_FARP); 		//write in to common mode register
	//write thru spi communication
	SPI1SendNByte(temp_array,4);


	//setup gateway IP address
	temp_array[0] 		= MSB(W5500_CRB_GAR_0);			//set address for common gateway register MSB
	temp_array[1] 		= LSB(W5500_CRB_GAR_0);			//set address for common gateway register LSB
	temp_array[2] 		|= (W5500_CP_BSB_CR
						| W5500_CP_WRITE
						| W5500_CP_OM_VDLM); 		//set byte for write in to common register
	temp_array[3] 		= gateway[0]; 					//setup gateway address byte 0
	temp_array[4] 		= gateway[1]; 					//setup gateway address byte 1
	temp_array[5] 		= gateway[2]; 					//setup gateway address byte 2
	temp_array[6] 		= gateway[3]; 					//setup gateway address byte 3
	//write thru spi communication
	SPI1SendNByte(temp_array,7);


	//setup subnet mask register
	temp_array[0] 		= MSB(W5500_CRB_SUBR_0);		//set address for common subnet mask register MSB
	temp_array[1] 		= LSB(W5500_CRB_SUBR_0);		//set address for common subnet mask register LSB
	temp_array[2] 		|= (W5500_CP_BSB_CR
						| W5500_CP_WRITE
						| W5500_CP_OM_VDLM); 		//set byte for write in to common register
	temp_array[3] 		= submask[0]; 					//setup subnet mask address byte 0
	temp_array[4] 		= submask[1]; 					//setup subnet mask address byte 1
	temp_array[5] 		= submask[2]; 					//setup subnet mask address byte 2
	temp_array[6] 		= submask[3]; 					//setup subnet mask address byte 3
	//write thru spi communication
	SPI1SendNByte(temp_array,7);


	//setup hardware address register
	temp_array[0] 		= MSB(W5500_CRB_SHAR_0);		//set address for common hardware address register MSB
	temp_array[1] 		= LSB(W5500_CRB_SHAR_0);		//set address for common hardware address register LSB
	temp_array[2] 		|= (W5500_CP_BSB_CR
						| W5500_CP_WRITE
						| W5500_CP_OM_VDLM); 		//set byte for write in to common register
	temp_array[3] 		= mac[0]; 						//setup hardware address byte 0
	temp_array[4] 		= mac[1]; 						//setup hardware address byte 1
	temp_array[5] 		= mac[2]; 						//setup hardware address byte 2
	temp_array[6] 		= mac[3]; 						//setup hardware address byte 3
	temp_array[7] 		= mac[4]; 						//setup hardware address byte 4
	temp_array[8] 		= mac[5]; 						//setup hardware address byte 5
	//write thru spi communication
	SPI1SendNByte(temp_array,9);

	//setup source IP address register
	temp_array[0] 		= MSB(W5500_CRB_SIPR_0);		//set address for source IP register MSB
	temp_array[1] 		= LSB(W5500_CRB_SIPR_0);		//set address for source IP register LSB
	temp_array[2] 		|= (W5500_CP_BSB_CR
						| W5500_CP_WRITE
						| W5500_CP_OM_VDLM); 		//set byte for write in to common register
	temp_array[3] 		= ip[0]; 						//setup source IP address byte 0
	temp_array[4] 		= ip[1]; 						//setup source IP address byte 1
	temp_array[5] 		= ip[2]; 						//setup source IP address byte 2
	temp_array[6] 		= ip[3]; 						//setup source IP address byte 3
	//write thru spi communication
	SPI1SendNByte(temp_array,7);


}
