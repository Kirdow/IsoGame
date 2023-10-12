#include "../tile.h"

tile_t* tile_init_leaf(void)
{
    return tile_setup_from(8, tilespec_none);
}
