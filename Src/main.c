#include "main.h"

int main(void) {
	rcc_setup(); //clock for peripheral, clock will be set to 216MHz
	gpio_setup(); //set pin modes and functions
	systick_setup(SYSTEM_FREQUENCY);
	basic_timer_setup(TIM6);

	for (uint8_t x = 0; x < 10U; x++) {
		toggle_led1();
		system_msdelay(100);
	}

	basic_timer_start(TIM6);
	while (1) {
	}
}
