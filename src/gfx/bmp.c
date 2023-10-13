#include "bmp.h"
#include "col.h"
#include "util/num.h"

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

bmp_t* bmp_error(void);
bmp_t* bmp_carpet(void);
bmp_t* bmp_rock(void);
bmp_t* bmp_wood(void);
bmp_t* bmp_dirt(void);
bmp_t* bmp_grass_top(void);
bmp_t* bmp_grass_side(void);
bmp_t* bmp_glass(void);
bmp_t* bmp_leaf(void);

void bmp_init(void)
{
    s_BitmapError = bmp_error();
    s_BitmapCarpet = bmp_carpet();
    s_BitmapRock = bmp_rock();
    s_BitmapWood = bmp_wood();
    s_BitmapDirt = bmp_dirt();
    s_BitmapGrassTop = bmp_grass_top();
    s_BitmapGrassSide = bmp_grass_side();
    s_BitmapGlass = bmp_glass();
    s_BitmapLeaf = bmp_leaf();
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

bool bmp_copy(bmp_t* dst, bmp_t* src)
{
    if (dst == NULL || src == NULL) return false;
    if (dst->width != src->width || dst->height != src->height) return false;

    size_t len = src->width * src->height;
    for (size_t i = 0; i < len; i++)
    {
        dst->pixels[i] = src->pixels[i];
    }

    return true;
}
