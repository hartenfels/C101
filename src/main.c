#include "c101_Cut.h"
#include "c101_Company.h"
#include "c101_Depth.h"
#include "c101_Median.h"
#include "c101_Parsing.h"
#include "c101_Print.h"
#include "c101_Subunit.h"
#include "c101_Total.h"
#include <stdio.h>

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
    c101_print(company);
    printf("Depth:  %u\n", c101_depth (company));
	printf("Total:  %g\n", c101_total (company));
    printf("Median: %g\n", c101_median(company));
	c101_cut(company);
	printf("Cut:    %g\n", c101_total (company));
    c101_freeCompany(company);

    company = c101_parse("sample.lua");
    c101_print(company);
    c101_freeCompany (company);

    return 0;
}

