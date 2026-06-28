#include "command_processor.h"
#include "gpio_driver.h"
#include "uart_driver.h"

void ProcessCommand(const char *buffer){
	if (String_Compare(buffer,"LEDON")){
				GPIO_SetPin();
				UART_WriteString("LED turned ON\r\n");

		}
		else if (String_Compare(buffer,"LEDOFF")){
			GPIO_ResetPin();
			UART_WriteString("LED turned OFF\r\n");

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
		else if (String_Compare(buffer, "STATUS"))
		{
			if (GPIO_ReadPin())		    {
				UART_WriteString("LED Status : ON\r\n");
			}
			else{
				UART_WriteString("LED Status : OFF\r\n");
			}
		}
		else{
			UART_WriteString("not recognized\r\n");
		}
}

