#ifndef COMPANIES101_VECTOR_H
#define COMPANIES101_VECTOR_H
#include <stdlib.h>
#ifdef __cplusplus
extern "C" {
#endif

struct c101_Vector {
    void** data;
    size_t size;
    size_t capacity;
    void (*destroy)(void*);
};


struct c101_Vector c101_newVector  (size_t capacity, void (*destroy)(void*));

void               c101_clearVector(struct c101_Vector* vector);

void               c101_freeVector (struct c101_Vector* vector);


void c101_resize(struct c101_Vector* vector,
                 size_t capacity);

void c101_pushBack(struct c101_Vector* vector,
                   void*               element);


void*  c101_at   (struct c101_Vector* vector,
                  size_t position);

void** c101_begin(struct c101_Vector* vector);

void** c101_end  (struct c101_Vector* vector);

void   c101_map  (void** begin,
                  void** end,
                  void (*callback)(void*));

void   c101_fold (void** begin,
                  void** end,
                  void*  out,
                  void (*callback)(void*, void*));

#ifdef __cplusplus
}
#endif
#endif

