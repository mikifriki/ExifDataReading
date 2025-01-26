
#include <stdlib.h>
#include <string.h>
/* Remove spaces on the right of the string */
void trim_spaces(char *buf)
{
    char *s = buf-1;
    for (; *buf; ++buf) {
        if (*buf != ' ') s = buf;
    }

    *++s = 0;
}

const char* get_filename(const char *filename) {
    const char *dot = strrchr(filename, '.');
    if(!dot || dot == filename) return NULL;
    return dot + 1;
}