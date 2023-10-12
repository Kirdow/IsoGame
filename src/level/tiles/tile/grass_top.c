#include "../tile.h"

tile_t* tile_init_grass_top(void)
{
    return tile_setup_from(5, tilespec_specular);
}
