#include "board.h"

#include "gpio.h"
#include "uart.h"

#include <errno.h>
#include <stdio.h>
#include <sys/unistd.h>

// override for printf
int _write(int file, char* data, int len) {
    if ((file != STDOUT_FILENO) && (file != STDERR_FILENO)) {
        errno = EBADF;
        return -1;
    }
    return uart_write(data, len) ? len : 0;
}

bool rcc_init(void) {
    RCC_OscInitTypeDef RCC_OscInitStruct = { 0 };
    RCC_ClkInitTypeDef RCC_ClkInitStruct = { 0 };
    RCC_PeriphCLKInitTypeDef PeriphClkInit = { 0 };

    // Configure the main internal regulator output voltage
    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

    // Initialize the CPU, AHB and APB busses clocks
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
    RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
        return false;
    }
    RCC_ClkInitStruct.ClockType =
      RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV2;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK) {
        return false;
    }
    PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART2 | RCC_PERIPHCLK_I2C1;
    PeriphClkInit.Usart2ClockSelection = RCC_USART2CLKSOURCE_PCLK1;
    PeriphClkInit.I2c1ClockSelection = RCC_I2C1CLKSOURCE_PCLK1;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK) {
        return false;
    }
    return true;
}

void gpio_init(void) {
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();

    gpio_config_t config;

    config.mode = GPIO_MODE_OUTPUT_PP;
    config.pull = GPIO_NOPULL;
    config.speed = GPIO_SPEED_FREQ_LOW;
    gpio_set_pin_state(LED0_PORT, LED0_PIN, GPIO_PIN_RESET);
    // gpio_set_pin_state(LED1_PORT, LED1_PIN, GPIO_PIN_RESET);
    // gpio_set_pin_state(LED2_PORT, LED2_PIN, GPIO_PIN_RESET);
    gpio_config_pin(LED0_PORT, LED0_PIN, &config);
    // gpio_config_pin(LED1_PORT, LED1_PIN, &config);
    // gpio_config_pin(LED2_PORT, LED2_PIN, &config);

    config.mode = GPIO_MODE_OUTPUT_PP;
    config.pull = GPIO_NOPULL;
    config.speed = GPIO_SPEED_FREQ_MEDIUM;
    gpio_set_pin_state(RGB_PORT, RGB_PIN, GPIO_PIN_RESET);
    gpio_config_pin(RGB_PORT, RGB_PIN, &config);

    config.mode = GPIO_MODE_IT_FALLING;
    config.pull = GPIO_NOPULL;
    config.speed = GPIO_SPEED_FREQ_LOW;
    gpio_config_pin(BTN_PORT, BTN_PIN, &config);
}

void nvic_init(void) {
    HAL_NVIC_SetPriority(BTN_IRQ, 1, 0);
    HAL_NVIC_EnableIRQ(BTN_IRQ);
}