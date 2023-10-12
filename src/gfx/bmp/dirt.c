#include "../bmp.h"
#include "gfx/col.h"
#include "util/num.h"

bmp_t* bmp_dirt(void)
{
    bmp_t* bmp = bmp_alloc(8, 8);
    for (size_t y = 0; y < 8; y++)
    {
        for (size_t x = 0; x < 8; x++)
        {
            uint32_t r = rnd_next(10);
            r = (r >= 4) ? (r + 4) : (r * 2);
            bmp->pixels[x + y * 8] = col_darken(0x7A411A, 30 + r, 48);
        }
    }

    return bmp;
}