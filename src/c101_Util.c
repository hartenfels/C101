#include "c101_Util.h"

void*
c101_malloc(size_t size)
{
    void* mem = malloc(size);
    if (!mem)
        exit(COMPANIES101_ERROR_MALLOC);
    return mem;
}

void*
c101_calloc(size_t num, size_t size)
{
    void* mem = calloc(num, size);
    if (!mem)
        exit(COMPANIES101_ERROR_CALLOC);
    return mem;
}

void*
c101_realloc(void* ptr, size_t size)
{
    void* mem = realloc(ptr, size);
    if (!mem)
        exit(COMPANIES101_ERROR_REALLOC);
    return mem;
}

char*
c101_strdup(char* str)
{
    size_t len = strlen(str);
    if (len) {
        char* buf = c101_malloc(len + 1);
        strcpy(buf, str);
        return buf;
    }
    return NULL;
}


