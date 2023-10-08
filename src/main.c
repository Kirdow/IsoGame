#include <stdio.h>
#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <stdbool.h>
#include "wnd.h"
#include "gfx.h"
#include "bmp.h"
#include "level.h"
#include "num.h"

void main(void)
{
    rnd_start();
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

    level_t* level = level_create(8);

    for (size_t x = 0; x < 5; x++)
    {
        for (size_t z = 0; z < 2; z++)
        {
            for (size_t y = 0; y < 7 - z; y++)
            {
                if (x == 4)
                {
                    uint32_t flag = 0;
                    if (z != 0 || y == 6) flag |= A_RIGHT_OUTER;
                    if (y - 6 == -z) flag |= A_LEFT_OUTER;

                    uint32_t tileId = T_GRASS_SIDE;
                    if (flag == 0 && z == 0)
                    {
                        flag |= A_RIGHT_OUTER;
                        tileId = T_DIRT;
                    }

                    level_set_tile(level, x, y, z, tileId, flag);
                }
                else if (y - 6 == -z)
                {
                    level_set_tile(level, x, y, z, T_GRASS_SIDE, A_LEFT_OUTER);
                }

                if (z != 0 || y == 6) level_set_tile(level, x, y, z, T_GRASS_TOP, A_TOP);
            }
        }
    }

    for (size_t x = 0; x < 2; x++)
    {
        for (size_t y = 0; y < 3; y++)
        {
            level_set_tile(level, x + 1, y + 1, 2, T_ROCK, A_BOTTOM);
            level_set_tile(level, x + 3, y + 1, 2, T_CARPET, A_BOTTOM);
            if (x == 1)
            {
                uint32_t flag = A_TOP | A_RIGHT_OUTER;
                if (y == 2) flag |= A_LEFT_OUTER;

                level_set_tile(level, x + 1, y + 1, 2, T_LEAF, flag);
                level_set_tile(level, x + 3, y + 1, 2, T_GLASS, flag);
            }
        }
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

        level_draw(level, window);

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