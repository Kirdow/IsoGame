#include "../tile.h"

tile_t* tile_init_carpet(void)
{
    return tile_setup_from(1, tilespec_shade);
}
