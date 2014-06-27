#include "c101_Unparsing.h"
#include "c101_Subunit.h"
#include "c101_Visit.h"

struct UnparsingData {
    FILE*        out;
    unsigned int depth;
};

static void
indent(unsigned int depth, FILE* out)
{ while (depth--) fputs("    ", out); }

static void
fputsXml(char* str, FILE* out)
{
    for (; *str != '\0'; ++str)
        switch (*str) {
        case '"': fputs("&quot;", out); break;
        case '&': fputs("&amp;",  out); break;
        default : fputc(*str,     out); break;
        }
}

static int
unparseVisitor(enum c101_VisitorType type, void* unit, void* userData)
{
    FILE*         out   =  ((struct UnparsingData*) userData)->out;
    unsigned int* depth = &((struct UnparsingData*) userData)->depth;

    switch (type) {
    case C101_COMPANY:
        indent(*depth, out);
        fputs   ("<company name=\"",                  out);
        fputsXml(((struct c101_Company*) unit)->name, out);
        fputs   ("\">\n",                               out);
        ++*depth;
        break;

    case C101_COMPANY_END:
        indent(--*depth, out);
        fputs("</company>\n", out);
        break;

    case C101_DEPARTMENT:
        indent(*depth, out);
        fputs   ("<department name=\"",                  out);
        fputsXml(((struct c101_Department*) unit)->name, out);
        fputs   ("\">\n",                                  out);
        ++*depth;
        break;

    case C101_DEPARTMENT_END:
        indent(--*depth, out);
        fputs("</department>\n", out);
        break;

    case C101_EMPLOYEE:
        indent(*depth, out);
        {
            struct c101_Employee* e = unit;
            fputs   ("<employee name=\"", out);
            fputsXml(e->name,             out);
            fputs   ("\" address=\"",     out);
            fputsXml(e->address,          out);
            fprintf (out, "\" salary=\"%f\"/>\n", e->salary);
        }
        break;

    default:
        break;
    }
    return 0;
}

int
c101_unparse(struct c101_Company* c, FILE* out)
{
    fputs("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n", out);
    struct UnparsingData data = {out, 0};
    return c101_visitCompany(c, &data, unparseVisitor);
}

