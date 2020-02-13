#ifndef TIMER_H
#define TIMER_H

#include <stdbool.h>

bool timer_init(void);
void timer_start(void);
void timer_stop(void);
void timer_handle_event(void);
void timer_clear(void);

#endif // TIMER_H