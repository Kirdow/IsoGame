#include "../tile.h"

tile_t* tile_init_glass(void)
{
    return tile_setup_from(7, tilespec_none);
}
