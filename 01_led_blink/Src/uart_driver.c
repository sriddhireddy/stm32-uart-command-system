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












