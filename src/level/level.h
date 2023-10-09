#ifndef _LEVEL_H
#define _LEVEL_H

#include "core/wnd.h"

#include <stdint.h>
#include <stdbool.h>

#define A_TOP 0x01
#define A_RIGHT_INNER 0x02
#define A_LEFT_INNER 0x04
#define A_RIGHT_OUTER 0x08
#define A_LEFT_OUTER 0x10
#define A_BOTTOM 0x20

#define T_CARPET 1
#define T_ROCK 2
#define T_WOOD 3
#define T_DIRT 4
#define T_GRASS_TOP 5
#define T_GRASS_SIDE 6
#define T_GLASS 7
#define T_LEAF 8

typedef struct {
    uint32_t* floors;
    uint32_t* wallsR;
    uint32_t* wallsL;
    uint32_t size;
    uint32_t size1;
    uint32_t stride;
    uint32_t layer;
} level_t;

level_t* level_create(uint32_t size);
void level_free(level_t* this);
void level_set_tile(level_t* this, uint32_t x, uint32_t y, uint32_t z, uint32_t tileId, uint32_t flag);
void level_set_wall(level_t* this, uint32_t x, uint32_t y, uint32_t z, bool right, uint32_t tileId);
void level_set_floor(level_t* this, uint32_t x, uint32_t y, uint32_t z, uint32_t tileId);
uint32_t level_get_wall(level_t* this, uint32_t x, uint32_t y, uint32_t z, bool right);
uint32_t level_get_floor(level_t* this, uint32_t x, uint32_t y, uint32_t z);
void level_draw(level_t* this, wnd_t* window);

#endif