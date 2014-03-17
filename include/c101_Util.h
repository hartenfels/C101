#ifndef COMPANIES101_UTIL_HPP
#define COMPANIES101_UTIL_HPP
#include <stdlib.h>
#include <string.h>
#ifdef __cplusplus
extern "C" {
#endif

enum c101_Errors {
    COMPANIES101_ERROR_MALLOC  = 1 << 0,
    COMPANIES101_ERROR_CALLOC  = 1 << 1,
    COMPANIES101_ERROR_REALLOC = 1 << 2,
    COMPANIES101_ERROR_STRDUP  = 1 << 3,
};


void* c101_malloc (size_t size);

void* c101_calloc (size_t num,
                   size_t size);

void* c101_realloc(void*  ptr,
                   size_t size);

char* c101_strdup (char*  str);

#ifdef __cplusplus
}
#endif
#endif

