
#ifndef __PINT_LUA_SYM_WRAPPER__
#define __PINT_LUA_SYM_WRAPPER__

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

int SYM_to_lua(lua_State *L, SYM sym);
  SYM *check_sym (lua_State *L, int);
int luaopen_sym (lua_State *L);
int sym_next (lua_State *L) ; 
int sym_i_func (lua_State *L) ; 
int sym_name (lua_State *L) ; 
int sym_prev (lua_State *L) ; 
int sym_address (lua_State *L) ; 
int sym_index (lua_State *L) ; 
int sym_value (lua_State *L) ; 
int sym_dynamic (lua_State *L) ; 
const struct luaL_reg sym_lib [] = {
  	{"next",sym_next},
	{"i_func",sym_i_func},
	{"name",sym_name},
	{"prev",sym_prev},
	{"address",sym_address},
	{"index",sym_index},
	{"value",sym_value},
	{"dynamic",sym_dynamic},

  {NULL, NULL}
};

#endif
