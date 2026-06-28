#include "gpio_driver.h"

#define GPIOAEN			(1U<<0)
#define PIN5			(1U<<5)

void gpio_init(void){

	RCC->AHB1ENR |= GPIOAEN;

	GPIOA-> MODER &=~(3U<<10); //clear both bits 10 and 11
	GPIOA-> MODER |= (1U<<10); //set bit 10 to 1 for output
}

void led_toggle(void){

	GPIOA->ODR^= PIN5;

	for(int i=0;i<100000;i++){};
}
