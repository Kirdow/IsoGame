#ifndef _BMP_H
#define _BMP_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

typedef struct {
    uint32_t* pixels;
    uint32_t width;
    uint32_t height;
} bmp_t;

void bmp_init(void);
bmp_t* bmp_get(uint32_t id);
bmp_t* bmp_alloc(uint32_t width, uint32_t height);
void bmp_free(bmp_t* this);
bmp_t* bmp_load(const char* filepath);
bool bmp_copy(bmp_t* dst, bmp_t* src);

#endif