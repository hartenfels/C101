#ifndef COMPANIES101_COMPANY_H
#define COMPANIES101_COMPANY_H
#include "c101_Vector.h"
#ifdef __cplusplus
extern "C" {
#endif

struct c101_Company {
    char*              name;
    struct c101_Vector subunits;
};


struct c101_Company* c101_newCompany(char*  name,
                                     size_t subunitCount,
                                            ...);

void                c101_freeCompany(struct c101_Company*);

#ifdef __cplusplus
}
#endif
#endif

