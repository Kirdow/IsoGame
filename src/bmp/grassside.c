#include "bmp.h"
#include "num.h"
#include "col.h"
#include "level.h"

bmp_t* bmp_grass_side(void)
{
    bmp_t* bmp = bmp_alloc(8, 8);

    bmp_t* dirt = bmp_get(T_DIRT);
    for (size_t x = 0; x < 8; x++)
    {
        uint32_t d = 1 + rnd_next(3);
        for (size_t y = 0; y < 8; y++)
        {
            uint32_t col;
            if (y < d)
                col = col_darken(0x1CBC26, 28 + rnd_next(8), 48);
            else
                col = dirt->pixels[x + y * 8];
            
            bmp->pixels[x + y * 8] = col;
        }
    }

    return bmp;
}