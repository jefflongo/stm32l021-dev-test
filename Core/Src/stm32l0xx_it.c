#include "stm32l0xx_it.h"

#include "board.h"
#include "stusb4500.h"
#include "timer.h"

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
        // HAL_GPIO_WritePin(LED0_PORT, LED0_PIN, GPIO_PIN_SET);
    }
    EXTI->PR = BTN_PIN;
}

// CABLE DETECT
void EXTI0_1_IRQHandler(void) {
    NVIC_DisableIRQ(CABLE_DET_IRQ);
    stusb_negotiate(true);

    htim2.Instance->CNT = 0;
    __HAL_TIM_CLEAR_FLAG(&htim2, TIM_IT_UPDATE);
    HAL_TIM_Base_Start_IT(&htim2);
}

void TIM2_IRQHandler(void) {
    HAL_TIM_IRQHandler(&htim2);
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* htim) {
    HAL_TIM_Base_Stop_IT(&htim2);
    htim2.Instance->CNT = 0;
    __HAL_TIM_CLEAR_IT(&htim2, TIM_IT_CC1);

    __HAL_GPIO_EXTI_CLEAR_IT(CABLE_DET_PIN);
    NVIC_ClearPendingIRQ(CABLE_DET_IRQ);
    NVIC_EnableIRQ(CABLE_DET_IRQ);
}