#include "../bmp.h"

bmp_t* bmp_error(void)
{
    bmp_t* bmp = bmp_alloc(8, 8);

    for (size_t y = 0; y < 8; y++)
    {
        size_t yIndex = y / 4;
        for (size_t x = 0; x < 8; x++)
        {
            size_t xIndex = x / 4;

            uint32_t c = ((xIndex + yIndex) % 2) == 0 ? 0xFE00FE : 0x000000;
            bmp->pixels[x + y * 8] = c;
        }
    }

    return bmp;
}

