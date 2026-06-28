#include "gpio_driver.h"
#include "uart_driver.h"


int main(void){
	char data;

	GPIO_Init();
	UART_Init();

	while(1){

		data= UART_ReadChar();

		if (data>='a' && data<='z')
			data -= ('a'-'A');

		UART_WriteChar(data);
	}

}
