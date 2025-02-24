
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
/* Remove spaces on the right of the string */
void trim_spaces(char *buf) {
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

int is_directory(const char *path) {
    struct stat pathBuf;
    if (stat(path, &pathBuf) != 0)
        return 1;
    return S_ISDIR(pathBuf.st_mode);
}

