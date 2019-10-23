/*
 * ADC.c
 *
 */
#include "ADC.h"

//Initialize ADC1 for temperature measurement
void ADC1TempInit(void){

	RCC		-> APB2ENR |= RCC_APB2ENR_ADC1EN;	//ADC1 clock enable

	//ADC 	-> CCR |=; //Enable temperature sensor

}
