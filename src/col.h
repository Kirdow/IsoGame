#ifndef _COL_H
#define _COL_H

#include <stdint.h>

uint32_t col_clamp(uint32_t channel);
uint32_t col_darken(uint32_t color, uint32_t numerator, uint32_t denominator);

#endif