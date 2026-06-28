#include "gpio_driver.h"

int main(void){

	GPIO_Init();

	while(1){

		GPIO_TogglePin();
	}

}
