#include "bmp.h"
#include "col.h"
#include "num.h"

#include <stdlib.h>

static bmp_t* s_BitmapError = NULL;
static bmp_t* s_BitmapCarpet = NULL;
static bmp_t* s_BitmapRock = NULL;
static bmp_t* s_BitmapWood = NULL;
static bmp_t* s_BitmapDirt = NULL;
static bmp_t* s_BitmapGrassTop = NULL;
static bmp_t* s_BitmapGrassSide = NULL;
static bmp_t* s_BitmapGlass = NULL;
static bmp_t* s_BitmapLeaf = NULL;

static bmp_t* bmp_alloc(uint32_t width, uint32_t height);
static void bmp_free(bmp_t* this);

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

    // GRASS TOP
    {
        bmp_t* bmp = bmp_alloc(8, 8);

        for (size_t i = 0; i < 64; i++)
        {
            bmp->pixels[i] = col_darken(0x1CBC26, 28 + rnd_next(8), 48);
        }

        s_BitmapGrassTop = bmp;
    }
}

bmp_t* bmp_get(uint32_t bmpId)
{
    switch (bmpId)
    {
    case 0: return s_BitmapError;
    case 1: return s_BitmapCarpet;
    case 5: return s_BitmapGrassTop;
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