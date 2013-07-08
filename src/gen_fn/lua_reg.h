
#ifndef __PINT_LUA_REG_WRAPPER__
#define __PINT_LUA_REG_WRAPPER__

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

int REG_to_lua(lua_State *L, REG reg);
  REG *check_reg (lua_State *L, int);
int luaopen_reg (lua_State *L);
int reg_is_half32 (lua_State *L) ; 
int reg_is_partialreg (lua_State *L) ; 
int reg_is_lower8 (lua_State *L) ; 
int reg_is_ymm (lua_State *L) ; 
int reg_is_pin64 (lua_State *L) ; 
int reg_is_gr64 (lua_State *L) ; 
int reg_is_xmm (lua_State *L) ; 
int reg_is_gr8 (lua_State *L) ; 
int reg_is_gr16 (lua_State *L) ; 
int reg_is_gr32 (lua_State *L) ; 
int reg_is_gr (lua_State *L) ; 
int reg_is_any_mxcsr (lua_State *L) ; 
int reg_is_mxcsr (lua_State *L) ; 
int reg_string_short (lua_State *L) ; 
int reg_is_mm (lua_State *L) ; 
int reg_is_fr_or_x87 (lua_State *L) ; 
int reg_is_half16 (lua_State *L) ; 
int reg_corresponding_ymm_reg (lua_State *L) ; 
int reg_is_fr_for_get_context (lua_State *L) ; 
int reg_is_fr (lua_State *L) ; 
int reg_is_upper8 (lua_State *L) ; 
int reg_is_any_x87 (lua_State *L) ; 
int reg_is_seg (lua_State *L) ; 
int reg_is_br (lua_State *L) ; 
int reg_full_reg_name (lua_State *L) ; 
const struct luaL_reg reg_lib [] = {
  	{"is_half32",reg_is_half32},
	{"is_partialreg",reg_is_partialreg},
	{"is_lower8",reg_is_lower8},
	{"is_ymm",reg_is_ymm},
	{"is_pin64",reg_is_pin64},
	{"is_gr64",reg_is_gr64},
	{"is_xmm",reg_is_xmm},
	{"is_gr8",reg_is_gr8},
	{"is_gr16",reg_is_gr16},
	{"is_gr32",reg_is_gr32},
	{"is_gr",reg_is_gr},
	{"is_any_mxcsr",reg_is_any_mxcsr},
	{"is_mxcsr",reg_is_mxcsr},
	{"string_short",reg_string_short},
	{"is_mm",reg_is_mm},
	{"is_fr_or_x87",reg_is_fr_or_x87},
	{"is_half16",reg_is_half16},
	{"corresponding_ymm_reg",reg_corresponding_ymm_reg},
	{"is_fr_for_get_context",reg_is_fr_for_get_context},
	{"is_fr",reg_is_fr},
	{"is_upper8",reg_is_upper8},
	{"is_any_x87",reg_is_any_x87},
	{"is_seg",reg_is_seg},
	{"is_br",reg_is_br},
	{"full_reg_name",reg_full_reg_name},

  {NULL, NULL}
};

#endif
