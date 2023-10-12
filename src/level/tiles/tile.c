#include "tile.h"

#include <stdlib.h>
#include <string.h>

static bmp_t* s_BitmapShader = NULL;

static tile_t* s_TileError = NULL;
static tile_t* s_TileCarpet = NULL;
static tile_t* s_TileRock = NULL;
static tile_t* s_TileWood = NULL;
static tile_t* s_TileDirt = NULL;
static tile_t* s_TileGrassTop = NULL;
static tile_t* s_TileGrassSide = NULL;
static tile_t* s_TileGlass = NULL;
static tile_t* s_TileLeaf = NULL;

static void tile_init_shader(void);

tile_t* tile_init_error(void);
tile_t* tile_init_carpet(void);
tile_t* tile_init_rock(void);
tile_t* tile_init_wood(void);
tile_t* tile_init_dirt(void);
tile_t* tile_init_grass_top(void);
tile_t* tile_init_grass_side(void);
tile_t* tile_init_glass(void);
tile_t* tile_init_leaf(void);

void tile_init(void)
{
    tile_init_shader();

    s_TileError = tile_init_error();
    s_TileCarpet = tile_init_carpet();
    s_TileRock = tile_init_rock();
    s_TileWood = tile_init_wood();
    s_TileDirt = tile_init_dirt();
    s_TileGrassTop = tile_init_grass_top();
    s_TileGrassSide = tile_init_grass_side();
    s_TileGlass = tile_init_glass();
    s_TileLeaf = tile_init_leaf();
}

bmp_t* tile_bmp_shader(void)
{
    return s_BitmapShader;
}

tile_t* tile_get(uint32_t tileId)
{
    switch (tileId)
    {
    case 0: return s_TileError;
    case 1: return s_TileCarpet;
    case 2: return s_TileRock;
    case 3: return s_TileWood;
    case 4: return s_TileDirt;
    case 5: return s_TileGrassTop;
    case 6: return s_TileGrassSide;
    case 7: return s_TileGlass;
    case 8: return s_TileLeaf;
    default: return s_TileError;
    }
}

tile_t* tile_alloc(uint32_t w, uint32_t h, tilespec_t spec)
{
    tile_t* tile = (tile_t*)malloc(sizeof(tile_t));
    if (!tile) return NULL;
    memset(tile, 0, sizeof(tile_t));

    tile->spec = spec;
    bmp_t* sprite = bmp_alloc(w, h);
    if (!sprite)
    {
        tile_free(&tile);
        return NULL;
    }
    tile->sprite = sprite;

    return tile;
}

void tile_free(tile_t** tile_ptr)
{
    if (!tile_ptr) return;

    tile_t* tile = *tile_ptr;
    if (!tile) return;

    if (tile->sprite)
    {
        free(tile->sprite);
        tile->sprite = NULL;
    }

    free(tile);
    *tile_ptr = NULL;
}

static void tile_init_draw_shape(bmp_t* dst, uint32_t x, uint32_t y, uint32_t w, uint32_t h, uint32_t c)
{
    uint32_t width = dst->width;
    uint32_t height = dst->height;
    uint32_t width1 = width - 1;
    uint32_t height1 = height - 1;

    for (uint32_t yy = 0; yy < h; yy++)
    {
        uint32_t yo = y + yy;
        if (yo < 0 || yo >= height) continue;

        for (uint32_t xx = 0; xx < w; xx++)
        {
            uint32_t xo = x + xx;
            if (xo < 0 || xo >= width) continue;
            if (yy % height1 == 0 && xx % width1 == 0) continue;

            dst->pixels[xo + yo * width] = c;
        }
    }
}

#define TILE_SHADER_CELLSIZE 5
#define TILE_SHADER_SIZE (TILE_SHADER_CELLSIZE * 8)
static void tile_init_shader(void)
{
    if (s_BitmapShader) return;

    bmp_t* bmp = bmp_alloc(TILE_SHADER_SIZE, TILE_SHADER_SIZE);
    for (size_t i = 0; i < TILE_SHADER_SIZE * TILE_SHADER_SIZE; i++)
        bmp->pixels[i] = 0xFFFFFF;
    
    for (size_t y = 0; y < 8; y++)
    {
        for (size_t x = 0; x < 8; x++)
        {
            if ((y + x) % 2 == 0) continue;

            tile_init_draw_shape(bmp, x * TILE_SHADER_CELLSIZE, y * TILE_SHADER_CELLSIZE, TILE_SHADER_CELLSIZE, TILE_SHADER_CELLSIZE, 0xE0E0E0);
        }
    }

    s_BitmapShader = bmp;
}

tile_t* tile_setup_from(uint32_t bmpId, tilespec_t spec)
{
    bmp_t* bmp = bmp_get(bmpId);
    if (bmp == NULL) return NULL;

    tile_t* tile = tile_alloc(bmp->width, bmp->height, spec);
    bmp_copy(tile->sprite, bmp);

    return tile;
}
