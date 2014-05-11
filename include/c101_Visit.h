#ifndef COMPANIES101_VISIT_H
#define COMPANIES101_VISIT_H
#include "c101_Company.h"
#include "c101_Subunit.h"
#ifdef __cplusplus
extern "C" {
#endif

enum c101_VisitorType {
    C101_COMPANY,
    C101_COMPANY_END,
    C101_DEPARTMENT,
    C101_DEPARTMENT_END,
    C101_EMPLOYEE
};

void c101_visitCompany   (struct c101_Company   * company,
                          void                  * userData,
                          void (*visitor)(enum c101_VisitorType, void*, void*));

void c101_visitDepartment(struct c101_Department* department,
                          void                  * userData,
                          void (*visitor)(enum c101_VisitorType, void*, void*));

void c101_visitEmployee  (struct c101_Employee  * employee,
                          void                  * userData,
                          void (*visitor)(enum c101_VisitorType, void*, void*));


#ifdef __cplusplus
}
#endif
#endif

