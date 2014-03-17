#include "c101_Cut.h"
#include "c101_Company.h"
#include "c101_Subunit.h"
#include "c101_Total.h"
#include <stdio.h>

static int depth;

static void
printSubunit(void* v)
{
    struct c101_Subunit* su = v;
    for (int i = 0; i < depth; ++i)
        putchar('\t');
    if (su->isDepartment) {
        struct c101_Department* d = &su->department;
        printf("%s (%zd Subunits)\n", d->name, d->subunits.size);
        ++depth;
        c101_map(c101_begin(&d->subunits), c101_end(&d->subunits), printSubunit);
        --depth;
    } else {
        printf("%s, %s, %g\n", su->employee.name, su->employee.address,
                               su->employee.salary);
    }
}

static void
printCompany(struct c101_Company* c)
{
    printf("%s (%zd Departments)\n", c->name, c->subunits.size);
    ++depth;
    c101_map(c101_begin(&c->subunits), c101_end(&c->subunits), printSubunit);
    --depth;
}

int
main(void)
{
    struct c101_Company* company =
            c101_newCompany("Acme Corporation", 2,
                c101_newDepartment("Research", 3,
                    c101_newEmployee("Craig", "Redmond", 123456),
                    c101_newEmployee("Erik" , "Utrecht", 12345 ),
                    c101_newEmployee("Ralf" , "Koblenz", 1234  )
                ),
                c101_newDepartment("Development", 2,
                    c101_newEmployee  ("Ray", "Redmond", 234567),
                    c101_newDepartment("Dev1", 2,
                        c101_newEmployee  ("Klaus", "Boston", 23456),
                        c101_newDepartment("Dev1.1", 2,
                            c101_newEmployee("Karl", "Riga"     , 2345),
                            c101_newEmployee("Joe" , "Wifi City", 2344)
                        )
                    )
                )
            );
    printCompany(company);
	printf("Total: %g\n", c101_totalCompany(company));
	c101_cutCompany(company);
	printf("Cut:   %g\n", c101_totalCompany(company));
    c101_freeCompany(company);
    return 0;
}

