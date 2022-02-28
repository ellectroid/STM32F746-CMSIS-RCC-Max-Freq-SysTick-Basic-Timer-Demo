#include "gpio.h"

/*
 * Private functions
 */

void gpio_setup_porta(void);
void gpio_setup_portb(void);
void gpio_setup_porti(void);

void gpio_setup(void) {
	gpio_setup_porta();
	gpio_setup_portb();
	gpio_setup_porti();
}

void gpio_setup_porta(void) {

}
void gpio_setup_portb(void) {

}
void gpio_setup_porti(void) {
	/*
	 *  PI1 GREEN LED LED1 ACTIVE HIGH
	 * */
	GPIOI->MODER = (GPIOI->MODER & ~(1U << 3U)) | (1U << 2U); //PI1 set to general purpose output mode
	GPIOI->OTYPER &= ~(GPIO_OTYPER_OT_1); //PI1 output push-pull
	GPIOI->OSPEEDR &= ~(GPIO_OSPEEDR_OSPEEDR1); //PI1 output speed very low
	GPIOI->PUPDR &= ~(GPIO_PUPDR_PUPDR1); //PI1 no pull-up no pull-down
}

void blink_led1(void) {
	GPIOI->ODR |= GPIO_ODR_OD1; //set PI1 to high
	system_msdelay(100U);
	GPIOI->ODR &= ~GPIO_ODR_OD1; //set PI1 to low
}
void toggle_led1(void){
	GPIOI->ODR ^= GPIO_ODR_OD1;
}
