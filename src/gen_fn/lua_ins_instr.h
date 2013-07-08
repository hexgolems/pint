#ifndef __PIN_LUA_INSTRUMENT_CALLBACKS__
#define __PIN_LUA_INSTRUMENT_CALLBACKS__

#include <stdarg.h>
#include "lua_callback.h"
#include "pin.H"

extern "C" {
    #include <lua.h>
    #include <lauxlib.h>
    #include <lualib.h>
}

int add_ins_call(lua_State *L);
#endif
