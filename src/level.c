#include "level.h"
#include "gfx.h"

#include <stdlib.h>

level_t* level_create(uint32_t size)
{
    level_t* level = (level_t*)malloc(sizeof(level_t));
    if (!level) return NULL;

    level->size = size;
    level->size1 = size + 1;
    level->stride = level->size1;
    level->layer = level->stride * level->size1;

    uint32_t len = level->size1 * level->size1 * level->size1;
    uint32_t* floors = (uint32_t*)malloc(len * sizeof(uint32_t));
    if (!floors)
    {
        free(level);
        return NULL;
    }

    level->floors = floors;

    uint32_t* wallsR = (uint32_t*)malloc(len * sizeof(uint32_t));
    if (!wallsR)
    {
        free(floors);
        free(level);
        return NULL;
    }

    level->wallsR = wallsR;
    
    uint32_t* wallsL = (uint32_t*)malloc(len * sizeof(uint32_t));
    if (!wallsL)
    {
        free(wallsR);
        free(floors);
        free(level);
        return NULL;
    }

    level->wallsL = wallsL;

    for (size_t i = 0; i < len; i++)
    {
        floors[i] = wallsR[i] = wallsL[i] = 0;
    }

    return level;
}

void level_free(level_t* this)
{
    if (!this) return;

    if (this->floors) free(this->floors);
    if (this->wallsR) free(this->wallsR);
    if (this->wallsL) free(this->wallsL);
    free(this);
}

void level_set_tile(level_t* this, uint32_t x, uint32_t y, uint32_t z, uint32_t tileId, uint32_t flag)
{
    if (flag & A_TOP) level_set_floor(this, x, y, z + 1, tileId);
    if (flag & A_RIGHT_INNER) level_set_wall(this, x, y, z, true, tileId);
    if (flag & A_LEFT_INNER) level_set_wall(this, x, y, z, false, tileId);
    if (flag & A_RIGHT_OUTER) level_set_wall(this, x + 1, y, z, false, tileId);
    if (flag & A_LEFT_OUTER) level_set_wall(this, x, y + 1, z, true, tileId);
    if (flag & A_BOTTOM) level_set_floor(this, x, y, z, tileId);
}

void level_set_wall(level_t* this, uint32_t x, uint32_t y, uint32_t z, bool right, uint32_t tileId)
{
    (right ? this->wallsR : this->wallsL)[x + y * this->stride + z * this->layer] = tileId;
}
void level_set_floor(level_t* this, uint32_t x, uint32_t y, uint32_t z, uint32_t tileId)
{
    this->floors[x + y * this->stride + z * this->layer] = tileId;
}
uint32_t level_get_wall(level_t* this, uint32_t x, uint32_t y, uint32_t z, bool right)
{
    return (right ? this->wallsR : this->wallsL)[x + y * this->stride + z * this->layer];
}
uint32_t level_get_floor(level_t* this, uint32_t x, uint32_t y, uint32_t z)
{
    return this->floors[x + y * this->stride + z * this->layer];
}

void level_draw(level_t* this, wnd_t* window)
{
    uint32_t t;
    for (size_t z = 0; z < this->size1; z++)
    {
        for (size_t y = 0; y < this->stride * 2; y++)
        {
            for (size_t x = 0; x <= y; x++)
            {
                size_t w = y - x;
                if (w < this->stride && x < this->stride)
                {
                    t = level_get_wall(this, x, w, z, false);
                    if (t) gfx_wall_tile(window, x, w, z, t, false);

                    t = level_get_wall(this, x, w, z, true);
                    if (t) gfx_wall_tile(window, x, w, z, t, true);

                    t = level_get_floor(this, x, w, z);
                    if (t) gfx_floor_tile(window, x, w, z, t);
                }
            }
        }
    }
}
