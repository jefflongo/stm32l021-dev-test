#include "board.h"
#include "gpio.h"
#include "i2c.h"
#include "uart.h"
#include "ws281x.h"

#include <stdbool.h>
#include <stdio.h>

int main(void) {
    HAL_Init();
    rcc_init();
    gpio_init();
    nvic_init();
    uart_init();
    i2c_master_init();

    ws_write((ws_color_t) { 0, 0x0F, 0 });

    while (1) {
        gpio_set_pin_state(LED0_PORT, LED0_PIN, !gpio_get_pin_state(LED0_PORT, LED0_PIN));
        DELAY(1000);
    }
}