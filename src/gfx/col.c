#include "col.h"

uint32_t col_clamp(uint32_t channel)
{
    int32_t ichannel = (int32_t)channel;
    return (uint32_t)(ichannel < 0 ? 0 : (ichannel > 255 ? 255 : ichannel));
}

uint32_t col_darken(uint32_t color, uint32_t numerator, uint32_t denominator)
{
    uint32_t r = (color >> 16) & 0xFF;
    uint32_t g = (color >> 8) & 0xFF;
    uint32_t b = (color) & 0xFF;

    r = r * numerator / denominator;
    g = g * numerator / denominator;
    b = b * numerator / denominator;

    return col_clamp(r) << 16 | col_clamp(g) << 8 | col_clamp(b);
}
