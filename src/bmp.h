#ifndef _BMP_H
#define _BMP_H

#include <stdint.h>

typedef struct {
    uint32_t* pixels;
    uint32_t width;
    uint32_t height;
} bmp_t;

void bmp_init(void);
bmp_t* bmp_get(uint32_t id);

#endif