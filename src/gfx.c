#include "gfx.h"
#include "bmp.h"

void gfx_fill(wnd_t* window, uint32_t color)
{
    for (size_t i = 0; i < window->width * window->height; i++)
        window->pixels[i] = color;
}

void gfx_rect(wnd_t* window, uint32_t x, uint32_t y, uint32_t w, uint32_t h, uint32_t color)
{
    for (size_t yy = 0; yy < h; yy++)
    {
        size_t yo = y + yy;
        if (yo < 0 || yo >= window->height) continue;
        for (size_t xx = 0; xx < w; xx++)
        {
            int xo = x + xx;
            if (xo < 0 || xo >= window->width) continue;

            window->pixels[xo + yo * window->width] = color;
        }
    }
}

void gfx_bmp(wnd_t* window, uint32_t x, uint32_t y, uint32_t bmpId)
{
    bmp_t* bitmap = bmp_get(bmpId);

    for (size_t yy = 0; yy < bitmap->height; yy++)
    {
        size_t yo = y + yy;
        if (yo < 0 || yo >= window->height) continue;
        for (size_t xx = 0; xx < bitmap->width; xx++)
        {
            size_t xo = x + xx;
            if (xo < 0 || xo >= window->width) continue;

            uint32_t col = bitmap->pixels[xx + yy * bitmap->width];
            if (col == 0xFF00FF) continue;

            window->pixels[xo + yo * window->width] = col;
        }
    }
}