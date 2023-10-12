#ifndef _TILESPEC_H
#define _TILESPEC_H

#include <stdbool.h>

#define TILESPEC_ENABLE_SHADE 1
#define TILESPEC_ENABLE_SPECULAR 1

#define TILESPEC_IS_SPECULAR(t) ((t & tilespec_specular) && TILESPEC_ENABLE_SPECULAR)
#define TILESPEC_IS_SHADE(t) ((t & tilespec_shade) && TILESPEC_ENABLE_SHADE)

typedef enum {
    tilespec_none = 0x00,
    tilespec_shade = 0x01,
    tilespec_specular = 0x02,
    tilespec_all = -1
} tilespec_t;

typedef struct {
    tilespec_t data;
} tilespecdata_t;

void tilespecdata_init(tilespecdata_t* this);
void tilespecdata_add(tilespecdata_t* this, tilespec_t spec);
void tilespecdata_remove(tilespecdata_t* this, tilespec_t spec);
bool tilespecdata_has(tilespecdata_t* this, tilespec_t spec);
bool tilespecdata_any(tilespecdata_t* this, tilespec_t spec);

#endif