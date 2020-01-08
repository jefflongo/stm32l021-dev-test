#ifndef WS281X_H
#define WS281X_H

#include <stdint.h>

typedef struct {
    uint8_t r;
    uint8_t g;
    uint8_t b;
} ws_color_t;

void ws_write(const ws_color_t color);

#endif /* WS281X_H */
