#ifndef GPIO_H_
#define GPIO_H_
#include "stm32f746xx.h"
#include "systick.h"


void gpio_setup(void);
void blink_led1(void);
void toggle_led1(void);

#endif /* GPIO_H_ */
