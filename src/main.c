#include <stdio.h>
#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <stdbool.h>
#include "wnd.h"
#include "gfx.h"
#include "bmp.h"

void main(void)
{
    bmp_init();

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("Failed to initialize SDL2\r\n");
        return;
    }

    printf("Initialized SDL2.\r\n");

    wnd_t* window = wnd_create("SDL Window", 320, 240);
    if (!window)
    {
        SDL_Quit();
        printf("Failed\r\n");
        return;
    }

    bool running = true;
    SDL_Event event;

    uint32_t color = 0xFF;
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }
        gfx_fill(window, color);
    
        for (size_t y = 0; y < 6; y++)
        {
            for (size_t x = 0; x < 3; x++)
            {
                if (x == 0) gfx_wall_tile(window, x, y, 0, 0, false);
                if (y == 0) gfx_wall_tile(window, x, y, 0, 0, true);
                
                uint32_t bmpId = 5;
                if (x == 1 && (y > 0 && y < 5)) bmpId = 1;
                gfx_floor_tile(window, x, y, 0, bmpId);
            }
        }

        gfx_bmp(window, 130, 55, 0);

        wnd_flush(window);
        wnd_sync(60);

        if (--color == 0) {
            color = 0xFF;
        }
    }

    SDL_Quit();
    return;
}