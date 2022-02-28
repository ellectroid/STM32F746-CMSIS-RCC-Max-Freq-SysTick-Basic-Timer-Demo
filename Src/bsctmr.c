#include "bsctmr.h"

void basic_timer_setup(TIM_TypeDef *TMR) {
	TMR->CR1 |= TIM_CR1_ARPE | TIM_CR1_URS; //ARR is buffered | only overflow/underflow generates update event.

	TMR->PSC = (108000U / 2U) - 1U; //APB1 is 54MHz, timer is 2x APB1 Freq, so now the timer is at 2kHz; 16-bit value!!! 65535 max!
	TMR->ARR = 2000U; //2000 ticks at 2kHz is 1s
	TMR->CNT = 0x00; //start value 0
	TMR->DIER |= TIM_DIER_UIE; //update event interrupt enable

	if (TMR == TIM6) {
		NVIC_SetPriority(TIM6_DAC_IRQn, 1U);
		NVIC_EnableIRQ(TIM6_DAC_IRQn);
	}
	if (TMR == TIM7) {
		NVIC_SetPriority(TIM7_IRQn, 1U);
		NVIC_EnableIRQ(TIM7_IRQn);
	}

}

void basic_timer_start(TIM_TypeDef *TMR) {
	TMR->CR1 |= TIM_CR1_CEN; //enable timer

}

void TIM6_DAC_IRQHandler(void) {
	TIM6->SR &= ~TIM_SR_UIF; //clear update event interrupt flag in timer peripheral
	NVIC_ClearPendingIRQ(TIM6_DAC_IRQn); //clear interrupt pending flag in NVIC
	toggle_led1();
}
