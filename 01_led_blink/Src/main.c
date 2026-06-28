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
//
//		UART_WriteString("You typed: ");
//		UART_WriteString(buffer);
//		UART_WriteString("\r\n");

		if (String_Compare(buffer,"LEDON")){
			GPIO_SetPin();
		}
		else if (String_Compare(buffer,"LEDOFF")){
			GPIO_ResetPin();
		}
		else if (String_Compare(buffer,"HELP")){
			UART_WriteString("\r\n");
			UART_WriteString("Available Commands\r\n");
			UART_WriteString("------------------\r\n");
			UART_WriteString("LEDON  - Turn LED ON\r\n");
			UART_WriteString("LEDOFF - Turn LED OFF\r\n");
			UART_WriteString("HELP   - Show commands\r\n");
			UART_WriteString("STATUS - Show LED status\r\n");
			UART_WriteString("\r\n");
		}
		else{
			UART_WriteString("not recognized\r\n");
		}

	}

}
