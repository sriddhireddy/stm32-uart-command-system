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
