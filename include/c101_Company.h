#ifndef COMPANIES101_COMPANY_H
#define COMPANIES101_COMPANY_H
#include "c101_Vector.h"
#ifdef __cplusplus
extern "C" {
#endif

/**<!--===============================================================================-->

@file c101_Company.h Class for representing a hierarchical company.


Feature
=======

Implements Feature:Hierarchical_company.


How It Works
============

The implementation of the company is class-like, with a struct containing the name and
a vector of departments and associated operations in this file.


Usage
=====

Use ::c101_newCompany to construct and ::c101_freeCompany to destruct a company.

<!--================================================================================-->*/

struct c101_Company {
    char*              name;
    struct c101_Vector subunits;
};


struct c101_Company* c101_newCompany(const char* name,
                                     size_t      subunitCount,
                                                 ...);


void                c101_freeCompany(struct c101_Company*);


#ifdef __cplusplus
}
#endif
#endif

