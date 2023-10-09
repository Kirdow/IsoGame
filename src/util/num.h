#ifndef _NUM_H
#define _NUM_H

#include <stdint.h>

uint32_t rnd_next(uint32_t bound);
void rnd_seed(uint32_t seed);
void rnd_start(void);

#endif