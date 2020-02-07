#ifndef UART_IMPL_H
#define UART_IMPL_H

#include <stdbool.h>
#include <stdint.h>

bool _uart_init_impl(void);
bool _uart_write_impl(const void* buf, uint16_t len);
bool _uart_read_impl(void* buf, uint16_t len);

#endif // UART_IMPL_H