#include "../tile.h"

tile_t* tile_init_error(void)
{
    return tile_setup_from(0, tilespec_none);
}
