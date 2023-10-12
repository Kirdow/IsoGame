#include "../tile.h"

tile_t* tile_init_wood(void)
{
    return tile_setup_from(3, tilespec_shade);
}
