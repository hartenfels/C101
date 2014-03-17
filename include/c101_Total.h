#ifndef COMPANIES101_TOTAL_H
#define COMPANIES101_TOTAL_H
#include "c101_Company.h"
#include "c101_Subunit.h"
#ifdef __cplusplus
extern "C" {
#endif

double c101_totalCompany(struct c101_Company* company);

double c101_totalSubunit(struct c101_Subunit* subunit);

#ifdef __cplusplus
}
#endif
#endif

