/*
 * DMA.h
 */

#ifndef DMA_H_
#define DMA_H_

#include "stm32f4xx.h"

void DMA2ADC1Init(uint16_t data_num, uint32_t *peripheral_address, uint32_t *memory_address);		//Direct memory access initialization for ADC1 peripheral

void DMA2Stream0InterruptEnable(void); 																//Direct memory access enable interrupt on stream 0

void DMA2ADC1CollectNewData(void); 																	//Collect new data from ADC1

#endif /* DMA_H_ */
