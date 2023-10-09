#ifndef _TIMER_H
#define _TIMER_H

#include <stdint.h>
#include <stdbool.h>

typedef struct {
    uint32_t last_tick;
    uint32_t interval;
    bool active;
} timer_t;

void timer_create(timer_t* timer, uint32_t interval);
void timer_frame(timer_t* timer);

#endif
