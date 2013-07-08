
#ifndef __PINT_LUA_OPCODE_WRAPPER__
#define __PINT_LUA_OPCODE_WRAPPER__

extern "C" {
    #include <lua.h>
    #include <lauxlib.h>
    #include <lualib.h>
}

#include "pin.H"
#include "lua_img.h"
#include "lua_ins.h"
#include "lua_sec.h"
#include "lua_rtn.h"
#include "lua_reg.h"
#include "lua_trace.h"
#include "lua_bbl.h"
#include "lua_sym.h"


int luaopen_opcode (lua_State *L);
int opcode_string_short (lua_State *L) ; 
const struct luaL_reg opcode_lib [] = {
  	{"string_short",opcode_string_short},

  {NULL, NULL}
};

#endif
