#include "ticker.h"

#include "ktime.h"

#include <stdio.h>
#include <string.h>

void ticker_create(ticker_t* ticker, uint32_t interval)
{
    ticker->ticks = 0;
    ticker->interval = interval;
    memset(ticker->tpi, 0, sizeof(char) * TICKER_TPI_SIZE);
    ticker->frame = ktime_get();
}

void ticker_tick(ticker_t* ticker)
{
    uint32_t frame = ktime_get();
    ticker->ticks++;
    if (frame >= ticker->frame + ticker->interval)
    {
        uint32_t ticks = frame - ticker->frame;
        ticker->frame += ticker->interval;
        float passedFactor = (float)ticks / (float)ticker->interval;
        float tpi = (float)ticker->ticks / (float)passedFactor;
        memset(ticker->tpi, 0, sizeof(char) * TICKER_TPI_SIZE);
        sprintf(ticker->tpi, "%.1f", tpi);
        
        ticker->ticks = 0;
    }
}

