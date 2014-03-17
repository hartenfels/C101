#include "c101_Print.h"
#include <stdio.h>

static size_t depth;

static void
c101_print(void* v)
{
    for (int i = 0; i < depth; ++i)
        putchar('\t');
    c101_printSubunit(v);
}

void
c101_printCompany(struct c101_Company* c)
{
    printf("%s (%zd Departments)\n", c->name, c->subunits.size);
    ++depth;
    c101_map(c101_begin(&c->subunits), c101_end(&c->subunits), c101_print);
    --depth;
}

void
c101_printSubunit(struct c101_Subunit* su)
{
    if (su->isDepartment) {
        struct c101_Department* d = &su->department;
        printf("%s (%zd Subunits)\n", d->name, d->subunits.size);
        ++depth;
        c101_map(c101_begin(&d->subunits), c101_end(&d->subunits), c101_print);
        --depth;
    } else {
        printf("%s, %s, %g\n", su->employee.name, su->employee.address,
                               su->employee.salary);
    }
}

