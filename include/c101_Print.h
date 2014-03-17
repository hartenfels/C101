#ifndef COMPANIES101_PRINT_H
#define COMPANIES101_PRINT_H
#include "c101_Company.h"
#include "c101_Subunit.h"
#ifdef __cplusplus
extern "C" {
#endif

void c101_printCompany(struct c101_Company* company);

void c101_printSubunit(struct c101_Subunit* subunit);

#ifdef __cplusplus
}
#endif
#endif

