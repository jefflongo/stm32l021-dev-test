#include "board.h"
#include "i2c.h"
#include "stusb4500.h"
#include "timer.h"
#include "uart.h"
#include "ws281x.h"

#include <stdbool.h>
#include <stdio.h>

int main(void) {
    HAL_Init();
    rcc_init();
    gpio_init();
    nvic_init();
    timer_init();
    uart_init();
    i2c_master_init();

    ws_write((ws_color_t) { 0, 0x0F, 0 });
    // Check for cable attached on dead battery
    if (HAL_GPIO_ReadPin(CABLE_DET_PORT, CABLE_DET_PIN) == GPIO_PIN_RESET) {
        stusb_negotiate(false);
    }

    while (1) {
    }
}