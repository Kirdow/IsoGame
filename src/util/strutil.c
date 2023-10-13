#include "strutil.h"

#include <string.h>
#include <stdlib.h>

char* str_reverse_lines(const char* text)
{
    size_t len = strlen(text);
    char* result = (char*)malloc((len + 1) * sizeof(char));
    for (size_t i = 0; i <= len; i++) result[i] = text[i];
    result[len] = '\0';

    char* ptr = result;
    char* pos = strchr(ptr, '\n');
    while (ptr)
    {
        char* end = pos ? pos : (result + len);
        size_t plen = (int)(end - ptr);
        for (size_t i = 0; i < (size_t)(end - ptr) / 2; i++)
        {
            char tmp = ptr[i];
            ptr[i] = ptr[plen - i - 1];
            ptr[plen - i - 1] = tmp;
        }

        if (pos == NULL) ptr = NULL;
        else
        {
            ptr = pos + 1;
            pos = strchr(ptr, '\n');
        }
    }

    return result;
}