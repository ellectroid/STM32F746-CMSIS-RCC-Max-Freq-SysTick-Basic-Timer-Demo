#include "bsctmr.h"

void basic_timer_setup(TIM_TypeDef *TMR) {
	TMR->CR1 |= TIM_CR1_ARPE | TIM_CR1_URS; //ARR is buffered | only overflow/underflow generates update event.

	TMR->PSC = (108000U / 2U) - 1U; //APB1 is 54MHz, timer is 2x APB1 Freq, so now the timer is at 2kHz; 16-bit value!!! 65535 max!
	TMR->ARR = 2000U-1U; //2000 ticks at 2kHz is 1s
	TMR->CNT = 0x00; //start value ARR
	TMR->SR &= ~TIM_SR_UIF; //make sure the update flag is cleared
	TMR->DIER |= TIM_DIER_UIE; //update event interrupt enable

}

void basic_timer_start(TIM_TypeDef *TMR) {
	TMR->EGR = TIM_EGR_UG; //force buffered register update via force update event
	TMR->SR &= ~TIM_SR_UIF; //clear update event
	if (TMR == TIM6) {
		NVIC_SetPriority(TIM6_DAC_IRQn, 1U);
		NVIC_ClearPendingIRQ(TIM6_DAC_IRQn);
		NVIC_EnableIRQ(TIM6_DAC_IRQn);
	}
	if (TMR == TIM7) {
		NVIC_SetPriority(TIM7_IRQn, 1U);
		NVIC_ClearPendingIRQ(TIM7_IRQn);
		NVIC_EnableIRQ(TIM7_IRQn);
	}

	TMR->CR1 |= TIM_CR1_CEN; //enable timer

}

void TIM6_DAC_IRQHandler(void) {
	TIM6->SR &= ~TIM_SR_UIF; //clear update event interrupt flag in timer peripheral
	toggle_led1();
}
