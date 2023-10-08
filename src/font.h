#ifndef _FONT_H
#define _FONT_H

#include "wnd.h"

#define FONT_DIR_LEFT -1
#define FONT_DIR_RIGHT 1

void font_init(void);
void font_draw(wnd_t* window, const char* text, uint32_t x, uint32_t y, int32_t dir);
void font_draw_color(wnd_t* window, const char* text, uint32_t x, uint32_t y, int32_t dir, uint32_t color);

#endif