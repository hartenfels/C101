#include "c101_Parsing.h"
#include "c101_Company.h"
#include "c101_Subunit.h"
#include "c101_Util.h"
#include <stdlib.h>
#include <stdio.h>
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

static void
c101_warnExcessive(lua_State* lua, int idx)
{
    if (idx < 0)
        --idx;
    lua_pushnil(lua);
    while (lua_next(lua, idx)) {
        lua_pop(lua, 1);
        fputs("Warning: excessive table key \"", stderr);
        fputs(lua_tostring(lua, -1),             stderr);
        fputs("\" ignored\n",                    stderr);
    }
}

static void
c101_popField(lua_State* lua, int idx, const char* key)
{
    if (!lua_checkstack(lua, 2))
        c101_luaError(NULL, "Could not enlarge stack");
    lua_getfield(lua, idx, key);
    lua_pushnil(lua);
    lua_setfield(lua, idx < 0 ? idx - 2 : idx, key);
}

static void
c101_popFields(lua_State* lua, ...)
{
    if (!lua_istable(lua, -1))
        c101_luaError(lua, "Cannot pop fields from something not a table");

    va_list vl;
    va_start(vl, lua);
    int idx = -1;
    const char* key;
    while ((key = va_arg(vl, const char*)))
        c101_popField(lua, idx--, key);
    c101_warnExcessive(lua, idx);
    lua_remove(lua, idx);
}


static struct c101_Subunit*
c101_parseEmployee(lua_State* lua)
{
    c101_popFields(lua, "salary", "address", "name", NULL);

    if (!lua_isstring(lua, -1))
        c101_luaError(lua, "Missing field \"name\" in employee");
    if (!lua_isstring(lua, -2))
        c101_luaError(lua, "Missing field \"address\" in employee");
    if (!lua_isnumber(lua, -3))
        c101_luaError(lua, "Missing field \"salary\" in employee");

    struct c101_Subunit* subunit = c101_newEmployee(lua_tostring(lua, -1),
                                                    lua_tostring(lua, -2),
                                                    lua_tonumber(lua, -3));
    lua_pop(lua, 3);
    return subunit;
}

static void
c101_parseEmployees(lua_State* lua, struct c101_Department* parent)
{
    lua_pushnil(lua);
    while (lua_next(lua, -2))
        c101_pushBack(&parent->subunits, c101_parseEmployee(lua));
}

static void c101_parseSubDepartments(lua_State* lua, struct c101_Department* parent);

static struct c101_Subunit*
c101_parseDepartment(lua_State* lua)
{
    c101_popFields(lua, "departments", "employees", "name", NULL);

    if (!lua_isstring(lua, -1))
        c101_luaError(lua, "Missing field \"name\" in department");
    struct c101_Subunit* subunit = c101_newDepartment(lua_tostring(lua, -1), 0);
    lua_pop(lua, 1);

    if (!lua_isnil(lua, -1))
        c101_parseEmployees(lua, &subunit->department);
    lua_pop(lua, 1);

    if (!lua_isnil(lua, -1))
        c101_parseSubDepartments(lua, &subunit->department);
    lua_pop(lua, 1);

    return subunit;
}

static void
c101_parseDepartments(lua_State* lua, struct c101_Company* company)
{
    lua_pushnil(lua);
    while (lua_next(lua, -2))
        c101_pushBack(&company->subunits, c101_parseDepartment(lua));
}

static void
c101_parseSubDepartments(lua_State* lua, struct c101_Department* parent)
{
    lua_pushnil(lua);
    while (lua_next(lua, -2))
        c101_pushBack(&parent->subunits, c101_parseDepartment(lua));
}

static struct c101_Company*
c101_parseCompany(lua_State* lua)
{
    c101_popFields(lua, "departments", "name", NULL);

    if (!lua_isstring(lua, -1))
        c101_luaError(lua, "Missing field \"name\" in company");
    struct c101_Company* company = c101_newCompany(lua_tostring(lua, -1), 0);
    lua_pop(lua, 1);

    if (!lua_isnil(lua, -1))
        c101_parseDepartments(lua, company);
    lua_pop(lua, 1);

    return company;
}

struct c101_Company*
c101_parse(const char* file)
{
    lua_State          * lua     = c101_initLua		(file);
	struct c101_Company* company = c101_parseCompany(lua );
    lua_close(lua);
	return company;
}

