#include "../tile.h"

tile_t* tile_init_rock(void)
{
    return tile_setup_from(2, tilespec_specular);
}