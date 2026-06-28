#include "gpio_driver.h"
#include "uart_driver.h"


int main(void){
	//char data;
	char buffer[20];

	GPIO_Init();
	UART_Init();

	while(1){

//		data= UART_ReadChar();
//
//		if (data>='a' && data<='z')
//			data -= ('a'-'A');
//
//		UART_WriteChar(data);

		UART_ReadString(buffer,sizeof(buffer));

		UART_WriteString("You typed: ");
		UART_WriteString(buffer);
		UART_WriteString("\r\n");
	}

}
