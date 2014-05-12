#include "c101_Parsing.h"
#include "c101_Subunit.h"
#include "c101_Util.h"
#include "c101_Visit.h"
#include <stdlib.h>
#include <stdio.h>
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

static void
luaSwap(lua_State* lua)
{
    lua_pushvalue(lua, -2);
    lua_pushvalue(lua, -2);
    lua_replace  (lua, -4);
    lua_replace  (lua, -2);
}

static void
unparseVisitor(enum c101_VisitorType type, void* unit, void* userData)
{
    lua_State* lua = userData;
    switch (type) {
    case C101_COMPANY:
        lua_getglobal (lua, "unparseCompany");
        lua_pushstring(lua, ((struct c101_Company*) unit)->name);
        if (lua_pcall(lua, 1, 1, 0))
            abort();
        break;

    case C101_DEPARTMENT:
        lua_getglobal (lua, "unparseDepartment");
        luaSwap       (lua);
        lua_pushstring(lua, ((struct c101_Department*) unit)->name);
        if (lua_pcall(lua, 2, 2, 0))
            abort();
        break;

    case C101_DEPARTMENT_END:
        lua_pop(lua, 1);
        break;

    case C101_EMPLOYEE:
        lua_getglobal(lua, "unparseEmployee");
        luaSwap      (lua);
        {
            struct c101_Employee* e = unit;
            lua_pushstring(lua, e->name);
            lua_pushstring(lua, e->address);
            lua_pushnumber(lua, e->salary);
        }
        if (lua_pcall(lua, 4, 1, 0))
            abort();
        break;

    default:
        break;
    }
}


void
c101_unparse(struct c101_Company* c, FILE* luaOut, FILE* jsonOut)
{
    lua_State* lua = c101_initLua("unparsing.lua");
    c101_visitCompany(c, lua, unparseVisitor);

    if (luaOut) {
        lua_getglobal(lua, "dumpLua");
        luaSwap      (lua);
        if (lua_pcall(lua, 1, 2, 0))
            abort();
        if (fputs(lua_tostring(lua, -1), luaOut) == EOF)
            perror("Error writing Lua output");
        lua_pop(lua, 1);
    }

    if (jsonOut) {
        lua_getglobal(lua, "dumpJson");
        luaSwap      (lua);
        if (lua_pcall(lua, 1, 2, 0))
            abort();
        if (fputs(lua_tostring(lua, -1), jsonOut) == EOF)
            perror("Error writing JSON output");
        lua_pop(lua, 1);
    }

    lua_close(lua);
}

