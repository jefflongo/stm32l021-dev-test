#ifndef TIMER_H
#define TIMER_H

#include "stm32l0xx_hal.h"

#include <stdbool.h>

extern TIM_HandleTypeDef htim2;

bool timer_init(void);

#endif // TIMER_H