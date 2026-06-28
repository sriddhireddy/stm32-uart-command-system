#include "gpio_driver.h"
#include "uart_driver.h"


int main(void){

	GPIO_Init();
	UART_Init();

	while(1){

		UART_WriteString("STM32 Ready!\r\n");

        for (volatile int i = 0; i < 1000000; i++);
	}

}
