#include "uart.h"

#include "uart_impl.h"

bool uart_init(void) {
    return _uart_init_impl();
}

bool uart_write(const void* buf, uint16_t len) {
    return _uart_write_impl(buf, len);
}

bool uart_read(void* buf, uint16_t len) {
    return _uart_read_impl(buf, len);
}