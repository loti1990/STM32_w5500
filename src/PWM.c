/*
 * PWM.c
 *
 */

#include "PWM.h"

//Initialized PWM on PIN PB3 (TIM3_CH4)
void InitPWMPB1(){

	//Enable system clock to TIM3
	//Enable TIM3 clock enable clk source 84 MHz
	RCC -> APB1ENR |= RCC_APB1ENR_TIM3EN;

	//Frequency of the PWM output signal was determinated with equation
	// fPWM = 84 MHz / (ARR * PSC)
	// we want frequency of 1 kHz
	// PSR * ARR = 84 MHz / 1kHz = 84000
	// PSC = 84
	// ARR = 1000

	TIM3 -> PSC 	= 84;					//Set presceler register to 84

	TIM3 -> ARR 	= 1000;					//Set auto - reload register to 1000

	TIM3 -> CCMR2 	|= (TIM_CCMR2_OC4M_2 | TIM_CCMR2_OC4M_1); 	//PWM mode 1

	TIM3 -> CCMR2 	|= TIM_CCMR2_OC4PE;  	//Enable preload register on CH4

	TIM3 -> CCER 	|= TIM_CCER_CC4E; 		//Capture/compere enable on CH4

	TIM3 -> CR1 	|= TIM_CR1_ARPE;		//Auto reload preload register

	TIM3 -> EGR 	|= TIM_EGR_UG; 			//Generate update on the registers

	TIM3 -> CR1 	|= TIM_CR1_CEN; 		//Enable Timer 3


	TIM3 -> CCR4 	= 700; 					//Set PWM to 50 %




	/*Pulse width modulation mode allows generating a signal with a frequency determined by the
	value of the TIMx_ARR register and a duty cycle determined by the value of the
	TIMx_CCRx register.
	The PWM mode can be selected independently on each channel (one PWM per OCx
	output) by writing 110 (PWM mode 1) or ‘111 (PWM mode 2) in the OCxM bits in the
	TIMx_CCMRx register. The user must enable the corresponding preload register by setting
	the OCxPE bit in the TIMx_CCMRx register, and eventually the auto-reload preload register
	by setting the ARPE bit in the TIMx_CR1 register.
	As the preload registers are transferred to the shadow registers only when an update event
	occurs, before starting the counter, the user has to initialize all the registers by setting the
	UG bit in the TIMx_EGR register.
	OCx polarity is software programmable using the CCxP bit in the TIMx_CCER register. It
	can be programmed as active high or active low. OCx output is enabled by the CCxE bit in
	the TIMx_CCER register. Refer to the TIMx_CCERx register description for more details.
	In PWM mode (1 or 2), TIMx_CNT and TIMx_CCRx are always compared to determine
	whether TIMx_CCRx≤TIMx_CNT or TIMx_CNT≤TIMx_CCRx (depending on the direction of
	the counter). However, to comply with the ETRF (OCREF can be cleared by an external
	event through the ETR signal until the next PWM period), the OCREF signal is asserted
	only:
	• When the result of the comparison changes, or
	• When the output compare mode (OCxM bits in TIMx_CCMRx register) switches from
	the “frozen” configuration (no comparison, OCxM=‘000) to one of the PWM modes
	(OCxM=‘110 or ‘111).
	This forces the PWM by software while the timer is running.
	General-purpose timers (TIM2 to TIM5)
	The timer is able to generate PWM in edge-aligned mode or center-aligned mode
	depending on the CMS bits in the TIMx_CR1 register.*/


}
