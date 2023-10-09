#include "../bmp.h"
#include "util/num.h"
#include "gfx/col.h"

#include <stdbool.h>

bmp_t* bmp_wood(void)
{
    bmp_t* bmp = bmp_alloc(8, 8);
    for (size_t y = 0; y < 8; y++)
    {
        for (size_t x = 0; x < 8; x++)
        {
            bool xIndex = (x / 2) % 2 == 0;
            bool zIndex = (x / 4) % 2 == 0;

            uint32_t darken = (xIndex ? 22 : 32) + (zIndex ? 0 : 1) + rnd_next(8);

            bmp->pixels[x + y * 8] = col_darken(0xAF9142, darken, 48);
        }
    }
    
    return bmp;
}