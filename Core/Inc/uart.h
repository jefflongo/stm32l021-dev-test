#ifndef UART_H
#define UART_H

#include <stdbool.h>
#include <stdint.h>

// TODO: Support parameter customization, multiple devices, etc

bool uart_init(void);
bool uart_write(const void* buf, uint16_t len);
bool uart_read(void* buf, uint16_t len);

#endif // UART_H