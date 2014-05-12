#include "c101_Util.h"
#include <stdio.h>
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

void*
c101_malloc(size_t size)
{
    void* mem = malloc(size);
    if (!mem)
        exit(COMPANIES101_ERROR_MALLOC);
    return mem;
}

void*
c101_calloc(size_t num, size_t size)
{
    void* mem = calloc(num, size);
    if (!mem)
        exit(COMPANIES101_ERROR_CALLOC);
    return mem;
}

void*
c101_realloc(void* ptr, size_t size)
{
    void* mem = realloc(ptr, size);
    if (!mem)
        exit(COMPANIES101_ERROR_REALLOC);
    return mem;
}

char*
c101_strdup(const char* str)
{
    size_t len = strlen(str);
    if (len) {
        char* buf = c101_malloc(len + 1);
        strcpy(buf, str);
        return buf;
    }
    return NULL;
}



lua_State*
c101_initLua(const char* file)
{
    lua_State* lua = luaL_newstate();
    if (!lua)
        c101_luaError(NULL, "Could not create Lua state");
    luaL_openlibs(lua);
    if (luaL_dofile(lua, file))
        c101_luaError(lua, lua_tostring(lua, -1));
    return lua;
}

void
c101_luaError(lua_State* lua, const char* err)
{
    fputs("Parsing Error: ", stderr);
    fputs(err,               stderr);
    fputc('\n',              stderr);
    if (lua)
        lua_close(lua);
    abort();
}


