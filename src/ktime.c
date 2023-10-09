#include "ktime.h"
#include <SDL.h>

static uint32_t s_Tick = 0;
static uint32_t s_DeltaTime = 0;
void ktime_frame(void)
{
    uint32_t tick = SDL_GetTicks();
    if (s_Tick == 0)
    {
        s_Tick = tick;
        s_DeltaTime = 0;
        return;
    }

    s_DeltaTime = tick - s_Tick;
    s_Tick = tick;
}

uint32_t ktime_get(void)
{
    return s_Tick;
}

uint32_t ktime_delta(void)
{
    return s_DeltaTime;
}