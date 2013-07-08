
#ifndef __PINT_LUA_PIN_WRAPPER__
#define __PINT_LUA_PIN_WRAPPER__

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


int luaopen_pin (lua_State *L);
int pin_set_syntax_x_e_d (lua_State *L) ; 
int pin_set_syntax_intel (lua_State *L) ; 
int pin_set_syntax_a_t_t (lua_State *L) ; 
int pin_undecorate_symbol_name (lua_State *L) ; 
int pin_claim_tool_register (lua_State *L) ; 
const struct luaL_reg pin_lib [] = {
  	{"set_syntax_x_e_d",pin_set_syntax_x_e_d},
	{"set_syntax_intel",pin_set_syntax_intel},
	{"set_syntax_a_t_t",pin_set_syntax_a_t_t},
	{"undecorate_symbol_name",pin_undecorate_symbol_name},
	{"claim_tool_register",pin_claim_tool_register},

  {NULL, NULL}
};

#endif
