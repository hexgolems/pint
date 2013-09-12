#ifndef __PIN_LUA_INSTRUMENTATION_CALLS__
#define __PIN_LUA_INSTRUMENTATION_CALLS__

#include <stdarg.h>
#include "lua_callback.h"
#include "pin.H"

extern "C" {
    #include <lua.h>
    #include <lauxlib.h>
    #include <lualib.h>
}

int add_ins_call(lua_State *L);
int add_bbl_call(lua_State *L);
#endif
