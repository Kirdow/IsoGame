#include <stdio.h>
#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <stdbool.h>
#include "wnd.h"

void main(void)
{
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

        for (int i = 0; i < window->width * window->height; ++i)
            window->pixels[i] = color;

        wnd_flush(window);
        wnd_sync(60);

        if (--color == 0) {
            color = 0xFF;
        }
    }

    SDL_Quit();
    return;
}