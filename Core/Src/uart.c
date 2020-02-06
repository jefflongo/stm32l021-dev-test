#include "uart.h"

#include "uart_impl.h"

#include <errno.h>
#include <stdio.h>
#include <sys/unistd.h>

// override for printf
int _write(int file, char* data, int len) {
    if ((file != STDOUT_FILENO) && (file != STDERR_FILENO)) {
        errno = EBADF;
        return -1;
    }
    return uart_write(data, len) == UART_OK ? len : 0;
}

inline int uart_init(void) {
    return _uart_init_impl();
}

inline int uart_write(const void* buf, uint16_t len) {
    return _uart_write_impl(buf, len);
}

inline int uart_read(void* buf, uint16_t len) {
    return _uart_read_impl(buf, len);
}