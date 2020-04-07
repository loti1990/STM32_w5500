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
#include "ADC.h"
#include "DMA.h"
#include "USART.h"

void EXTI0_IRQHandler(void); 		//Initialization of handler for external interrupt on line 0
void EXTI3_IRQHandler(void); 		//Initialization of handler for external interrupt on line 3
void DMA2_Stream0_IRQHandler(void); //Initialization of handler for DMA2 interrupt on stream 0

//DEFINITIONS
//#define TH1 	3900
//#define TH2 	3600
#define RX_BUFF_SIZE 	2
#define TX_BUFF_SIZE	2

//State machine defintions
//#define ST_IDLE 	0x00
//#define ST_TH1 		0x01
//#define ST_INTEG	0x02
//#define ST_PRINT 	0x03


//GLOBAL VARIABLES

uint8_t ip[4] 					= {192,168,1,100};//{172,17,10,96}; 					//dedicated ip address for external W5500 device
uint8_t gateway[4]				= {192,168,1,1};//{172,17,10,1}; 					//gateway
uint8_t submask[4]				= {255,255,255,0}; 					//subnet mask
uint8_t mac[6]					= {0x00,0x01,0x02,0x03,0x04,0x05}; 	//dedicated mac address
uint8_t TCP_sorket_num 			= 0;								//TCP socket number form 0 to 7
uint16_t port 					= 1024; 							//TCP socket port
uint8_t rx_buff_size 			= 2; 								//Rx buff size in KB
uint8_t tx_buff_size 			= 2;							//Tx buff size in KB

//Buffers
uint8_t rx_buffer[RX_BUFF_SIZE*1024] = {0,}; 						//Rx buffer
uint8_t tx_buffer[TX_BUFF_SIZE*1024] = {0,}; 						//Tx buffer

//
//MAIN
//
int main(void){

  uint32_t ret_code_from_sysTick; 	//return code from SysTick_Config function 1 for error see core_cm4.h
  uint8_t error_hand;

//  volatile uint16_t adc_data[256];
//
//  volatile uint16_t i = 0;
//
//  volatile float temperature = 0.0;
//  volatile uint16_t temp = 0;

  //Init GPIOA
  InitGPIO();
  //Init SPI1ls
  SPI1Init();
  //USART3 init
  USART3Init(115200);
  //ADC1 enable at channel 8
  //ADC1In8Init();
  //Init ADC1 for temp sensor
  //ADC1TempInit();
  //Initialize DAM for ADC1 temperature sensor
  //DMA2ADC1Init((uint16_t)256, (uint32_t *) &ADC1 -> DR, (uint32_t *) &adc_data);
  //Enable interrupt for DMA2 stream 0
  //DMA2Stream0InterruptEnable();

  //W5500 initialize
  if(W5500SpiConnCheck() == 0){

	  W5500InitV2(ip, gateway, submask, mac);
	  //Initialize socket n for TCP protocol
	  error_hand = W5500InitTCP(TCP_sorket_num,port,TX_BUFF_SIZE,RX_BUFF_SIZE);
	  //error was occurred
	  if(error_hand !=0)return 0;
	  //Open TCP server socket
	  error_hand = W5500OpenTCPServer(TCP_sorket_num);
	  //error was occurred
	  if(error_hand !=0)return 0;

  }else{

	  return 0;
  }

  //Configure system ticks to us range
  ret_code_from_sysTick = SysTick_Config(SystemCoreClock / 1000000);

  if(ret_code_from_sysTick != 0){
	  //Error handler
  }


  //DMA2ADC1CollectNewData();
  //uint8_t data[6] = {'T','e','s','t','\r','\n'};
  //uint8_t data2[6] = {'K','o','s','t','\r','\n'};
//  uint16_t ADC_value = 0;
//  uint8_t currentState = 0x00;
//  uint64_t integral = 0;

  /* Infinite loop */
  while (1){

//	  ADC_value = ADC1In8Read();
//
//	  switch(currentState){
//
//	  case ST_IDLE:
//
//		  if(ADC_value < TH1 && ADC_value > TH2){
//			  currentState = ST_TH1;
//		  }
//
//		  break;
//
//	  case ST_TH1:
//
//		  if(ADC_value < TH2){
//			  currentState = ST_INTEG;
//		  }
//
//		  break;
//
//	  case ST_INTEG:
//
//		  if(ADC_value > TH1){
//			  currentState = ST_PRINT;
//		  }
//
//		  integral += ADC_value;
//
//		  break;
//
//	  case ST_PRINT:
//
//		  USART3SendText((uint8_t *)&integral,8);
//		  integral = 0;
//		  currentState = ST_IDLE;
//
//		  break;
//
//	  }


	  //ADC_value = ADC1In8Read();
	  //ADC_value = ADC_value >> 4;
	  //DelayMs(100);
	  //USART3SendText((uint8_t *)&ADC_value,1);
	  //DelayMs(100);
	  //USART3SendText((uint8_t *)&data2,5);



// 		ADC1 temperature read
//	  if(!(ADC1->CR2&ADC_CR2_ADON)){
//
//		  for(i = 0; i < 256; i++){
//			  if(i == 1){
//				  temp = adc_data[i];
//			  }else{
//				  temp +=adc_data[i];
//				  temp = temp >> 1;
//			  }
//		  }
//		  temperature = (((3.0*(float)temp/4095.0)-0.76)/0.0025)+25.0;
//		  DMA2ADC1CollectNewData();
//	  }

	  //temp = TempSensRead();
	  //temperature = (((3.0*(float)temp/4095.0)-0.76)/0.0025)+25.0;
	  //LED3 turn on and off in 1s interval
//	  DelayMs(1000);
//	  GPIOD -> ODR	|= GPIO_ODR_ODR_13;
//	  DelayMs(2000);
//	  GPIOD -> ODR	&= ~(GPIO_ODR_ODR_13);


	  //GPIOA ->ODR |= GPIO_ODR_ODR_8; 	//set PA8 to 1
	  //GPIOA ->ODR &= ~(GPIO_ODR_ODR_8);	//set PA8 to 0

	  //DelayUs(1);
	  //SPI1SendNByte(test_data,4);


  }
}

