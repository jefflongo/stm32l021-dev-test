#ifndef BOARD_H
#define BOARD_H

#include "stm32l0xx_hal.h"

#include <stdbool.h>

#define LOG

#define GET_MS() HAL_GetTick()
#define DELAY(ms) HAL_Delay(ms)

#define RGB_PORT GPIOB
#define RGB_PIN GPIO_PIN_1

#define LED0_PORT GPIOC
#define LED0_PIN GPIO_PIN_14

#define TX_PORT GPIOA
#define TX_PIN GPIO_PIN_9
#define LED1_PORT GPIOA
#define LED1_PIN GPIO_PIN_9

#define RX_PORT GPIOA
#define RX_PIN GPIO_PIN_10
#define LED2_PORT GPIOA
#define LED2_PIN GPIO_PIN_10

#define BTN_PORT GPIOC
#define BTN_PIN GPIO_PIN_15
#define BTN_IRQ EXTI4_15_IRQn

#define CABLE_DET_PORT GPIOA
#define CABLE_DET_PIN GPIO_PIN_0
#define CABLE_DET_IRQ EXTI0_1_IRQn

#define TIMER_IRQ TIM2_IRQn

#define SDA_PORT GPIOB
#define SDA_PIN GPIO_PIN_7

#define SCL_PORT GPIOB
#define SCL_PIN GPIO_PIN_6

bool rcc_init();
void gpio_init();
void nvic_init();

#endif // BOARD_H