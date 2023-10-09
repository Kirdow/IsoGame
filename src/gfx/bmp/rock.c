#include "../bmp.h"
#include "util/num.h"
#include "gfx/col.h"

bmp_t* bmp_rock(void)
{
    bmp_t* bmp = bmp_alloc(8, 8);

    for (size_t y = 0; y < 8; y++)
    {
        for (size_t x = 0; x < 8; x++)
        {
            uint32_t col = 0xFF;
            col |= col << 16 | col << 8;

            uint32_t darken;
            if (x == 0 || y == 0 || x == 7 || y == 7) darken = 32 + rnd_next(8);
            else darken = 24 + rnd_next(8);

            bmp->pixels[x + y * 8] = col_darken(col, darken, 48);
        }
    }


    return bmp;
}