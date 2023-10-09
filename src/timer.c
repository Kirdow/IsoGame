#include "timer.h"
#include "ktime.h"

void timer_create(timer_t* timer, uint32_t interval)
{
    timer->last_tick = ktime_get();
    timer->interval = interval;
    timer->active = false;
}

void timer_frame(timer_t* timer)
{
    timer->active = false;
    uint32_t tick = ktime_get();
    if (tick - timer->last_tick >= timer->interval)
    {
        timer->active = true;
        timer->last_tick += timer->interval;
    }
}
