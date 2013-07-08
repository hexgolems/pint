#ifndef __PINT_LUA_TYPED_CALLBACK_WRAPPER__
#define __PINT_LUA_TYPED_CALLBACK_WRAPPER__

extern "C" {
    #include <lua.h>
    #include <lauxlib.h>
    #include <lualib.h>
}

#include "pin.H"
#include "lua_callback.h"

int CALLBACK_to_lua(lua_State *L, LUA_CALLBACK* cb);
LUA_CALLBACK *check_typed_callback (lua_State *L, int);
int luaopen_typed_callback (lua_State *L);

int instrument_lua_callback(lua_State *L);
void instrument_callback(LUA_CALLBACK* cb, ...);

IARGLIST get_instrument_arglist(lua_State *L, int offset);
int create_typed_callback(lua_State *L);

const struct luaL_reg typed_callback_lib [] = {
  {"new",create_typed_callback},
  {NULL, NULL}
};

#endif
