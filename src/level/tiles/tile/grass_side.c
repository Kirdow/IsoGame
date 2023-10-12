#include "../tile.h"

tile_t* tile_init_grass_side(void)
{
    return tile_setup_from(6, tilespec_shade);
}
