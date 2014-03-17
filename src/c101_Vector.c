#include "c101_Vector.h"
#include "c101_Util.h"
#include <stdlib.h>

struct c101_Vector
c101_newVector(size_t cap, void (*call)(void*))
{
    struct c101_Vector v;
    v.data     = c101_calloc(cap, sizeof(void*));
    v.size     = 0;
    v.capacity = cap;
    v.destroy  = call;
    return v;
}

void c101_clearVector(struct c101_Vector* v)
{
    if (v->destroy)
        c101_map(c101_begin(v), c101_end(v), v->destroy);
}

void c101_freeVector(struct c101_Vector* v)
{
    c101_clearVector(v);
    free(v->data);
}


void
c101_resize(struct c101_Vector* v, size_t cap)
{
    if (cap > v->capacity) {
        v->data     = c101_realloc(v->data, cap * sizeof(void*));
        v->capacity = cap;
    }
}

void
c101_pushBack(struct c101_Vector* v, void* elem)
{
    if (v->size == v->capacity)
        c101_resize(v, v->capacity * 2);
    v->data[v->size++] = elem;
}


void*
c101_at(struct c101_Vector* v, size_t pos)
{
    if (v->size < pos)
        return NULL;
    return v->data[pos];
}

void**
c101_begin(struct c101_Vector* v)
{
    return v->data;
}

void**
c101_end(struct c101_Vector* v)
{
    return v->data + v->size;
}

void
c101_map (void** it, void** end, void (*call)(void*))
{
    while (it != end)
        call(*it++);
}

void c101_fold(void** it, void** end, void* out, void (*call)(void*, void*))
{
    while (it != end)
        call(*it++, out);
}

