#ifndef UART_DRIVER_H_
#define UART_DRIVER_H_

#include "stm32f4xx.h"

void UART_Init(void);
void UART_WriteChar(char c);
void UART_WriteString(const char *str);

#endif /* UART_DRIVER_H_ */
