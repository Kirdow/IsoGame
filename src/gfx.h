#ifndef _GFX_H
#define _GFX_H

#include <stdint.h>
#include "wnd.h"

void gfx_fill(wnd_t* window, uint32_t color);
void gfx_rect(wnd_t* window, uint32_t x, uint32_t y, uint32_t w, uint32_t h, uint32_t color);
void gfx_bmp(wnd_t* window, uint32_t x, uint32_t y, uint32_t bmpId);

#endif