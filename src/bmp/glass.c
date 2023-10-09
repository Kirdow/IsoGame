#include "bmp.h"

bmp_t* bmp_glass(void)
{
    bmp_t* bmp = bmp_alloc(8, 8);
    for (size_t y = 0; y < 8; y++)
    {
        for (size_t x = 0; x < 8; x++)
        {
            uint32_t col = 0xFF00FF;
            if (
                (
                    (x % 7 == 0 || y % 7 == 0) && ((x + 1) % 3 != 0 && (y + 1) % 3 != 0)
                ) || (
                    (x + 1) % 5 == 0 && (y + 1) % 5 == 0
                )
            )
            {
                col = 0xFFFFFF;
            }
        
            bmp->pixels[x + y * 8] = col;
        }
    }

    return bmp;
}