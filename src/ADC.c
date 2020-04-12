/*
 * ADC.c
 *
 */
#include "ADC.h"

//Initialize ADC1 for temperature measurement
void ADC1TempInit(){

	RCC		-> APB2ENR 	|= RCC_APB2ENR_ADC1EN;	//ADC1 clock enable default APB2 clock was 84 MHz

	ADC1 	-> CR2 		&= ~(ADC_CR2_ADON);		//Turn off ADC1

	ADC 	-> CCR 		|= ADC_CCR_TSVREFE;		//Enable temperature sensor

	ADC 	-> CCR 		|= ADC_CCR_ADCPRE_0; 	//For all ADC clock was set to APB2/4(prescaler) = 84 MHz /4 = 21 MHz (1 cycle was 48 ns)

	ADC1 	-> SQR1		&= ~(ADC_SQR1_L_0 | ADC_SQR1_L_1 | ADC_SQR1_L_2 | ADC_SQR1_L_3); 	// One conversion

	ADC1	-> SQR3 	|= ADC_SQR3_SQ1_4; 		//Select Channel 16 (temp sensor) to be converted in first and only sequance

	ADC1 	-> SMPR1 	|= (ADC_SMPR1_SMP16_0 | ADC_SMPR1_SMP16_1 | ADC_SMPR1_SMP16_2); 	//For temperature measurement the sampling time must be > 10 us so 480 cycle * 48 ns = 23 us

	ADC1 	-> CR1 		&= ~(ADC_CR1_RES_0 | ADC_CR1_RES_1);	//Setup 12 bit resolution (take 15 ADC clock cycle)

	//ADC1 	-> CR1 		|= (ADC_CR1_RES_1);		//Setup 8 bit resolution (take 11 ADC clock cycle)

	ADC1 	-> CR2 		|=(ADC_CR2_CONT); 		//Continious convertion mode

	//ADC1 	-> CR2 		|= ADC_CR2_ADON;		//Turn on ADC1

}

//Read temperature value from internal temperature sensor
uint16_t TempSensRead(){

	ADC1 	-> CR2 		|= ADC_CR2_SWSTART;		//Start conversion


	while(!(ADC1 -> SR & ADC_SR_EOC)); 			//Wait on EOC status flag

	return (uint16_t) ADC1 -> DR;
}


//ADC1 IN8 on PB0 initialization
void ADC1In8Init(){

	RCC		-> APB2ENR 	|= RCC_APB2ENR_ADC1EN;	//ADC1 clock enable default APB2 clock was 84 MHz

	ADC1 	-> CR2 		&= ~(ADC_CR2_ADON);		//Turn off ADC1

	ADC 	-> CCR 		|= ADC_CCR_ADCPRE_0; 	//For all ADC clock was set to APB2/4(prescaler) = 84 MHz /4 = 21 MHz (1 cycle was 48 ns)

	ADC1 	-> CR1 		&= ~(ADC_CR1_RES_0 | ADC_CR1_RES_1);	//Setup 12 bit resolution (take 15 ADC clock cycle)

	ADC1	-> SQR3 	|= ADC_SQR3_SQ1_3; 		//Select Channel 8 (at GPIOB PB0) to be converted in first and only sequance

	ADC1 	-> SMPR2 	|= ADC_SMPR2_SMP8_2; 	//Setup sampling time to 480 cycle * 48 ns = 23 us

	ADC1 	-> SQR1		&= ~(ADC_SQR1_L_0 | ADC_SQR1_L_1 | ADC_SQR1_L_2 | ADC_SQR1_L_3); 	// One conversion

	//Analog watchdog settings

	ADC1 	-> CR1 		|= ADC_CR1_AWDSGL; 		//Enable watchdog on a single chanel defined below

	ADC1 	-> CR1 		|= ADC_CR1_AWDCH_3; 	//Select analog watchdog channel 8

	ADC1 	-> CR1 		|= ADC_CR1_AWDIE; 		//Interrupt enable for watchdog

	ADC1 	-> CR1 		|= ADC_CR1_AWDEN; 		//Enable analog watchdog on regular chanel

	ADC1   	-> LTR 		= 3900;			//ADC1 watchdog lower treshold register

	ADC1  	-> HTR 		= 4095; 		//ADC1 watchdog higher treshold register

	NVIC -> ISER[0] 	|= (1 << ADC_IRQn); 	//Enable ADC interrupt

	NVIC -> IP[ADC_IRQn] 		= (uint8_t) 0x02;		//set priority of ADC_IRQ to 2 (lower are the number the higher are priority)

	//Analog watchdog settings

	ADC1 	-> CR2 		|= ADC_CR2_ADON;		//Turn on ADC1

	//ADC1 	-> CR2 		|=(ADC_CR2_CONT); 		//Continious convertion mode
}

//Read ADC value form channel 8 at PB0
uint16_t ADC1In8Read(){

	ADC1 	-> CR2 		|= ADC_CR2_SWSTART;		//Start conversion


	while(!(ADC1 -> SR & ADC_SR_EOC)); 			//Wait on EOC status flag

	return (uint16_t) ADC1 -> DR;
}




