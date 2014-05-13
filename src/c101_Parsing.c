#include "c101_Parsing.h"
#include "c101_Company.h"
#include "c101_Subunit.h"
#include "c101_Util.h"
#include "c101_Vector.h"
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

struct ParseData {
    struct c101_Company* company;
    struct c101_Vector   stack;
};

static int
c101_parseCompany(lua_State* lua)
{
    struct ParseData* data = lua_touserdata (lua, 1);
    const char      * name = lua_tostring   (lua, 2);

    data->company = c101_newCompany(name, 0);
    data->stack   = c101_newVector (1, NULL);

    return 0;
}

static int
c101_parseDepartment(lua_State* lua)
{
    struct ParseData* data = lua_touserdata (lua, 1);
    const char      * name = lua_tostring   (lua, 2);

    struct c101_Subunit* subunit = c101_newDepartment(name, 0);
    struct c101_Vector * parent  = data->stack.size
            ? &((struct c101_Subunit*) c101_back(&data->stack))->department.subunits
            : &data->company->subunits;
    c101_pushBack(parent,       subunit);
    c101_pushBack(&data->stack, subunit);

    return 0;
}

static int
c101_parseEmployee(lua_State* lua)
{
    struct ParseData* data    = lua_touserdata (lua, 1);
    const char      * name    = lua_tostring   (lua, 2);
    const char      * address = lua_tostring   (lua, 3);
    double            salary  = lua_tonumber   (lua, 4);

    struct c101_Subunit* subunit = c101_newEmployee(name, address, salary);
    struct c101_Vector * parent  =
              &((struct c101_Subunit*) c101_back(&data->stack))->department.subunits;
    c101_pushBack(parent, subunit);

    return 0;
}

static int
c101_endDepartment(lua_State* lua)
{
    struct ParseData* data = lua_touserdata(lua, 1);
    c101_popBack(&data->stack);
    return 0;
}

struct c101_Company*
c101_parse(const char* file)
{
    lua_State* lua = c101_initLua("parsing.lua");

    lua_pushcfunction(lua,  c101_parseCompany    );
    lua_setglobal    (lua, "c101_parseCompany"   );
    lua_pushcfunction(lua,  c101_parseDepartment );
    lua_setglobal    (lua, "c101_parseDepartment");
    lua_pushcfunction(lua,  c101_parseEmployee   );
    lua_setglobal    (lua, "c101_parseEmployee"  );
    lua_pushcfunction(lua,  c101_endDepartment   );
    lua_setglobal    (lua, "c101_endDepartment"  );

    lua_getglobal(lua, "parseCompany");
    struct ParseData data;
    lua_pushlightuserdata(lua, &data);
    if (luaL_dofile(lua, file))
        c101_luaError(lua, lua_tostring(lua, -1));

    if (lua_pcall(lua, 2, 0, 0))
        c101_luaError(lua, lua_tostring(lua, -1));
    lua_close(lua);

    c101_freeVector(&data.stack);
	return data.company;
}

