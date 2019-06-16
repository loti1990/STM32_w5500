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
uint8_t CR_SIPR_W5500[7] = {0x00,0x0f,0x04,0xc0,0xa8,0x01,0x64};

//Initialize W5500 ethernet module
void W5500Init(void){

	//enable bing
	SPI1SendNByte(CR_MR_W5500,4);

	//setup gateway IP address
	SPI1SendNByte(CR_GAR_W5500,7);

	//setup subnet mask register
	SPI1SendNByte(CR_SUBR_W5500,7);

	//setup hardware address register
	SPI1SendNByte(CR_SHAR_W5500,9);

	//setup source IP address register
	SPI1SendNByte(CR_SIPR_W5500,7);

}
