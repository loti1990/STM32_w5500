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


#endif /* ADC_H_ */
