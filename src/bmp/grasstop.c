#include "bmp.h"
#include "num.h"
#include "col.h"

bmp_t* bmp_grass_top(void)
{
    bmp_t* bmp = bmp_alloc(8, 8);
    for (size_t i = 0; i < 64; i++)
    {
        bmp->pixels[i] = col_darken(0x1CBC26, 28 + rnd_next(8), 48);
    }

    return bmp;
}