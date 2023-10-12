#ifndef _TILE_H
#define _TILE_H

#include <stdint.h>
#include <stdbool.h>

#include "tilespec.h"
#include "gfx/bmp.h"

typedef struct {
    bmp_t* sprite;
    tilespec_t spec;
} tile_t;

bmp_t* tile_bmp_shader(void);

void tile_init(void);
void tile_free(tile_t** tile_ptr);
tile_t* tile_alloc(uint32_t w, uint32_t h, tilespec_t spec);
tile_t* tile_get(uint32_t tileId);
tile_t* tile_setup_from(uint32_t bmpId, tilespec_t spec);

#endif