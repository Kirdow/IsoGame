#include <stdio.h>
#define SDL_MAIN_HANDLED
#include <SDL.h>
#include "bmp.h"
#include "num.h"
#include "font.h"
#include "app.h"
#include "ktime.h"

void main(void)
{
    rnd_start();
    bmp_init();
    font_init();

    app_start_t start_info;
    start_info.appTitle = "IsoGame";
    start_info.width = 320;
    start_info.height = 240;

    if (!app_init(&start_info))
    {
        printf("Failed to start IsoGame\r\n");
        return;
    }

    while (app_active())
    {
        ktime_frame();
        app_run();
    }

    app_close();
}