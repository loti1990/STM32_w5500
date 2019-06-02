//In this file we will implement hendlers for GPIO

#include "GPIO.h"

void InitGPIO(void){

	//Enable GPIOA AHB1 clock source
	RCC -> AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
	//Enable GPIOB AHB1 clock source
	RCC -> AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
	//Enable SPI3 APB1 clock source 42 MHz max clock
	RCC -> APB1ENR |= RCC_APB1ENR_SPI3EN;
	//Enable SPI1 APB2 clock source 84 MHz max clock
	RCC -> APB2ENR |= RCC_APB2ENR_SPI1EN;

	/**********************************************************************************
	//////////////////////////PIN CONFIGURATION////////////////////////////////////////
	***********************************************************************************/

	//GPIOA PA8//
	GPIOA -> MODER 		|= GPIO_MODER_MODER8_0; 	//PA8 pin as output
	GPIOA -> OTYPER 	&= ~(GPIO_OTYPER_OT_8);		//PA8 output type push-pull
	GPIOA -> OSPEEDR 	|= GPIO_OSPEEDER_OSPEEDR8; 	//PA8 output speed register (very high speed)
	GPIOA -> PUPDR 		|= GPIO_PUPDR_PUPDR8_0; 	//PA8 pull-up

	/**********************************************************************************
	//////////////////////////SPI1 CONFIGURATION///////////////////////////////////////
	***********************************************************************************/

	//////////
	//SPI1_NSS hardware
	//////////
//	GPIOA -> MODER  	|= GPIO_MODER_MODER4_1; 	//PA4 pin as alternate function
//	GPIOA -> OTYPER     &= ~(GPIO_OTYPER_OT_4); 	//PA4 output type push-pull
//	GPIOA -> OSPEEDR 	|= GPIO_OSPEEDER_OSPEEDR4; 	//PA4 output speed register (very high speed)
//	GPIOA -> PUPDR		|= GPIO_PUPDR_PUPDR4_0; 	//PA4 pull-up
//	GPIOA -> AFR[0] 	|= (0x05 << 16); 			//PA4 alternate function SPI1_NSS

	//////////
	//SPI1_NSS software
	//////////
	GPIOA -> MODER		|= GPIO_MODER_MODER4_0;		//PA4 pin output mode
	GPIOA -> OTYPER 	&= ~(GPIO_OTYPER_OT_4); 	//PA4 output push-pull
	GPIOA -> OSPEEDR 	|= GPIO_OSPEEDER_OSPEEDR4; 	//PA4 output speed register (very high speed)
	GPIOA -> PUPDR		|= GPIO_PUPDR_PUPDR4_0; 	//PA4 pull-up
	GPIOA -> ODR 		|= GPIO_ODR_ODR_4;			//PA4 set in a high output logical level

	//////////
	//SPI1_CLK
	//////////
	//pin PA5 CLK configuration
	GPIOA -> MODER  	|= GPIO_MODER_MODER5_1; 	//PA5 pin as alternate function
	GPIOA -> OTYPER     &= ~(GPIO_OTYPER_OT_5); 	//PA5 output type push-pull
	GPIOA -> OSPEEDR 	|= GPIO_OSPEEDER_OSPEEDR5;  //PA5 output speed register (very high speed)
	GPIOA -> PUPDR		|= GPIO_PUPDR_PUPDR5_0; 	//PA5 pull-up
	GPIOA -> AFR[0] 	|= (0x05 << 20); 			//PA5 alternate function SPI1_CLK

	///////////
	//SPI1_MISO
	///////////
	//pin PA6 MISO configuration
	GPIOA -> MODER  	|= GPIO_MODER_MODER6_1; 	//PA6 pin as alternate function
	GPIOA -> OTYPER     &= ~(GPIO_OTYPER_OT_6); 	//PA6 output type push-pull
	GPIOA -> OSPEEDR 	|= GPIO_OSPEEDER_OSPEEDR6;  //PA6 output speed register (very high speed)
	GPIOA -> PUPDR		|= GPIO_PUPDR_PUPDR6_0; 	//PA6 pull-up
	GPIOA -> AFR[0] 	|= (0x05 << 24); 			//PA6 alternate function SPI1_MISO

	///////////
	//SPI1_MOSI
	///////////
	//pin PA7 MOSI configuration
	GPIOA -> MODER  	|= GPIO_MODER_MODER7_1; 	//PA7 pin as alternate function
	GPIOA -> OTYPER     &= ~(GPIO_OTYPER_OT_7); 	//PA7 output type push-pull
	GPIOA -> OSPEEDR 	|= GPIO_OSPEEDER_OSPEEDR7;  //PA7 output speed register (very high speed)
	GPIOA -> PUPDR		|= GPIO_PUPDR_PUPDR7_0; 	//PA7 pull-up
	GPIOA -> AFR[0] 	|= (0x05 << 28); 			//PA7 alternate function SPI1_MOSI


	/**********************************************************************************
	//////////////////////////SPI3 CONFIGURATION///////////////////////////////////////
	***********************************************************************************/

	//////////
	//SPI3_NSS
	//////////
	//pin PA15 NSS configuration
	GPIOA -> MODER  	|= GPIO_MODER_MODER15_1; 	//PA15 pin as alternate function
	GPIOA -> OTYPER     &= ~(GPIO_OTYPER_OT_15); 	//PA15 output type push-pull
	GPIOA -> OSPEEDR 	|= GPIO_OSPEEDER_OSPEEDR15; //PA15 output speed register (very high speed)
	GPIOA -> PUPDR		|= GPIO_PUPDR_PUPDR15_0; 	//PA15 pull-up
	GPIOA -> AFR[1] 	|= (0x06 << 28); 			//PA15 alternate function SPI3_NSS

	//////////
	//SPI3_CLK
	//////////
	//pin PB3 CLK configuration
	GPIOB -> MODER  	|= GPIO_MODER_MODER3_1; 	//PB3 pin as alternate function
	GPIOB -> OTYPER     &= ~(GPIO_OTYPER_OT_3); 	//PB3 output type push-pull
	GPIOB -> OSPEEDR 	|= GPIO_OSPEEDER_OSPEEDR3;  //PB3 output speed register (very high speed)
	GPIOB -> PUPDR		|= GPIO_PUPDR_PUPDR3_0; 	//PB3 pull-up
	GPIOB -> AFR[0] 	|= (0x06 << 12); 			//PB3 alternate function SPI3_CLK

	///////////
	//SPI3_MISO
	///////////
	//pin PB4 MISO configuration
	GPIOB -> MODER  	|= GPIO_MODER_MODER4_1; 	//PB4 pin as alternate function
	GPIOB -> OTYPER     &= ~(GPIO_OTYPER_OT_4); 	//PB4 output type push-pull
	GPIOB -> OSPEEDR 	|= GPIO_OSPEEDER_OSPEEDR4;  //PB4 output speed register (very high speed)
	GPIOB -> PUPDR		|= GPIO_PUPDR_PUPDR4_0; 	//PB4 pull-up
	GPIOB -> AFR[0] 	|= (0x06 << 16); 			//PB4 alternate function SPI3_MISO

	///////////
	//SPI3_MOSI
	///////////
	//pin PB5 MOSI configuration
	GPIOB -> MODER  	|= GPIO_MODER_MODER5_1; 	//PB5 pin as alternate function
	GPIOB -> OTYPER     &= ~(GPIO_OTYPER_OT_5); 	//PB5 output type push-pull
	GPIOB -> OSPEEDR 	|= GPIO_OSPEEDER_OSPEEDR5;  //PB5 output speed register (very high speed)
	GPIOB -> PUPDR		|= GPIO_PUPDR_PUPDR5_0; 	//PB5 pull-up
	GPIOB -> AFR[0] 	|= (0x06 << 20); 			//PB5 alternate function SPI3_MOSI
}


