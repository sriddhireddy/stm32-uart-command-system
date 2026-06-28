
#ifndef GPIO_DRIVER_H_
#define GPIO_DRIVER_H_

#include "stm32f4xx.h"

void GPIO_Init(void);
void GPIO_TogglePin(void);

void GPIO_SetPin(void);
void GPIO_ResetPin(void);

#endif /* GPIO_DRIVER_H_ */
