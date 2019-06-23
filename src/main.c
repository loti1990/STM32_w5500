/*
******************************************************************************
File:     main.c
Info:     Generated by Atollic TrueSTUDIO(R) 9.3.0   2019-03-01

The MIT License (MIT)
Copyright (c) 2019 STMicroelectronics

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

******************************************************************************
*/

/* Includes */
#include "stm32f4xx.h"
#include "stm32f4xx_it.h"
#include "GPIO.h"
#include "SPI.h"
#include "W5500.h"

void EXTI0_IRQHandler(void); 		//Initialization of handler for external interrupt on line 0
void EXTI3_IRQHandler(void); 		//Initialization of handler for external interrupt on line 3

//
//MAIN
//
int main(void){

  uint32_t ret_code_from_sysTick; 	//return code from SysTick_Config function 1 for error see core_cm4.h
  uint8_t test_data[4] = {0x00,0x00,0x00,0xaa};
  uint8_t test_receive = 0x00;

  //Init GPIOA
  InitGPIO();
  //Init SPI3
  SPI3Init();
  //Init SPI1
  SPI1Init();
  //W5500 initialize
  W5500Init();

  //Configure system ticks to us range
  ret_code_from_sysTick = SysTick_Config(SystemCoreClock / 1000000);

  if(ret_code_from_sysTick != 0){
	  //Error heandler
  }


  //ADDED COMENT FOR GIT EXAMPLE
  /* Infinite loop */
  while (1){

	  //LED3 turn on and off in 1s interval
//	  DelayMs(1000);
//	  GPIOD -> ODR	|= GPIO_ODR_ODR_13;
//	  DelayMs(2000);
//	  GPIOD -> ODR	&= ~(GPIO_ODR_ODR_13);


	  //GPIOA ->ODR |= GPIO_ODR_ODR_8; 	//set PA8 to 1
	  //GPIOA ->ODR &= ~(GPIO_ODR_ODR_8);	//set PA8 to 0

	  //DelayUs(1);
	  //SPI1SendNByte(test_data,4);

//	  test_data[0] = 0x00;
//	  test_data[1] = 0x09;
//	  test_data[2] = 0x04;
//	  SPI1SendNByte(test_data,4);
//	  test_data[0] = 0x00;
//	  test_data[1] = 0x09;
//	  test_data[2] = 0x00;
//	  test_receive = SPI1SendNByteReceive1Byte(test_data,3);

//	  test_data[0] = 0x00;
//	  test_data[1] = 0x0f;
//	  test_data[2] = 0x00;
//	  test_receive = SPI1SendNByteReceive1Byte(test_data,3);
//
//	  test_data[0] = 0x00;
//	  test_data[1] = 0x10;
//	  test_data[2] = 0x00;
//	  test_receive = SPI1SendNByteReceive1Byte(test_data,3);
//
//	  test_data[0] = 0x00;
//	  test_data[1] = 0x11;
//	  test_data[2] = 0x00;
//	  test_receive = SPI1SendNByteReceive1Byte(test_data,3);
//
//	  test_data[0] = 0x00;
//	  test_data[1] = 0x12;
//	  test_data[2] = 0x00;
//	  test_receive = SPI1SendNByteReceive1Byte(test_data,3);
//
//	  test_data[0] = 0x00;
//	  test_data[1] = 0x13;
//	  test_data[2] = 0x00;
//	  test_receive = SPI1SendNByteReceive1Byte(test_data,3);



	  //Enable SPI3
	  //SPI3 -> CR1 	|= SPI_CR1_SPE;
	  //Disable SPI3
	  //SPI3 -> CR1 	&= ~(SPI_CR1_SPE);
  }
}

//External interrupt handler on line 3
void EXTI3_IRQHandler(void){
	if((EXTI -> PR & EXTI_PR_PR3) != 0){
		if((GPIOD -> ODR & GPIO_ODR_ODR_13) != 0){

			GPIOD -> ODR	&= ~(GPIO_ODR_ODR_13); 	//LED3 off
		}else{

			GPIOD -> ODR	|= GPIO_ODR_ODR_13; 	//LED3 on
		}
		EXTI -> PR |= EXTI_PR_PR3; 	//Clear flag this is necessary
	}
}

//External interrupt handler on line 3
void EXTI0_IRQHandler(void){
	if((EXTI -> PR & EXTI_PR_PR0) != 0){
		if((GPIOD -> ODR & GPIO_ODR_ODR_13) != 0){

			GPIOD -> ODR	&= ~(GPIO_ODR_ODR_13); 	//LED3 off
		}else{

			GPIOD -> ODR	|= GPIO_ODR_ODR_13; 	//LED3 on
		}
		EXTI -> PR |= EXTI_PR_PR0; 	//Clear flag this is necessary
	}
}
