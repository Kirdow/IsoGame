#include "font.h"
#include "bmp.h"
#include "gfx.h"
#include "util/strutil.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <string.h>

static bmp_t* s_FontBitmap = NULL;
static bmp_t** s_CharBitmaps = NULL;

static const char* s_ALLOWEDCHARS = "ABCDEFGHIJKLMNOPQRSTUVWXYZ      0123456789.,!?'\"-+=/\\%()zZ:;";

static void font_draw_color2(wnd_t* window, const char* text, uint32_t x, uint32_t y, int32_t dir, uint32_t color);
static bool font_draw_char(wnd_t* window, char c, uint32_t x, uint32_t y, uint32_t color);

void font_init(void)
{
    bmp_t* bitmap = bmp_load("res/font.png");
    s_FontBitmap = bitmap;

    s_CharBitmaps = (bmp_t**)malloc(64 * sizeof(bmp_t*));
    for (size_t y = 0; y < 2; y++)
    {
        for (size_t x = 0; x < 32; x++)
        {
            size_t i = x + y * 32;

            bmp_t* bmp = bmp_alloc(8, 8);

            for (size_t yy = 0; yy < 8; yy++)
            {
                size_t yt = y * 8 + yy;
                for (size_t xx = 0; xx < 8; xx++)
                {
                    size_t xt = x * 8 + xx;

                    bmp->pixels[xx + yy * 8] = bitmap->pixels[xt + yt * bitmap->width];
                }
            }

            s_CharBitmaps[i] = bmp;
        }
    }
}

void font_draw(wnd_t* window, const char* text, uint32_t x, uint32_t y, int32_t dir)
{
    font_draw_color(window, text, x, y, dir, 0xFFFFFF);
}

void font_draw_color(wnd_t* window, const char* text, uint32_t x, uint32_t y, int32_t dir, uint32_t color)
{
    font_draw_color2(window, text, x + 1, y + 1, dir, 0);
    font_draw_color2(window, text, x, y, dir, color);
}

typedef struct {
    char* str;
    size_t len;
} line_t;

typedef struct {
    char* str;
    line_t* lines;
    size_t count;
} lines_t;

static void font_draw_color2(wnd_t* window, const char* text, uint32_t x, uint32_t y, int32_t dir, uint32_t color)
{
    if (dir < 0) x += dir * 8;
    size_t startX = x;
    size_t startY = y;
    char* data = (char*)text;
    if (dir < 0) data = str_reverse_lines(text);
    char* ptr = (char*)data;
    while (*ptr)
    {
        char c = toupper(*ptr);
        if (c == '\n') {
            x = startX;
            y = (startY += 8);
            ++ptr;
            continue;
        }

        if (font_draw_char(window, c, x, y, color)) x += dir * 8;
        ++ptr;
    }

    if (dir < 0) free(data);
}

static bool font_draw_char(wnd_t* window, char c, uint32_t x, uint32_t y, uint32_t color)
{
    char* position = strchr(s_ALLOWEDCHARS, c);
    if (!position) return false;

    gfx_bmp2(window, x, y, s_CharBitmaps[(int)(position - s_ALLOWEDCHARS)], 0xFFFFFF, color);
    return true;
}