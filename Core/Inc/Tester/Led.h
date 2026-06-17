#ifndef LED_H
#define LED_H

#include "stm32f4xx_hal.h"

void Led_Init(void);
void Led_AllOff(void);
void Led_RunTestPattern(void);

#endif // LED_H
