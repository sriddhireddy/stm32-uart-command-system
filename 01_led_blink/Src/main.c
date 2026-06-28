#include "gpio_driver.h"
#include "uart_driver.h"


int main(void){

	GPIO_Init();
	UART_Init();

	while(1){

		GPIO_TogglePin();
	}

}
