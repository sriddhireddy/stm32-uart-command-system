#include "stm32f4xx.h"

#define GPIOAEN			(1U<<0)
#define PIN5			(1U<<5)

int main(void){

	RCC->AHB1ENR |= GPIOAEN;

	GPIOA-> MODER &=~(3U<<11); //clear both bits 10 and 11
	GPIOA-> MODER |= (1U<<10); //set bit 10 to 1 for output

	while(1){

		GPIOA->ODR^= PIN5;

		for(int i=0;i<100000;i++){}
	}

}
