#ifndef _KTIME_H
#define _KTIME_H

#include <stdint.h>

void ktime_frame(void);
uint32_t ktime_get(void);
uint32_t ktime_delta(void);

#endif