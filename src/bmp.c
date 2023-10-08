#include "bmp.h"
#include "col.h"
#include "num.h"

#include <stdlib.h>
#include <stdbool.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

static bmp_t* s_BitmapError = NULL;
static bmp_t* s_BitmapCarpet = NULL;
static bmp_t* s_BitmapRock = NULL;
static bmp_t* s_BitmapWood = NULL;
static bmp_t* s_BitmapDirt = NULL;
static bmp_t* s_BitmapGrassTop = NULL;
static bmp_t* s_BitmapGrassSide = NULL;
static bmp_t* s_BitmapGlass = NULL;
static bmp_t* s_BitmapLeaf = NULL;

void bmp_init(void)
{
    // ERROR
    {
        bmp_t* bmp = bmp_alloc(8, 8);

        for (size_t y = 0; y < 8; y++)
        {
            size_t yIndex = y / 4;
            for (size_t x = 0; x < 8; x++)
            {
                size_t xIndex = x / 4;

                uint32_t c = ((xIndex + yIndex) % 2) == 0 ? 0x7F007F : 0x00FF00;
                bmp->pixels[x + y * 8] = c;
            }
        }
        s_BitmapError = bmp;
    }

    // CARPET
    {
        bmp_t* bmp = bmp_alloc(8, 8);

        for (size_t y = 0; y < 8; y++)
        {
            for (size_t x = 0; x < 8; x++)
            {
                uint32_t col = 0xFF << 16;
                uint32_t darken;
                if (x > 1 && y > 1 && x < 6 && y < 6) darken = 24 + rnd_next(8);
                else if (x > 0 && y > 0 && x < 7 && y < 7) darken = 20 + rnd_next(8);
                else darken = 29 + rnd_next(8);
                bmp->pixels[x + y * 8] = col_darken(col, darken, 48);
            }
        }
        s_BitmapCarpet = bmp;
    }

    // ROCK
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

        s_BitmapRock = bmp;
    }

    // WOOD
    {
        bmp_t* bmp = bmp_alloc(8, 8);
        for (size_t y = 0; y < 8; y++)
        {
            for (size_t x = 0; x < 8; x++)
            {
                bool xIndex = (x / 2) % 2 == 0;
                bool zIndex = (x / 4) % 4 == 0;

                uint32_t darken = (xIndex ? 22 : 32) + (zIndex ? 0 : 1) + rnd_next(8);

                bmp->pixels[x + y * 8] = col_darken(0xAF9142, darken, 48);
            }
        }

        s_BitmapWood = bmp;
    }

    // DIRT
    {
        bmp_t* bmp = bmp_alloc(8, 8);
        for (size_t y = 0; y < 8; y++)
        {
            for (size_t x = 0; x < 8; x++)
            {
                bmp->pixels[x + y * 8] = col_darken(0x7A411A, 36 + rnd_next(8), 48);
            }
        }
    
        s_BitmapDirt = bmp;
    }

    // GRASS TOP
    {
        bmp_t* bmp = bmp_alloc(8, 8);

        for (size_t i = 0; i < 64; i++)
        {
            bmp->pixels[i] = col_darken(0x1CBC26, 28 + rnd_next(8), 48);
        }

        s_BitmapGrassTop = bmp;
    }

    // GRASS SIDE
    {
        bmp_t* bmp = bmp_alloc(8, 8);
        for (size_t x = 0; x < 8; x++)
        {
            uint32_t d = 1 + rnd_next(3);
            for (size_t y = 0; y < 8; y++)
            {
                uint32_t col;
                if (y < d)
                    col = col_darken(0x1CBC26, 28 + rnd_next(8), 48);
                else
                    col = s_BitmapDirt->pixels[x + y * 8];

                bmp->pixels[x + y * 8] = col;
            }
        }

        s_BitmapGrassSide = bmp;
    }

    // GLASS
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

        s_BitmapGlass = bmp;
    }

    // LEAF
    {
        bmp_t* bmp = bmp_alloc(8, 8);
        for (size_t y = 0; y < 8; y++)
        {
            for (size_t x = 0; x < 8; x++)
            {
                uint32_t col;
                if (rnd_next(5) < 2) col = 0xFF00FF;
                else col = col_darken(0x1CBC26, 28 + rnd_next(8), 48);
                bmp->pixels[x + y * 8] = col;
            }
        }

        s_BitmapLeaf = bmp;
    }

}

bmp_t* bmp_get(uint32_t bmpId)
{
    switch (bmpId)
    {
    case 0: return s_BitmapError;
    case 1: return s_BitmapCarpet;
    case 2: return s_BitmapRock;
    case 3: return s_BitmapWood;
    case 4: return s_BitmapDirt;
    case 5: return s_BitmapGrassTop;
    case 6: return s_BitmapGrassSide;
    case 7: return s_BitmapGlass;
    case 8: return s_BitmapLeaf;
    default: return s_BitmapError;
    }
}

void bmp_free(bmp_t* this)
{
    if (!this) return;
    if (this->pixels) free(this->pixels);
    free(this);
}

bmp_t* bmp_alloc(uint32_t width, uint32_t height)
{
    uint32_t* pixels = (uint32_t*)malloc(width * height * sizeof(uint32_t));
    if (!pixels) return NULL;

    bmp_t* result = (bmp_t*)malloc(sizeof(bmp_t));
    if (!result)
    {
        free(pixels);
        return NULL;
    }

    result->pixels = pixels;
    result->width = width;
    result->height = height;
    return result;
}

bmp_t* bmp_load(const char* filepath)
{
    int width, height, nc;

    uint8_t* data = stbi_load(filepath, &width, &height, &nc, 4);
    if (!data) return NULL;

    bmp_t* bmp = bmp_alloc(width, height);
    if (!bmp)
    {
        stbi_image_free(data);
        return NULL;
    }

    for (size_t y = 0; y < bmp->height; y++)
    {
        for (size_t x = 0; x < bmp->width; x++)
        {
            uint32_t c = ((uint32_t*)data)[x + y * bmp->width] & 0xFFFFFF;
            bmp->pixels[x + y * bmp->width] = c;
        }
    }

    stbi_image_free(data);
    return bmp;
}