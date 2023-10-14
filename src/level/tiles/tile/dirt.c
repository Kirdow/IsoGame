#include "../tile.h"

tile_t* tile_init_dirt(void)
{
    return tile_setup_from(4, tilespec_none);
}
