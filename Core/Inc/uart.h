#ifndef UART_H
#define UART_H

#include <stdint.h>

#define UART_OK 0
#define UART_FAILURE -1

// TODO: Support parameter customization, multiple devices, etc

int uart_init(void);
int uart_write(const void* buf, uint16_t len);
int uart_read(void* buf, uint16_t len);

#endif // UART_H