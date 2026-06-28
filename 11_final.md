# main.c

```c
#include "gpio_driver.h"
#include "uart_driver.h"
#include "command_processor.h"

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

        ProcessCommand(buffer);

	}

}

```

# command_processor.h

```c
#ifndef COMMAND_PROCESSOR_H_
#define COMMAND_PROCESSOR_H_

void ProcessCommand(const char *buffer);

#endif /* COMMAND_PROCESSOR_H_ */
```

# gpio_driver.h

```c
#ifndef GPIO_DRIVER_H_
#define GPIO_DRIVER_H_

#include "stm32f4xx.h"

void GPIO_Init(void);
void GPIO_TogglePin(void);

void GPIO_SetPin(void);
void GPIO_ResetPin(void);

uint8_t GPIO_ReadPin(void);

#endif /* GPIO_DRIVER_H_ */
```

# uart_driver.h

```c
#ifndef UART_DRIVER_H_
#define UART_DRIVER_H_

#include "stm32f4xx.h"

void UART_Init(void);
void UART_WriteChar(char c);
void UART_WriteString(const char *str);
char UART_ReadChar(void);
void UART_ReadString(char *buffer,uint32_t maxLen);

int String_Compare(const char *s1, const char *s2);

#endif /* UART_DRIVER_H_ */
```

# command_processor.c

```c
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
```

# gpio_driver.c

```c
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

uint8_t GPIO_ReadPin(void){
//	if(GPIOA->ODR & PIN5) return 1;
//	else return 0;

	return (GPIOA->ODR & PIN5) ? 1 : 0;
}
```

# uart_driver.c

```c
#include "uart_driver.h"

//use datasheet to find block diagram to figure which clock to enable.
//use referece manual to set that bits
#define GPIOAEN			(1U<<0)
#define UART2EN			(1U<<17)

#define SYS_CLK     16000000U
#define BAUDRATE    115200U

#define CR1_UE			(1U<<13)
#define CR1_TE			(1U<<3)
#define CR1_RE			(1U<<2)

#define SR_TXE			(1U<<7)
#define SR_RXNE			(1U<<5)

void UART_Init(void){

	RCC->AHB1ENR |= GPIOAEN;
	RCC->APB1ENR |= UART2EN;

	GPIOA->MODER &=~(15U<<4); //0000 to bits 7:4
	GPIOA->MODER |= (10U<<4); //1010 to bits 7:4

	GPIOA->AFR[0] &=~(15U<<8); //0000 to bits 11:8 (rm: afr; pa2)
	GPIOA->AFR[0] &=~(15U<<12); //0000 to bits 15:12 (rm: afr; pa3)
	GPIOA->AFR[0] |= (7U<<8); //0111 to bits 11:8
	GPIOA->AFR[0] |= (7U<<12); //0111 to bits 15:12

	/*ALTER
	 * GPIOA->AFR[0] &= ~(0xFFU << 8);   // Clear bits 15:8
	 * GPIOA->AFR[0] |=  (0x77U << 8);   // AF7 for PA2 and PA3
	 * */

	USART2->BRR = SYS_CLK/BAUDRATE; //BRR = clk freq/baudrate = 16M /115200 = 138.88 = 139

	USART2->CR1 |= (CR1_TE | CR1_RE | CR1_UE);

}

void UART_WriteChar(char c){

	while(!(USART2->SR & SR_TXE)){} //polling

	USART2->DR = c;
}

void UART_WriteString(const char *str){ //const implies the func will NOT modify the string

	while(*str){ //same as *str != "\0" as \0 equivalent to 0
		UART_WriteChar(*str);
		str++;
	}
}

char UART_ReadChar(void){
	while(!(USART2->SR & SR_RXNE)){}

	return (char)USART2->DR; //char implies i want only lower 8 bits (char-8bits)
}

void UART_ReadString(char *buffer,uint32_t maxLen){
	uint32_t count=0;

    if (maxLen == 0) return;

	while(count < maxLen-1){

		*buffer = UART_ReadChar();
		if(*buffer == '\r'){
			*buffer = '\0';
			return;
		}

		buffer++;
		count++;
	}

	*buffer = '\0';
}

int String_Compare(const char *s1, const char *s2){
	while(*s1 != '\0' && *s2 != '\0'){
		if (*s1!=*s2) return 0;
		else{
			s1++; s2++;
		}
	}
//	if(*s1!=*s2) return 0;
//	else return 1;
	return(*s1==*s2);
}
```