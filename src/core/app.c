#include "app.h"

#include "wnd.h"
#include "level/level.h"
#include "gfx/gfx.h"
#include "gfx/font.h"
#include "util/ticker.h"
#include "util/timer.h"
#include "util/kmath.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

#include <SDL.h>

typedef struct {
    uint32_t color;
} app_data_t;

typedef struct {
    app_start_t start_info;
    wnd_t* window;
    level_t* level;
    bool is_running;
    SDL_Event sdl_event;
    app_data_t data;
    ticker_t frame_ticker;
    ticker_t tick_ticker;
    timer_t tick_timer;
} app_t;

static app_t s_App;

static void app_generate_level(level_t* level);
static void app_tick(void);
static void app_events(void);
static void app_frame(void);
static void app_fps_display(void);

bool app_init(app_start_t* start_info)
{
    memset(&s_App, 0, sizeof(app_t));

    s_App.start_info = *start_info;
    
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("Failed to initialize SDL2\r\n");
        return false;
    }

    printf("Initialized SDL2.\r\n");

    wnd_t* window = wnd_create(start_info->appTitle, start_info->width, start_info->height);
    if (!window)
    {
        SDL_Quit();
        printf("Failed\r\n");
        return false;
    }
    
    s_App.window = window;

    s_App.level = level_create(8);
    app_generate_level(s_App.level);

    s_App.is_running = true;
    s_App.data.color = 0xFF;

    ticker_create(&s_App.frame_ticker, 1000);
    ticker_create(&s_App.tick_ticker, 1000);
    timer_create(&s_App.tick_timer, 1000 / 50);

    return true;
}

bool app_active(void)
{
    return s_App.is_running;
}

void app_run(void)
{
    // Poll events
    app_events();
    
    // Main frame draw
    app_frame();

    // Draw debug
    app_fps_display();
    
    // Flush to window
    wnd_flush(s_App.window);

    // Ticks stuff
    ticker_tick(&s_App.frame_ticker);
    timer_frame(&s_App.tick_timer);
    if (s_App.tick_timer.active)
    {
        ticker_tick(&s_App.tick_ticker);
        app_tick();
    }
}

void app_close(void)
{
    if (s_App.window)
    {
        wnd_close(s_App.window);
        s_App.window = NULL;
    }

    memset(&s_App, 0, sizeof(app_t));

    SDL_Quit();
}

static void app_tick(void)
{
    if (--s_App.data.color == 0)
    {
        s_App.data.color = 0xFF;
    }
}

static void app_generate_level(level_t* level)
{
    size_t xsize = smin(level->size, 7);
    for (size_t x = 0; x < xsize; x++)
    {
        for (size_t z = 0; z < 3; z++)
        {
            size_t ysize = level->size - z;
            for (size_t y = 0; y < ysize; y++)
            {
                if (x == xsize - 1)
                {
                    uint32_t flag = 0;
                    if (z == 2 || y == ysize - 1) flag |= A_RIGHT_OUTER;
                    if (y - level->size + 1 == -z) flag |= A_LEFT_OUTER;
                
                    uint32_t tileId = T_GRASS_SIDE;
                    if (flag == 0 && z < 2)
                    {
                        flag |= A_RIGHT_OUTER;
                        tileId = T_DIRT;
                    }

                    level_set_tile(level, x, y, z, tileId, flag);
                }
                else if (y - level->size + 1 == -z)
                {
                    level_set_tile(level, x, y, z, T_GRASS_SIDE, A_LEFT_OUTER);
                }

                if (z == 2 || y == ysize - 1)
                    level_set_tile(level, x, y, z, T_GRASS_TOP, A_TOP);
            }
        }
    }

    for (size_t x = 0; x < 2; x++)
    {
        for (size_t y = 0; y < 3; y++)
        {
            level_set_tile(level, x + 1, y + 1, 3, T_ROCK, A_BOTTOM);
            level_set_tile(level, x + xsize - 3, y + 1, 3, T_CARPET, A_BOTTOM);
            if (x == 1)
            {
                uint32_t flag = A_TOP | A_RIGHT_OUTER;
                if (y == 2) flag |= A_LEFT_OUTER;
                
                level_set_tile(level, x + 1, y + 1, 3, T_LEAF, flag);
                level_set_tile(level, x + xsize - 3, y + 1, 3, T_GLASS, flag);
            }
        }
    }

}

static void app_events(void)
{
    SDL_Event* event = &s_App.sdl_event;
    while (SDL_PollEvent(event))
    {
        if (event->type == SDL_QUIT)
            s_App.is_running = false;
    }
}

static void app_frame(void)
{
    // Pre-frame

    gfx_fill(s_App.window, s_App.data.color);

    // Draw scene

    level_draw(s_App.level, s_App.window);
    gfx_bmp(s_App.window, 130, 55, 0);

    // Draw UI

    // TODO: UI goes here
}

#define FPS_BUFFER_LEN 127
#define FPS_BUFFER_SIZE (FPS_BUFFER_LEN + 1)

static char s_FpsBuffer[FPS_BUFFER_SIZE];
static void app_fps_display(void)
{
    if (s_App.tick_ticker.tpi[0] || s_App.frame_ticker.tpi[0])
    {
        memset(s_FpsBuffer, 0, sizeof(char) * FPS_BUFFER_SIZE);
        if (s_App.tick_ticker.tpi[0] && s_App.frame_ticker.tpi[0])
            sprintf_s(s_FpsBuffer, FPS_BUFFER_LEN, "%s T/%s F", s_App.tick_ticker.tpi, s_App.frame_ticker.tpi);
        else if (s_App.tick_ticker.tpi[0])
            sprintf_s(s_FpsBuffer, FPS_BUFFER_LEN, "%s T", s_App.tick_ticker.tpi);
        else
            sprintf_s(s_FpsBuffer, FPS_BUFFER_LEN, "%s F", s_App.frame_ticker.tpi);
        
        font_draw(s_App.window, s_FpsBuffer, s_App.window->width - 10, 10, FONT_DIR_LEFT);
    }
}