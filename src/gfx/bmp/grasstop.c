#include "../bmp.h"
#include "util/num.h"
#include "gfx/col.h"

bmp_t* bmp_grass_top(void)
{
    bmp_t* bmp = bmp_alloc(8, 8);
    for (size_t i = 0; i < 64; i++)
    {
        uint32_t r = rnd_next(5);
        r = (r >= 2) ? (r + 1) : (r * 2);
        bmp->pixels[i] = col_darken(0x1CBC26, 28 + r, 48);
    }

    return bmp;
}