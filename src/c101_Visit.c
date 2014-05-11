#include "c101_Visit.h"

struct VisitorData {
    void(* visitor)(enum c101_VisitorType, void*, void*);
    void * userData;
};

static void
c101_visitSubunit(void* v, void* d)
{
    struct c101_Subunit* subunit = v;
    struct VisitorData * data    = d;
    if (subunit->isDepartment)
        c101_visitDepartment(&subunit->department, data->userData, data->visitor);
    else
        c101_visitEmployee  (&subunit->employee  , data->userData, data->visitor);
}

void
c101_visitCompany(struct c101_Company* c, void* userData,
                  void(*visitor)(enum c101_VisitorType, void*, void*))
{
    visitor(C101_COMPANY,     c, userData);
    struct VisitorData data = {visitor, userData};
    c101_fold(c101_begin(&c->subunits), c101_end(&c->subunits), &data, c101_visitSubunit);
    visitor(C101_COMPANY_END, c, userData);
}

void
c101_visitDepartment(struct c101_Department* d, void* userData,
                     void(*visitor)(enum c101_VisitorType, void*, void*))
{
    visitor(C101_DEPARTMENT,     d, userData);
    struct VisitorData data = {visitor, userData};
    c101_fold(c101_begin(&d->subunits), c101_end(&d->subunits), &data, c101_visitSubunit);
    visitor(C101_DEPARTMENT_END, d, userData);
}

void
c101_visitEmployee(struct c101_Employee* employee, void* userData,
                   void(*visitor)(enum c101_VisitorType, void*, void*))
{ visitor(C101_EMPLOYEE, employee, userData); }

