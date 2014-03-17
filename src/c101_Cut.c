#include "c101_Cut.h"

static void
c101_cut(void* su)
{
    c101_cutSubunit((struct c101_Subunit*) su);
}

void
c101_cutCompany(struct c101_Company* c)
{
    c101_map(c101_begin(&c->subunits), c101_end(&c->subunits), c101_cut);
}

void
c101_cutSubunit(struct c101_Subunit* su)
{
    if (su->isDepartment)
        c101_map(c101_begin(&su->department.subunits),
                 c101_end(&su->department.subunits), c101_cut);
    else
        su->employee.salary /= 2;
}

