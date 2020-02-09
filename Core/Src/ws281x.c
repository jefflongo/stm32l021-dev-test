#include "ws281x.h"

#include "board.h"
#include "gpio.h"

static uint32_t reverse(uint8_t b) {
    b = (b & 0xF0) >> 4 | (b & 0x0F) << 4;
    b = (b & 0xCC) >> 2 | (b & 0x33) << 2;
    b = (b & 0xAA) >> 1 | (b & 0x55) << 1;
    return b;
}

static uint32_t convert_rgb(const ws_color_t color) {
    return (reverse(color.b) << 16) | (reverse(color.r) << 8) | reverse(color.g);
}

void ws_write(const ws_color_t color) {
    // Hold data line low for 50us to reset LED driver
    RGB_PORT->BRR = RGB_PIN;
    DELAY(50);

    // Convert rgb data to custom WS281x format: GRB, MSB first
    uint32_t data = convert_rgb(color);

    for (int i = 0; i < 24; i++) {
        if (data & 1) {
            // High for > 0.35us for 1
            RGB_PORT->BSRR = RGB_PIN;
            asm("NOP");
            asm("NOP");
            asm("NOP");
            asm("NOP");
            RGB_PORT->BRR = RGB_PIN;
        } else {
            // High for < 0.35us for 0
            RGB_PORT->BSRR = RGB_PIN;
            asm("NOP");
            RGB_PORT->BRR = RGB_PIN;
        }
        data >>= 1;
    }
}