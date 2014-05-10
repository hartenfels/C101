#ifndef COMPANIES101_SUBUNIT_H
#define COMPANIES101_SUBUNIT_H
#include "c101_Vector.h"
#include <stdbool.h>
#ifdef __cplusplus
extern "C" {
#endif

struct c101_Employee {
    char*  name;
    char*  address;
    double salary;
};

struct c101_Department {
    char*              name;
    struct c101_Vector subunits;
};

struct c101_Subunit {
    bool isDepartment;
    union {
        struct c101_Employee   employee;
        struct c101_Department department;
    };
};


struct c101_Subunit* c101_newEmployee  (const char* name,
                                        const char* address,
                                        double      salary);

struct c101_Subunit* c101_newDepartment(const char* name,
                                        size_t      subunitCount,
                                                    ...);

void                 c101_freeSubunit  (void* subunit);

#ifdef __cplusplus
}
#endif
#endif

