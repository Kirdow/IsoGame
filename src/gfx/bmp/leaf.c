#include "../bmp.h"
#include "util/num.h"
#include "gfx/col.h"

bmp_t* bmp_leaf(void)
{
    bmp_t* bmp = bmp_alloc(8, 8);
    for (size_t y = 0; y < 8; y++)
    {
        for (size_t x = 0; x < 8; x++)
        {
            uint32_t col;
            if (rnd_next(35) < 17) col = 0xFF00FF;
            else col = col_darken(0x1CBC26, 20 + rnd_next(5) * 2, 48);
            bmp->pixels[x + y * 8] = col;
        }
    }

    return bmp;
}