//In this file we will implement handlers for GPIO

#include "GPIO.h"

void TestInitGpioAsm(void){

	//Enable GPIOD AHB1 clock source
	//RCC -> AHB1ENR |= RCC_AHB1ENR_GPIODEN;

	asm volatile(
			"//Enable GPIOD AHB1 clock source\n\t"
			"LDR 	r0,=0x40023800 		//RCC base address\n\t"
			"LDR 	r1,[r0,#48]			//Read RCC AHB1 peripheral set register\n\t"
			"ORR 	r1,r1,#0x08 		//Logical or with readable RCC AHB1 register\n\t"
			"STR 	r1,[r0,#48] 		//Enable clock to GPIOD peripheral in RCC AHB1 peripheral clock enable register\n\t"
	);

	//0x4002 0C00 //GPIOD mode register
	asm volatile(
			"LDR	r0, =0x40020C00 	//base address of GPIOD\n\t"

			"//PD13 pin as output\n\t"
			"LDR 	r1,[r0] 			//load GPIOD MODER register\n\t"
			"ORR 	r1,r1,#0x4000000 	//Logical OR\n\t"
			"STR 	r1,[r0] 			//store r1 in to address specified in r0\n\t"

			"//PD13 output type push-pull\n\t"
			"LDR	r1,[r0,#4]			//store value of GPIOD port output type register\n\t"
			"BIC 	r1,r1,0xFFFFDFFF	//clear bit 13 in GPIO OTYPE register\n\r"
			"STR 	r1,[r0,#4] 			//store r1 in to address specified in r0 with offset 4 byte\n\t"

			"//PD13 output speed register (medium speed)\n\t"
			"LDR	r1,[r0,#8]			//store value of the GPIOD OSPEEDER in to r1\n\t"
			"ORR 	r1,r1,#0x4000000 	//set bit 26 for GPIOD pin 13 medium speed\n\t"
			"STR 	r1,[r0,#8] 			//store r1 in to address specified in r0 with offset 8 byte\n\t"

			"//PD13 pull-up\n\t"
			"LDR	r1,[r0,#12]			//store value of the GPIOD PUPDR in to r1\n\t"
			"ORR	r1,r1,#0x4000000	//Logical OR\n\t"
			"STR 	r1,[r0,#12] 		//store r1 in to address specified in r0 with offset 12 byte\n\t"

			"//TURN ON LED ON PD13\n\t"
			"LDR	r1,=0x2000			//store value in to r1 for turning on PD3\n\t"
			"STR 	r1,[r0,#24] 		//store r1 in to address specified in r0 with offset 24 byte\n\t"
	);

	/*
	//////////////////////////////////////
	//GPIOD PD13/LED3 on discovery board//
	//////////////////////////////////////
	GPIOD -> MODER 		|= GPIO_MODER_MODER13_0;		//PD13 pin as output
	GPIOD -> OTYPER 	&= ~(GPIO_OTYPER_OT_13);		//PD13 output type push-pull
	GPIOD -> OSPEEDR 	|= GPIO_OSPEEDER_OSPEEDR13_0; 	//PD13 output speed register (medium speed)
	GPIOD -> PUPDR 		&= ~(GPIO_PUPDR_PUPDR13); 		//PD13 pull-up
	*/

}

