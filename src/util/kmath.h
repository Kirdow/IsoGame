#ifndef _KMATH_H
#define _KMATH_H

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>

typedef struct {
    int32_t x;
    int32_t y;
} ivec_t;


// min(a, b) and max(a, b) definitions
#define _MINDEF(name, type) \
static type name(type a, type b) { return a < b ? a : b; }
#define _MAXDEF(name, type) \
static type name(type a, type b) { return a > b ? a : b; }
_MINDEF(imin32, int)
_MAXDEF(imax32, int)
_MINDEF(umin32, unsigned int)
_MAXDEF(umax32, unsigned int)
_MINDEF(smin, size_t)
_MAXDEF(smax, size_t)

static int imin(int a, int b) { return a < b ? a : b; }
static int imax(int a, int b) { return a > b ? a : b; }

#define IVEC_ONE _ivec_default_one()
#define IVEC_ZERO _ivec_default_zero()
#define IVEC_RIGHT _ivec_default_right()
#define IVEC_DOWN _ivec_default_down()
#define IVEC_LEFT _ivec_default_left()
#define IVEC_UP _ivec_default_up()
#define IVEC(x,y) _ivec_new(x,y)

// ivec_t ivec_add(ivec_t lhs, ivec_t rhs)
#define IVEC_ADD(lhs, rhs) _ivec_add(lhs, rhs)

// ivec_t ivec_sub(ivec_t lhs, ivec_t rhs)
#define IVEC_SUB(lhs, rhs) _ivec_sub(lhs, rhs)

/*
 * Default definition functions. These will be called with macros
 */
inline static ivec_t _ivec_default_one()
{
    ivec_t v;
    v.x = 1;
    v.y = 1;
    return v;
}

inline static ivec_t _ivec_default_zero()
{
    ivec_t v;
    v.x = 0;
    v.y = 0;
    return v;
}

inline static ivec_t _ivec_default_right()
{
    ivec_t v;
    v.x = 1;
    v.y = 0;
    return v;
}

inline static ivec_t _ivec_default_down()
{
    ivec_t v;
    v.x = 0;
    v.y = 1;
    return v;
}

inline static ivec_t _ivec_default_left()
{
    ivec_t v;
    v.x = -1;
    v.y = 0;
    return v;
}

inline static ivec_t _ivec_default_up()
{
    ivec_t v;
    v.x = 0;
    v.y = -1;
    return v;
}

inline static ivec_t _ivec_new(int32_t x, int32_t y)
{
    ivec_t v;
    v.x = x;
    v.y = y;
    return v;
}

/*
 * Main functions
 */
inline static ivec_t _ivec_add(ivec_t lhs, ivec_t rhs)
{
    ivec_t v;
    v.x = lhs.x + rhs.x;
    v.y = lhs.y + rhs.y;
}

inline static ivec_t _ivec_sub(ivec_t lhs, ivec_t rhs)
{
    ivec_t v;
    v.x = lhs.x - rhs.x;
    v.y = lhs.y - rhs.y;
    return v;

}

#endif