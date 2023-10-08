#include "num.h"

#include <stdlib.h>

uint32_t rnd_next(uint32_t bound)
{
    return rand() % bound;
}

void rnd_seed(uint32_t seed)
{
    srand(seed);
}

void rnd_start(void)
{
    srand(0);
    srand(rand());
}