void InitGPIO(void){

	/*************************************************
	////////////ENABLE CLK FOR PERIPHERALS////////////
	*************************************************/

	//Enable GPIOA AHB1 clock source
	RCC -> AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
	//Enable GPIOB AHB1 clock source
	RCC -> AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
	//Enable GPIOD AHB1 clock source
	RCC -> AHB1ENR |= RCC_AHB1ENR_GPIODEN;
	//Enable SPI3 APB1 clock source 42 MHz max clock
	RCC -> APB1ENR |= RCC_APB1ENR_SPI3EN;
	//Enable USART3 CLK enable clk source 42 Mhz
	RCC -> APB1ENR |= RCC_APB1ENR_USART3EN;
	//Enable I2C1 clock enable clk source 42 MHz
	RCC -> APB1ENR |= RCC_APB1ENR_I2C1EN;
	//Enable SPI1 APB2 clock source 84 MHz max clock
	RCC -> APB2ENR |= RCC_APB2ENR_SPI1EN;
	//Enable SYSCONFIG for interrupt purpose
	RCC -> APB2ENR |= RCC_APB2ENR_SYSCFGEN;



	/**********************************************************************************
	//////////////////////////PIN CONFIGURATION////////////////////////////////////////
	***********************************************************************************/


				/*************************************************
				////////////////////INPUTS////////////////////////
				*************************************************/

	//////////////////////////////////////////////////////////
	//GPIOA PA3 configure for interrupt generated from W5500//
	//////////////////////////////////////////////////////////
	GPIOA -> MODER 		&= ~(GPIO_MODER_MODER3); 		//PA3 pin as input
	//GPIOA -> PUPDR 		&= ~(GPIO_PUPDR_PUPDR3); 	//PA3 no pull-up, pull-down
	GPIOA -> PUPDR 		|= GPIO_PUPDR_PUPDR3_0; 		//PA3 pull-up
	//Enable external interrupt on line 3
	//NVIC_EnableIRQ(EXTI3_IRQn);						//Enable external interrupt
	NVIC -> ISER[0] 	|= (1 << EXTI3_IRQn); 			//Enable external interrupt
	//NVIC_SetPriority(EXTI3_IRQn,1); 					//set priority of EXTI3_IRQn to 1 (lower are the number the higher are priority)
	NVIC -> IP[EXTI3_IRQn] 		= (uint8_t) 0x02;		//set priority of EXTI3_IRQn to 2 (lower are the number the higher are priority)
	//Select external interrupt in SYSCFG register
	SYSCFG -> EXTICR[0] |= SYSCFG_EXTICR1_EXTI3_PA;		//PA3 as external interrupt setting up in EXTICR1
	//Interrupt was generated in high to low voltage transition
	EXTI -> FTSR 		|= EXTI_FTSR_TR3;				//interrupt generated at falling edge
	//Setup masked register
	//0- masked (disabled), 1- not masked (enabled)
	EXTI -> IMR			|= EXTI_IMR_MR3; 				//Enable external interrupt at pin 3

	/////////////////////////////////////////////////////////
	//GPIOA PA0 user button configure as external interrupt//
	/////////////////////////////////////////////////////////
	GPIOA -> MODER 		&= ~(GPIO_MODER_MODER0); 		//PA0 pin as input
	GPIOA -> PUPDR 		&= ~(GPIO_PUPDR_PUPDR0); 		//PA0 no pull-up, pull-down
	//Enable external interrupt on line 0
	NVIC -> ISER[0] 	|= (1 << EXTI0_IRQn); 			//Enable external interrupt
	NVIC -> IP[EXTI0_IRQn] 		= (uint8_t) 0x01;		//set priority of EXTI3_IRQn to 1 (lower are the number the higher are priority)
	//Select external interrupt in SYSCFG register
	SYSCFG -> EXTICR[0] |= SYSCFG_EXTICR1_EXTI0_PA;		//PA0 as external interrupt setting up in EXTICR1
	//Interrupt was generated in low to high voltage transition
	EXTI -> RTSR 		|= EXTI_RTSR_TR0;				//interrupt generated at rising edge
	//Setup masked register
	//0- masked (disabled), 1- not masked (enabled)
	EXTI -> IMR			|= EXTI_IMR_MR0; 				//Enable external interrupt at pin 0


	//////////////////////////////////////////////////////////
	//GPIOB PB0 configure for ADC1 IN8////////////////////////
	//////////////////////////////////////////////////////////
	GPIOB -> MODER 		|= GPIO_MODER_MODER0; 			//PB0 analog mode
	GPIOB -> PUPDR 		&= ~(GPIO_PUPDR_PUPDR0);	 	//PB0 no pull-up or pull-down



					/*************************************************
					////////////////////OUTPUTS///////////////////////
					*************************************************/


	/////////////
	//GPIOA PA8//
	/////////////
	GPIOA -> MODER 		|= GPIO_MODER_MODER8_0; 		//PA8 pin as output
	GPIOA -> OTYPER 	&= ~(GPIO_OTYPER_OT_8);			//PA8 output type push-pull
	GPIOA -> OSPEEDR 	|= GPIO_OSPEEDER_OSPEEDR8; 		//PA8 output speed register (very high speed)
	GPIOA -> PUPDR 		|= GPIO_PUPDR_PUPDR8_0; 		//PA8 pull-up

	//////////////////////////////////////
	//GPIOD PD13/LED3 on discovery board//
	//////////////////////////////////////
	GPIOD -> MODER 		|= GPIO_MODER_MODER13_0;		//PD13 pin as output
	GPIOD -> OTYPER 	&= ~(GPIO_OTYPER_OT_13);		//PD13 output type push-pull
	GPIOD -> OSPEEDR 	|= GPIO_OSPEEDER_OSPEEDR13_0; 	//PD13 output speed register (medium speed)
	GPIOD -> PUPDR 		&= ~(GPIO_PUPDR_PUPDR13); 		//PD13 pull-up

	////////////////////////////////////////////
	//GPIOA PA2 pin for reset control in W5500//
	////////////////////////////////////////////
	GPIOA -> MODER 		|=  GPIO_MODER_MODER2_0; 		//PA2 pin as output
	GPIOA -> OTYPER 	&= ~(GPIO_OTYPER_OT_2);			//PA2 output type push-pull
	GPIOA -> OSPEEDR 	|= GPIO_OSPEEDER_OSPEEDR2_0; 	//PA2 output speed register (medium speed)
	GPIOA -> PUPDR 		&= ~(GPIO_PUPDR_PUPDR2); 		//PA2 pull-up
	GPIOA -> ODR 		|= GPIO_ODR_ODR_2; 				//Enable W5500 module


	/**********************************************************************************
	//////////////////////////USART3 CONFIGURATION/////////////////////////////////////
	***********************************************************************************/

	//////////
	//USART3 RX
	//////////
	GPIOB -> MODER  	|= GPIO_MODER_MODER11_1; 	//PB11 pin as alternate function
	GPIOB -> OTYPER     &= ~(GPIO_OTYPER_OT_11); 	//PB11 output type push-pull
	GPIOB -> OSPEEDR 	|= GPIO_OSPEEDER_OSPEEDR11; //PB11 output speed register (very high speed)
	GPIOB -> PUPDR		|= GPIO_PUPDR_PUPDR11_0; 	//PB11 pull-up
	GPIOB -> AFR[1] 	|= (0x07 << 12); 			//PB11 alternate function USART3 RX


	//////////
	//USART3 TX
	//////////
	GPIOB -> MODER  	|= GPIO_MODER_MODER10_1; 	//PB10 pin as alternate function
	GPIOB -> OTYPER     &= ~(GPIO_OTYPER_OT_10); 	//PB10 output type push-pull
	GPIOB -> OSPEEDR 	|= GPIO_OSPEEDER_OSPEEDR10; //PB10 output speed register (very high speed)
	GPIOB -> PUPDR		|= GPIO_PUPDR_PUPDR10_0; 	//PB10 pull-up
	GPIOB -> AFR[1] 	|= (0x07 << 8); 			//PB10 alternate function USART3 TX


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

	/**********************************************************************************
	//////////////////////////I2C1 CONFIGURATION///////////////////////////////////////
	***********************************************************************************/

	///////////
	//I2C1_SCL
	///////////
	//pin PB6 SCL configuration
	GPIOB -> MODER  	|= GPIO_MODER_MODER6_1; 		//PB6 pin as alternate function
	GPIOB -> OTYPER 	|= GPIO_OTYPER_OT_6; 			//PB6 output type open-drain
	GPIOB -> OSPEEDR 	|= GPIO_OSPEEDER_OSPEEDR6_0;  	//PB6 output speed register (medium speed)
	//GPIOB -> PUPDR		&= ~(GPIO_PUPDR_PUPDR6); 		//PB6 no pull-up, pull-down
	GPIOB -> PUPDR 		|= GPIO_PUPDR_PUPDR6_0;			//Pull up for test
	GPIOB -> AFR[0] 	|= (0x04 << 24);				//PB6 alternate function I2C1_SCL


	///////////
	//I2C1_SDA
	///////////
	//pin PB7 SDA configuration
	GPIOB -> MODER  	|= GPIO_MODER_MODER7_1; 		//PB7 pin as alternate function
	GPIOB -> OTYPER 	|= GPIO_OTYPER_OT_7; 			//PB7 output type open-drain
	GPIOB -> OSPEEDR 	|= GPIO_OSPEEDER_OSPEEDR7_0;  	//PB7 output speed register (medium speed)
	GPIOB -> PUPDR		&= ~(GPIO_PUPDR_PUPDR7); 		//PB7 no pull-up, pull-down
	GPIOB -> AFR[0] 	|= (0x04 << 28);				//PB7 alternate function I2C1_SDA

}


