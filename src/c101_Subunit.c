#include "c101_Subunit.h"
#include "c101_Util.h"
#include <stdarg.h>

struct c101_Subunit*
c101_newEmployee(char* n, char* a, double s)
{
    struct c101_Subunit* e = c101_malloc(sizeof(struct c101_Subunit));
    e->isDepartment        = false;
    e->employee.name       = c101_strdup(n);
    e->employee.address    = c101_strdup(a);
    e->employee.salary     = s;
    return e;
}

struct c101_Subunit*
c101_newDepartment(char* n, size_t count, ...)
{
    struct c101_Subunit* d = c101_malloc(sizeof(struct c101_Subunit));
    d->isDepartment        = true;
    d->department.name     = c101_strdup(n);

    if (count) {
        d->department.subunits = c101_newVector(count, c101_freeSubunit);
        va_list vl;
        va_start(vl, count);
        while (count--)
            c101_pushBack(&d->department.subunits, va_arg(vl, struct c101_Subunit*));
    } else
        d->department.subunits = c101_newVector(1, c101_freeSubunit);

    return d;
}

void
c101_freeSubunit(void* v)
{
    struct c101_Subunit* su = v;
    if (su->isDepartment) {
        free(su->department.name);
        c101_freeVector(&su->department.subunits);
    } else {
        free(su->employee.name);
        free(su->employee.address);
    }
    free(su);
}

