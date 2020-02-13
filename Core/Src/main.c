#include "board.h"
#include "gpio.h"
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

    // ws_write((ws_color_t) { 0, 0x0F, 0 });
    timer_start();
    // Check for cable attached on dead battery
    if (gpio_get_pin_state(CABLE_DET_PORT, CABLE_DET_PIN) == GPIO_PIN_RESET) {
        // if (!stusb_negotiate(false)) printf("FAILED TO NEGOTIATE\r\n");
    }

    while (1) {
        printf("%d\r\n", TIM2->CNT);
        DELAY(100);
    }
}