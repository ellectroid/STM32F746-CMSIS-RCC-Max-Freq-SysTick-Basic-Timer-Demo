#ifndef SYSTICK_H_
#define SYSTICK_H_

#include "stm32f746xx.h"
#include "core_cm7.h"
#include "rcc.h"

void systick_setup(uint32_t sys_freq);
uint32_t millis(void);
void system_msdelay(uint32_t delay_ms);

#endif /* SYSTICK_H_ */
