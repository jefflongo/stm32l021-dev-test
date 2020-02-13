#include "uart_impl.h"

#include "board.h"
#include "stm32l0xx_hal.h"
#include "uart.h"

static UART_HandleTypeDef huart;

bool _uart_init_impl(void) {
    huart.Instance = USART2;
    huart.Init.BaudRate = 115200;
    huart.Init.WordLength = UART_WORDLENGTH_8B;
    huart.Init.StopBits = UART_STOPBITS_1;
    huart.Init.Parity = UART_PARITY_NONE;
    huart.Init.Mode = UART_MODE_TX_RX;
    huart.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart.Init.OverSampling = UART_OVERSAMPLING_16;
    huart.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
    huart.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
    return HAL_UART_Init(&huart) == HAL_OK;
}

bool _uart_write_impl(const void* buf, uint16_t len) {
    return HAL_UART_Transmit(&huart, (uint8_t*)buf, len, HAL_MAX_DELAY) == HAL_OK;
}

bool _uart_read_impl(void* buf, uint16_t len) {
    return HAL_UART_Receive(&huart, (uint8_t*)buf, len, HAL_MAX_DELAY) == HAL_OK;
}

void HAL_UART_MspInit(UART_HandleTypeDef* uartHandle) {
    if (uartHandle->Instance == USART2) {
        __HAL_RCC_USART2_CLK_ENABLE();
        __HAL_RCC_GPIOA_CLK_ENABLE();

        GPIO_InitTypeDef config = {
            .Pin = TX_PIN | RX_PIN,
            .Mode = GPIO_MODE_AF_PP,
            .Pull = GPIO_NOPULL,
            .Speed = GPIO_SPEED_FREQ_VERY_HIGH,
            .Alternate = GPIO_AF4_USART2,
        };
        HAL_GPIO_Init(TX_PORT, &config);
    }
}

void HAL_UART_MspDeInit(UART_HandleTypeDef* uartHandle) {
    if (uartHandle->Instance == USART2) {
        __HAL_RCC_USART2_CLK_DISABLE();

        HAL_GPIO_DeInit(TX_PORT, TX_PIN);
        HAL_GPIO_DeInit(RX_PORT, RX_PIN);
    }
}