#include "board.h"

#include "uart.h"

#include <errno.h>
#include <stdio.h>
#include <sys/unistd.h>

// override for printf
int _write(int file, char* data, int len) {
    if ((file != STDOUT_FILENO) && (file != STDERR_FILENO)) {
        errno = EBADF;
        return -1;
    }
    return uart_write(data, len) ? len : 0;
}