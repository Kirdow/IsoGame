#include "tilespec.h"

#include <stddef.h>

void tilespec_init(tilespecdata_t* this)
{
    if (!this) return;

    this->data = tilespec_none;
}

void tilespecdata_add(tilespecdata_t* this, tilespec_t spec)
{
    if (!this) return;

    this->data |= spec;
}

void tilespecdata_remove(tilespecdata_t* this, tilespec_t spec)
{
    if (!this) return;

    this->data &= ~spec;
}

bool tilespecdata_has(tilespecdata_t* this, tilespec_t spec)
{
    if (!this) return false;

    return (this->data & spec) == spec;
}

bool tilespecdata_any(tilespecdata_t* this, tilespec_t spec)
{
    if (!this) return false;

    return (this->data & spec) != 0;
}
