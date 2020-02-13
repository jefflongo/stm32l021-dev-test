#include "stm32l0xx_it.h"

#include "board.h"
#include "gpio.h"
#include "stusb4500.h"
#include "timer.h"

#include <stdio.h>

void NMI_Handler(void) {
}

void HardFault_Handler(void) {
    while (1) {
    }
}

void SVC_Handler(void) {
}

void PendSV_Handler(void) {
}

void SysTick_Handler(void) {
    HAL_IncTick();
}

// BTN
void EXTI4_15_IRQHandler(void) {
    DELAY(50);
    if (HAL_GPIO_ReadPin(BTN_PORT, BTN_PIN) == GPIO_PIN_RESET) {
        gpio_set_pin_state(LED0_PORT, LED0_PIN, GPIO_PIN_SET);
    }
    EXTI->PR = BTN_PIN;
}

// CABLE DETECT
void EXTI0_1_IRQHandler(void) {
    // stusb_negotiate(true);
    EXTI->PR = CABLE_DET_PIN;
}

void TIM2_IRQHandler(void) {
    timer_handle_event();
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* htim) {
    gpio_set_pin_state(LED0_PORT, LED0_PIN, !gpio_get_pin_state(LED0_PORT, LED0_PIN));
    timer_clear();
}