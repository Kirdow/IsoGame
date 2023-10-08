#include <stdio.h>
#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <stdbool.h>
#include "wnd.h"
#include "gfx.h"
#include "bmp.h"
#include "level.h"
#include "num.h"
#include "font.h"

typedef struct {
    uint32_t color;
} app_t;

typedef struct {
    uint32_t frame;
    uint32_t ticks;
    uint32_t interval;
    uint32_t tpi;
} ticker_t;

void ticker_create(ticker_t* ticker, uint32_t interval);
void ticker_tick(ticker_t* ticker);

void tick(app_t* app);

void main(void)
{
    rnd_start();
    bmp_init();
    font_init();

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

    app_t app;
    ticker_t framecount;
    ticker_t tickcount;
    ticker_create(&framecount, 1000);
    ticker_create(&tickcount, 1000);

    bool running = true;
    SDL_Event event;

    char fpsbuffer[128];

    uint32_t lastTick = SDL_GetTicks();

    app.color = 0xFF;
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }
        gfx_fill(window, app.color);

        level_draw(level, window);

        gfx_bmp(window, 130, 55, 0);

        for (size_t i = 0; i < 128; i++) fpsbuffer[i] = '\0';
        sprintf_s(fpsbuffer, 127, "%d T/%d F", tickcount.tpi, framecount.tpi);

        font_draw(window, fpsbuffer, window->width - 10, 10, FONT_DIR_LEFT);

        wnd_flush(window);
        
        uint32_t ticks = SDL_GetTicks();
        ticker_tick(&framecount);
        if (ticks - lastTick >= 20)
        {
            ticker_tick(&tickcount);
            lastTick += 20;
            tick(&app);
        }
    }

    SDL_Quit();
    return;
}

void tick(app_t* app)
{
    if (--app->color == 0) {
        app->color = 0xFF;
    }
}

void ticker_create(ticker_t* ticker, uint32_t interval)
{
    ticker->ticks = 0;
    ticker->interval = interval;
    ticker->tpi = 0;
    ticker->frame = SDL_GetTicks();
}

void ticker_tick(ticker_t* ticker)
{
    uint32_t frame = SDL_GetTicks();
    ticker->ticks++;
    if (frame >= ticker->frame + ticker->interval)
    {
        ticker->frame += ticker->interval;
        ticker->tpi = ticker->ticks;
        ticker->ticks = 0;
    }
}