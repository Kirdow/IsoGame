#ifndef _APP_H
#define _APP_H

#include <stdint.h>
#include <stdbool.h>

typedef struct {
    const char* appTitle;
    uint32_t width;
    uint32_t height;
} app_start_t;

bool app_init(app_start_t* startInfo);
bool app_active(void);
void app_run(void);
void app_close(void);

#endif