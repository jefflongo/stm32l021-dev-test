#ifndef BOARD_H
#define BOARD_H

#include "stm32l0xx_hal.h"

#define LOG

#define DELAY(ms) HAL_Delay(ms)

#define LED0_Pin GPIO_PIN_14
#define LED0_GPIO_Port GPIOC
#define BTN_Pin GPIO_PIN_15
#define BTN_GPIO_Port GPIOC
#define BTN_EXTI_IRQn EXTI4_15_IRQn
#define RGB_Pin GPIO_PIN_1
#define RGB_GPIO_Port GPIOB

#endif // BOARD_H