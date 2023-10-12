#include <stdio.h>
#define SDL_MAIN_HANDLED
#include <SDL.h>
#include "gfx/bmp.h"
#include "level/tiles/tile.h"
#include "gfx/font.h"
#include "core/app.h"
#include "util/ktime.h"
#include "util/num.h"
#include "util/kmath.h"

int main(void)
{
    rnd_start();
    bmp_init();
    tile_init();
    font_init();

    app_start_t start_info;
    start_info.appTitle = "IsoGame";
    start_info.width = 320;
    start_info.height = 240;

    if (!app_init(&start_info))
    {
        printf("Failed to start IsoGame\r\n");
        return 1;
    }

    while (app_active())
    {
        ktime_frame();
        app_run();
    }

    app_close();

    return 0;
}