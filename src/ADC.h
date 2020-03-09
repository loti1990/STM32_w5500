/*
 * ADC.h
 *
 */

#include "stm32f4xx.h"
#include "core_cm4.h"

#ifndef ADC_H_
#define ADC_H_

void ADC1TempInit(void); 	//Initialize ADC1 for temperature measurement

uint16_t TempSensRead(void); //Read data data register from integrated temperature sensor

void ADC1In8Init(void); 		//Initialization ADC1 on input channel 8 at PB0

uint16_t ADC1In8Read(); 	//Read converted ADC value from ADC1 on input channel 8 PB0




#endif /* ADC_H_ */
