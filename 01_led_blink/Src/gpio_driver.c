#include "gpio_driver.h"

static void delay(void);

#define GPIOAEN			(1U<<0)
#define PIN5			(1U<<5)

void GPIO_Init(void){
	RCC->AHB1ENR |= GPIOAEN;

	GPIOA->MODER &=~(3U<<10); //clear PA5 mode bits (bits 11:10)
	GPIOA->MODER |= (1U<<10); //set bit 10 to 1 for output
}

void GPIO_TogglePin(void){
	GPIOA->ODR^= PIN5;
	delay();
}

static void delay(void){
	for(volatile int i=0;i<100000;i++){};
}

void GPIO_SetPin(void){
	GPIOA->ODR |= PIN5;
}

void GPIO_ResetPin(void){
	GPIOA->ODR &= ~PIN5;
}











