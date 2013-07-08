
#ifndef __PINT_LUA_SEC_WRAPPER__
#define __PINT_LUA_SEC_WRAPPER__

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

int SEC_to_lua(lua_State *L, SEC sec);
  SEC *check_sec (lua_State *L, int);
int luaopen_sec (lua_State *L);
int sec_is_executable (lua_State *L) ; 
int sec_img (lua_State *L) ; 
int sec_next (lua_State *L) ; 
int sec_size (lua_State *L) ; 
int sec_name (lua_State *L) ; 
int sec_rtn_head (lua_State *L) ; 
int sec_is_writeable (lua_State *L) ; 
int sec_rtn_tail (lua_State *L) ; 
int sec_address (lua_State *L) ; 
int sec_mapped (lua_State *L) ; 
int sec_prev (lua_State *L) ; 
int sec_is_readable (lua_State *L) ; 
int sec_type (lua_State *L) ; 
const struct luaL_reg sec_lib [] = {
  	{"is_executable",sec_is_executable},
	{"img",sec_img},
	{"next",sec_next},
	{"size",sec_size},
	{"name",sec_name},
	{"rtn_head",sec_rtn_head},
	{"is_writeable",sec_is_writeable},
	{"rtn_tail",sec_rtn_tail},
	{"address",sec_address},
	{"mapped",sec_mapped},
	{"prev",sec_prev},
	{"is_readable",sec_is_readable},
	{"type",sec_type},

  {NULL, NULL}
};

#endif
