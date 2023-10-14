#include "gfx.h"
#include "bmp.h"
#include "col.h"

#include "level/tiles/tile.h"

inline static bmp_t* gfx_get_shader(void)
{
    static bmp_t* s_Shader = NULL;

    if (s_Shader == NULL) s_Shader = tile_bmp_shader();

    return s_Shader;
}

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
            size_t xo = x + xx;
            if (xo < 0 || xo >= window->width) continue;

            window->pixels[xo + yo * window->width] = color;
        }
    }
}

inline static uint32_t gfx_run_shader(uint32_t color, uint32_t shader, tilespec_t spec)
{
    bool shade = spec & tilespec_shade;
    if (spec == tilespec_none || spec == (tilespec_shade | tilespec_specular)) return color;

    uint32_t result = 0;

    uint32_t src = shade ? 0xFFFFFFFF : shader;
    uint32_t dst = shade ? shader : 0xFFFFFFFF;

    uint8_t* pcolor = (uint8_t*)&color;
    uint8_t* psrc = (uint8_t*)&src;
    uint8_t* pdst = (uint8_t*)&dst;
    uint8_t* presult = (uint8_t*)&result;

    for (size_t i = 0; i < 4; i++) {
        presult[i] = (psrc[i] == 0) ? 0 : (pcolor[i] * pdst[i] / psrc[i]);
    }

    return result;
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

void gfx_bmp2(wnd_t* window, uint32_t x, uint32_t y, bmp_t* bitmap, uint32_t mask, uint32_t color)
{
    for (size_t yy = 0; yy < bitmap->height; yy++)
    {
        size_t yo = y + yy;
        if (yo < 0 || yo >= window->height) continue;
        for (size_t xx = 0; xx < bitmap->width; xx++)
        {
            size_t xo = x + xx;
            if (xo < 0 || xo >= window->width) continue;

            uint32_t col = bitmap->pixels[xx + yy * bitmap->width];
            if (col != mask) continue;

            window->pixels[xo + yo * window->width] = color;
        }
    }
}

void gfx_floor_tile(wnd_t* window, uint32_t x, uint32_t y, uint32_t z, uint32_t bmpId)
{
    gfx_world_data_t data;
    data.x = x;
    data.y = y;
    data.z = z;

    x -= z;
    y -= z;

    uint32_t worldX = (x - y) * 16 + window->width / 2;
    uint32_t worldY = (x + y) * 8 + window->height / 2;

    gfx_floor(window, worldX, worldY, bmpId, &data);
}

void gfx_floor(wnd_t* window, uint32_t x, uint32_t y, uint32_t bmpId, gfx_world_data_t* world_data)
{
    tile_t* tile = tile_get(bmpId);
    bmp_t* bitmap = bmp_get(bmpId);
    bmp_t* shader = tile_bmp_shader();

    size_t size = 32;
    size_t halfsize = size / 2;
    size_t startX = x;
    size_t startY = y - halfsize / 2;

    uint32_t rawBitmapPixel;
    for (size_t yo = 0; yo <= size; yo++)
    {
        uint32_t yt = yo * bitmap->height / halfsize;
        uint32_t ytd = yt / 2;
        if (ytd >= bitmap->height) ytd = bitmap->height - 1;
        for (size_t xo = 0; xo <= size; xo++)
        {
            uint32_t xt = xo * bitmap->width / halfsize;
            uint32_t xtd = xt / 2;
            if (xtd >= bitmap->width) xtd = bitmap->width - 1;

            int32_t xPix = 0, yPix = 0;

            xPix += xo;
            yPix += xo / 2;

            xPix -= yo;
            yPix += yo / 2;

            xPix = startX + xPix / 2;
            yPix = startY + yPix / 2;

            if ((int32_t)xPix < 0 || (int32_t)yPix < 0 || (uint32_t)xPix >= window->width || (uint32_t)yPix >= window->height) continue;
            rawBitmapPixel = bitmap->pixels[xtd + ytd * bitmap->width];
            if (rawBitmapPixel == 0xFF00FF) continue;
            uint32_t shadeX = (world_data->x * 8 + xtd) % shader->width;
            uint32_t shadeY = (world_data->z * 8 + ytd) % shader->height;
            rawBitmapPixel = gfx_run_shader(rawBitmapPixel, shader->pixels[shadeX + shadeY * shader->width], tile->spec);
            window->pixels[xPix + yPix * window->width] = rawBitmapPixel;
        }
    }
}

void gfx_wall_tile(wnd_t* window, uint32_t x, uint32_t y, uint32_t z, uint32_t bmpId, bool right)
{
    gfx_world_data_t data;
    data.x = x;
    data.y = y;
    data.z = z;

    x -= z;
    y -= z;

    uint32_t worldX = (x - y) * 16 + window->width / 2;
    uint32_t worldY = (x + y) * 8 + window->height / 2;

    gfx_wall(window, worldX, worldY, bmpId, right, &data);
}

void gfx_wall(wnd_t* window, uint32_t x, uint32_t y, uint32_t bmpId, bool right, gfx_world_data_t* world_data)
{
    tile_t* tile = tile_get(bmpId);
    bmp_t* bitmap = bmp_get(bmpId);
    bmp_t* shader = tile_bmp_shader();

    size_t size = 32;

    size_t startX = x;
    size_t startY = y - size * 3 / 4;
    if (!right)
    {
        startX -= size / 2;
        startY += size / 4;
    }

    uint32_t rawBitmapPixel;
    for (size_t yo = 0; yo <= size * 2; yo++)
    {
        uint32_t yt = yo * bitmap->height / size;
        uint32_t ytd = yt / 2;
        if (ytd >= bitmap->height) ytd = bitmap->height - 1;
        for (size_t xo = 0; xo <= size; xo++)
        {
            uint32_t xt = xo * bitmap->width / (size / 2);
            uint32_t xtd = xt / 2;
            if (xtd >= bitmap->width) xtd = bitmap->width - 1;

            int32_t xPix = 0, yPix = 0;

            xPix += xo;
            yPix += right ? (xo / 2) : -(xo / 2);

            yPix += yo / 2;

            xPix = startX + xPix / 2;
            yPix = startY + yPix / 2;

            if (xPix < 0 || yPix < 0 || (uint32_t)xPix >= window->width || (uint32_t)yPix >= window->height) continue;
            rawBitmapPixel = bitmap->pixels[xtd + ytd * bitmap->width];
            if (rawBitmapPixel == 0xFF00FF) continue;
            uint32_t shadeX = ((world_data->x + world_data->y) * 8 + xtd) % shader->width;
            uint32_t shadeY = (world_data->z * 8 + ytd) % shader->height;
            rawBitmapPixel = gfx_run_shader(rawBitmapPixel, shader->pixels[shadeX + shadeY * shader->width], tile->spec);
            window->pixels[xPix + yPix * window->width] = col_darken(rawBitmapPixel, right ? 28 : 25, 32);
        }
    }
}