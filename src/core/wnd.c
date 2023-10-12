#include "wnd.h"
#include <string.h>
#include <stdio.h>

wnd_t* wnd_create(const char* title, uint32_t width, uint32_t height)
{
    printf("Creating %dx%d window named \"%s\"\r\n", width, height, title);

    SDL_Window* window = SDL_CreateWindow(
        title,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width * 2,
        height * 2,
        SDL_WINDOW_SHOWN
    );

    if (!window)
    {
        printf("Failed to create window\r\n");
        return NULL;
    }

    printf("Creating renderer\r\n");

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer)
    {
        printf("Failed to create renderer\r\n");
        return NULL;
    }

    printf("Creating texture\r\n");

    SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, width, height);
    if (!texture)
    {
        printf("Failed to create texture\r\n");
        return NULL;
    }

    printf("Creating %dx%d array of pixels\r\n", width, height);
    
    uint32_t* pixels = (uint32_t*)malloc(width * height * sizeof(uint32_t));
    if (!pixels)
    {
        printf("Failed to create pixel array\r\n");
        return NULL;
    }

    printf("Creating wnd_t* instance\r\n");

    wnd_t* wnd = (wnd_t*)malloc(sizeof(wnd_t));
    if (!wnd)
    {
        printf("Failed to create wnd_t* instance\r\n");
        return NULL;
    }

    wnd->pixels = pixels;
    wnd->width = width;
    wnd->height = height;
    wnd->window = window;
    wnd->renderer = renderer;
    wnd->texture = texture;

    size_t titleLength = strlen(title);
    char* windowTitle = (char*)malloc((titleLength + 1) * sizeof(char));
    for (size_t i = 0; i < titleLength + 1; i++)
        windowTitle[i] = title[i];

    wnd->title = windowTitle;

    return wnd;
}

void wnd_close(wnd_t* this)
{
    if (!this) return;

    if (this->pixels)
    {
        memset(this->pixels, 0, sizeof(uint32_t) * this->width * this->height);
        free(this->pixels);
        this->pixels = NULL;
    }

    if (this->texture)
    {
        SDL_DestroyTexture(this->texture);
        this->texture = NULL;
    }

    if (this->renderer)
    {
        SDL_DestroyRenderer(this->renderer);
        this->renderer = NULL;
    }

    if (this->window)
    {
        SDL_DestroyWindow(this->window);
        this->window = NULL;
    }

    memset(this, 0, sizeof(wnd_t));
    free(this);
}

void wnd_flush(wnd_t* this)
{
    SDL_UpdateTexture(this->texture, NULL, this->pixels, this->width * sizeof(uint32_t));
    SDL_RenderClear(this->renderer);
    SDL_RenderCopy(this->renderer, this->texture, NULL, NULL);
    SDL_RenderPresent(this->renderer);
}

void wnd_sync(uint32_t rate)
{
    uint32_t interval = 1000 / (rate > 0 ? rate : 1);
    if (interval == 0) interval = 1;
    
    SDL_Delay(interval);
}
