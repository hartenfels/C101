#include "c101_Total.h"

static void
c101_total(void* su, void* out)
{
    *(double*) out += c101_totalSubunit((struct c101_Subunit*) su);
}

double
c101_totalCompany(struct c101_Company* c)
{
    double total = 0;
    c101_fold(c101_begin(&c->subunits), c101_end(&c->subunits), &total, c101_total);
    return total;
}

double
c101_totalSubunit(struct c101_Subunit* su)
{
    if (su->isDepartment) {
        double total = 0;
        c101_fold(c101_begin(&su->department.subunits),
                  c101_end(&su->department.subunits), &total, c101_total);
        return total;
    } else {
        return su->employee.salary;
    }
}

