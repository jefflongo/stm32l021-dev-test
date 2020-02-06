#ifndef UART_IMPL_H
#define UART_IMPL_H

#include <stdint.h>

int _uart_init_impl(void);
int _uart_write_impl(const void* buf, uint16_t len);
int _uart_read_impl(void* buf, uint16_t len);

#endif // UART_IMPL_H