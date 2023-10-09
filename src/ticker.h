#ifndef _TICKER_H
#define _TICKER_H

#include <stdint.h>

#define TICKER_TPI_LEN 7
#define TICKER_TPI_SIZE (TICKER_TPI_LEN + 1)

typedef struct {
    uint32_t frame;
    uint32_t ticks;
    uint32_t interval;
    char tpi[TICKER_TPI_SIZE];
} ticker_t;

void ticker_create(ticker_t* ticker, uint32_t interval);
void ticker_tick(ticker_t* ticker);

#endif