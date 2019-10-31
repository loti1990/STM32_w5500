/*
 * DMA.c
 */

#include "DMA.h"

/*
 * DMA initialization function for ADC1 peripheral
 * */
void DMA2ADC1Init(uint16_t data_num, uint32_t *peripheral_address, uint32_t *memory_address){

	//Enable DMA2 AHB1 clock source
	RCC -> AHB1ENR |= RCC_AHB1ENR_DMA2EN;

	//DMA2_Stream0 CR configurations

	DMA2_Stream0 -> CR		&= ~(DMA_SxCR_EN); 												//Disable DMA

	DMA2_Stream0 -> CR		&= ~(DMA_SxCR_CHSEL_0 | DMA_SxCR_CHSEL_1 | DMA_SxCR_CHSEL_2); 	//Stream 0 Chennel 0 select for ADC1 DMA

	DMA2_Stream0 -> CR		&= ~(DMA_SxCR_MBURST_0 | DMA_SxCR_MBURST_1); 					//Memory burst transfer configuration -> single transfer

	DMA2_Stream0 -> CR		&= ~(DMA_SxCR_PBURST_0 | DMA_SxCR_PBURST_1); 					//Peripheral burst transfer configuration -> single transfer

	DMA2_Stream0 -> CR		&= ~(DMA_SxCR_CT); 												//Current target -> the current target memory is Memory 0 (addressed by the DMA_SxM0AR pointer)

	DMA2_Stream0 -> CR		&= ~(DMA_SxCR_DBM); 											//Double buffer mode -> no buffer switching at the end of transfer

	DMA2_Stream0 -> CR		|= (DMA_SxCR_PL_0 | DMA_SxCR_PL_1); 							//Priority level -> very high

	DMA2_Stream0 -> CR		&= ~(DMA_SxCR_PINCOS);											//Peripheral increment offset size -> the offset size for the peripheral address calculation is linked to the PSIZE

	DMA2_Stream0 -> CR		|= (DMA_SxCR_MSIZE_0); 											//Memory data size -> half-word (16 - bit)

	DMA2_Stream0 -> CR		|= (DMA_SxCR_PSIZE_0);											//Peripheral data size -> half-word (16 - bit)

	DMA2_Stream0 -> CR		|= (DMA_SxCR_MINC);												//Memory increment mode -> memory address pointer is incremented after each data transfer (increment is done according to MSIZE)

	DMA2_Stream0 -> CR		&= ~(DMA_SxCR_PINC); 											//Peripheral increment mode -> peripheral address pointer is fixed

	DMA2_Stream0 -> CR		|= (DMA_SxCR_CIRC); 											//Circular mode -> enabled

	DMA2_Stream0 -> CR		&= ~(DMA_SxCR_DIR_0 | DMA_SxCR_DIR_1); 							//Data transfer direction -> peripheral-to-memory

	DMA2_Stream0 -> CR		&= ~(DMA_SxCR_PFCTRL); 											//Peripheral flow controller -> the DMA is the flow controller

	DMA2_Stream0 -> CR		|= (DMA_SxCR_TCIE); 											//Transfer complete interrupt -> enable

	DMA2_Stream0 -> CR		&= ~(DMA_SxCR_HTIE | DMA_SxCR_TEIE | DMA_SxCR_DMEIE); 			//Half transfer interrupt -> disable; Transfer error interrupt -> disable; Direct mode error interrupt -> disable

	//Data length to be transfered
	DMA2_Stream0 -> NDTR 	= data_num;								//Number of data items to transfer

	//Peripheral address register
	DMA2_Stream0 -> PAR 	= (uint32_t) peripheral_address;		//Peripheral address

	//DMA stream 0 memory 0 address register
	DMA2_Stream0 -> M0AR	= (uint32_t) memory_address;			//Memory address

}

//DMA2 enable interrupt on stream line 0
void DMA2Stream0InterruptEnable(void){

	//Enable DMA interrupt on stream 0
	NVIC_EnableIRQ(DMA2_Stream0_IRQn);

	//Setup DMA priority on stream 0
	NVIC_SetPriority(DMA2_Stream0_IRQn,1);

}

void DMA2ADC1CollectNewData(void){

	  DMA2_Stream0 	-> CR		|= (DMA_SxCR_EN); 		//Enable DAM2
	  ADC1 			-> CR2 		|= (ADC_CR2_DMA); 		//Enable DMA on ADC1
	  ADC1 			-> CR2 		|= ADC_CR2_ADON; 		//Turn ADC1 to ON state
	  ADC1 			-> CR2 		|= ADC_CR2_SWSTART; 	//Software start ADC1
}
