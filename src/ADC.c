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

	ADC1 	-> SMPR1 	|= (ADC_SMPR1_SMP16_0 | ADC_SMPR1_SMP16_1 | ADC_SMPR1_SMP16_2); 	//For temperature measurement the sampling time must be > 10 us so 480 cycle * 48 ns = 2,3 ms

	ADC1 	-> CR1 		&= ~(ADC_CR1_RES_0 | ADC_CR1_RES_1);	//Setup 12 bit resolution (take 15 ADC clock cycle

	ADC1 	-> CR2 		|= ADC_CR2_ADON;		//Turn on ADC1

}

uint16_t TempSensRead(){

	ADC1 	-> CR2 		|= ADC_CR2_SWSTART;		//Start conversion


	while(!(ADC1 -> SR & ADC_SR_EOC)); 			//Wait on EOC status flag

	return (uint16_t) ADC1 -> DR;
}