//External interrupt handler on line 3
void EXTI3_IRQHandler(void){

	//w5500 socket number and status
	volatile uint8_t w5500_socket_interrupt_status;
	//uint16_t recv_len = 0;
	//Check if interrupt occurred in W5500 side
	if((EXTI -> PR & EXTI_PR_PR3) != 0){
		//check interrupt status
		w5500_socket_interrupt_status = CheckInterruptStatus();

		USART3SendText((uint8_t *)&w5500_socket_interrupt_status,1);

		switch(w5500_socket_interrupt_status & 0x1F){

		//Disconnect interrupt
		case W5500_SR_IR_DISCON:
			W5500OpenTCPServer(((w5500_socket_interrupt_status & 0xE0) >> 5));

			break;

		//Connect interrupt
		case W5500_SR_IR_CON:

			break;

		//Receive interrupt
		case W5500_SR_IR_RECV:
			ReadRecvSizeAndData(((w5500_socket_interrupt_status & 0xE0) >> 5), rx_buffer);
			if(rx_buffer[0] == 0x30){
				SendData(((w5500_socket_interrupt_status & 0xE0) >> 5),tx_buffer,2048);

			}
			//USART3SendText((uint8_t *)&recv_len,2);
			//USART3SendText((uint8_t *)&rx_buffer,1024);
			break;

		//Send OK
		case W5500_SR_IR_SEND_OK:

			break;


		default:
			USART3SendText((uint8_t *)&w5500_socket_interrupt_status,1);
			if((GPIOD -> ODR & GPIO_ODR_ODR_13) != 0){

				GPIOD -> ODR	&= ~(GPIO_ODR_ODR_13); 	//LED3 off
			}else{

				GPIOD -> ODR	|= GPIO_ODR_ODR_13; 	//LED3 on
			}
			break;

		}
//		if(((CheckInterruptStatus() & 0xE0) >> 5) == 0){ 		//check on which socket occurred interrupt
//
//			if((GPIOD -> ODR & GPIO_ODR_ODR_13) != 0){
//
//				GPIOD -> ODR	&= ~(GPIO_ODR_ODR_13); 	//LED3 off
//			}else{
//
//				GPIOD -> ODR	|= GPIO_ODR_ODR_13; 	//LED3 on
//			}
//		}

		EXTI -> PR |= EXTI_PR_PR3; 	//Clear flag this is necessary
	}
}

//External interrupt handler on line 0
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

//DMA2 interrupt handler on stream 0
void DMA2_Stream0_IRQHandler(void){

	//Check if interrupt was ocured on stream 0 transfer complete
	if(DMA2 -> LISR & DMA_LISR_TCIF0){

		if((GPIOD -> ODR & GPIO_ODR_ODR_13) != 0){

			GPIOD -> ODR	&= ~(GPIO_ODR_ODR_13); 	//LED3 off
		}else{

			GPIOD -> ODR	|= GPIO_ODR_ODR_13; 	//LED3 on
		}
	}

	DMA2_Stream0 	-> CR		&= ~(DMA_SxCR_EN); 		//Disable DMA2 Stream 0 Chanel0
	ADC1 			-> CR2 		&= ~(ADC_CR2_DMA); 		//Disable DMA in adc1 CR
	ADC1 			-> CR2 		&= ~(ADC_CR2_ADON); 	//Turn ADC1 to OFF state

	DMA2 -> LIFCR	|= DMA_LIFCR_CTCIF0; 				//Clear interrupt flag for transfer complete
	DMA2 -> LIFCR	|= DMA_LIFCR_CHTIF0; 				//Clear interrupt flag for transfer half transfer
}

//USART3 interrupt handler
void USART3_IRQHandler(void){
	if(USART3 -> SR & USART_SR_RXNE){
		uint8_t temp = USART3 -> DR;
		if(temp == 0x30){
			uint16_t ADC_value = ADC1In8Read();
			//ADC_value = ADC_value >> 4;
			USART3SendText((uint8_t *)&ADC_value,2);
		}
		//Clear interrupt if you are not reading form USART3 DR
		//USART3 -> SR		&= ~(USART_SR_RXNE);
	}

}

//ADC interrupt handler
void ADC_IRQHandler(void){

	//Check for analog watchdog interrupt occured
	if(ADC1 -> SR & ADC_SR_AWD){

		if((GPIOD -> ODR & GPIO_ODR_ODR_13) != 0){

			GPIOD -> ODR	&= ~(GPIO_ODR_ODR_13); 	//LED3 off
		}else{

			GPIOD -> ODR	|= GPIO_ODR_ODR_13; 	//LED3 on
		}
	ADC1 -> SR 	&= ~(ADC_SR_AWD); 	//Clear watchdog interrupt flag
	}

}
