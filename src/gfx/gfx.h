#ifndef _GFX_H
#define _GFX_H

#include <stdint.h>
#include <stdbool.h>
#include "core/wnd.h"
#include "bmp.h"

typedef struct {
    uint32_t x, y, z;
} gfx_world_data_t;

void gfx_fill(wnd_t* window, uint32_t color);
void gfx_rect(wnd_t* window, uint32_t x, uint32_t y, uint32_t w, uint32_t h, uint32_t color);
void gfx_bmp(wnd_t* window, uint32_t x, uint32_t y, uint32_t bmpId);
void gfx_bmp2(wnd_t* window, uint32_t x, uint32_t y, bmp_t* bmp, uint32_t mask, uint32_t color);
void gfx_floor_tile(wnd_t* window, uint32_t x, uint32_t y, uint32_t z, uint32_t bmpId);
void gfx_floor(wnd_t* window, uint32_t x, uint32_t y, uint32_t bmpId, gfx_world_data_t* world_data);
void gfx_wall_tile(wnd_t* window, uint32_t x, uint32_t y, uint32_t z, uint32_t bmpId, bool right);
void gfx_wall(wnd_t* window, uint32_t x, uint32_t y, uint32_t bmpId, bool right, gfx_world_data_t* world_data);

#endif