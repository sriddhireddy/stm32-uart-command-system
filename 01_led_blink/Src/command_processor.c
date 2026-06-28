#include "command_processor.h"
#include "gpio_driver.h"
#include "uart_driver.h"

#define CMD_LEDON     "LEDON"
#define CMD_LEDOFF    "LEDOFF"
#define CMD_LEDBLINK  "LEDBLINK"
#define CMD_HELP      "HELP"
#define CMD_STATUS    "STATUS"

void ProcessCommand(const char *buffer){
	if (String_Compare(buffer,CMD_LEDON)){
				GPIO_SetPin();
				UART_WriteString("LED turned ON\r\n");

		}
		else if (String_Compare(buffer,CMD_LEDOFF)){
			GPIO_ResetPin();
			UART_WriteString("LED turned OFF\r\n");

		}
		else if (String_Compare(buffer,CMD_LEDBLINK)){
			GPIO_TogglePin();
			UART_WriteString("LED Blinking\r\n");
		}
		else if (String_Compare(buffer,CMD_HELP)){
			UART_WriteString("\r\n");
			UART_WriteString("Available Commands\r\n");
			UART_WriteString("------------------\r\n");
			UART_WriteString("LEDON  - Turn LED ON\r\n");
			UART_WriteString("LEDOFF - Turn LED OFF\r\n");
			UART_WriteString("LEDBLINK - Blink LED\r\n");
			UART_WriteString("HELP   - Show commands\r\n");
			UART_WriteString("STATUS - Show LED status\r\n");
			UART_WriteString("\r\n");
		}
		else if (String_Compare(buffer, CMD_STATUS))
		{
			if (GPIO_ReadPin())		    {
				UART_WriteString("LED Status : ON\r\n");
			}
			else{
				UART_WriteString("LED Status : OFF\r\n");
			}
		}
		else{
			UART_WriteString("Unknown command.\r\n");
			UART_WriteString("Type HELP for available commands.\r\n");
		}
}

