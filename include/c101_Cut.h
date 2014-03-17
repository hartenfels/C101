#ifndef COMPANIES101_CUT_H
#define COMPANIES101_CUT_H
#include "c101_Company.h"
#include "c101_Subunit.h"
#ifdef __cplusplus
extern "C" {
#endif

void c101_cutCompany(struct c101_Company* company);

void c101_cutSubunit(struct c101_Subunit* subunit);

#ifdef __cplusplus
}
#endif
#endif

