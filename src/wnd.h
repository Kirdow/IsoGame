#ifndef _WND_H
#define _WND_H

#include <stdint.h>
#define SDL_MAIN_HANDLED
#include <SDL.h>

typedef struct {
    uint32_t* pixels;
    uint32_t width;
    uint32_t height;
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* texture;
    char* title;
} wnd_t;

wnd_t* wnd_create(const char* title, uint32_t width, uint32_t height);
void wnd_flush(wnd_t* this);
void wnd_sync(uint32_t rate);

#endif