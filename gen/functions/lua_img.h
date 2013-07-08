
#ifndef __PINT_LUA_IMG_WRAPPER__
#define __PINT_LUA_IMG_WRAPPER__

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

int IMG_to_lua(lua_State *L, IMG img);
  IMG *check_img (lua_State *L, int);
int luaopen_img (lua_State *L);
int img_find_by_address (lua_State *L) ; 
int img_is_static_executable (lua_State *L) ; 
int img_sec_head (lua_State *L) ; 
int img_size_mapped (lua_State *L) ; 
int img_entry (lua_State *L) ; 
int img_open (lua_State *L) ; 
int img_id (lua_State *L) ; 
int img_type (lua_State *L) ; 
int img_high_address (lua_State *L) ; 
int img_close (lua_State *L) ; 
int img_low_address (lua_State *L) ; 
int img_load_offset (lua_State *L) ; 
int img_gp (lua_State *L) ; 
int img_start_address (lua_State *L) ; 
int img_name (lua_State *L) ; 
int img_find_img_by_id (lua_State *L) ; 
int img_sec_tail (lua_State *L) ; 
int img_prev (lua_State *L) ; 
int img_is_main_executable (lua_State *L) ; 
int img_next (lua_State *L) ; 
int img_regsym_head (lua_State *L) ; 
const struct luaL_reg img_lib [] = {
  	{"find_by_address",img_find_by_address},
	{"is_static_executable",img_is_static_executable},
	{"sec_head",img_sec_head},
	{"size_mapped",img_size_mapped},
	{"entry",img_entry},
	{"open",img_open},
	{"id",img_id},
	{"type",img_type},
	{"high_address",img_high_address},
	{"close",img_close},
	{"low_address",img_low_address},
	{"load_offset",img_load_offset},
	{"gp",img_gp},
	{"start_address",img_start_address},
	{"name",img_name},
	{"find_img_by_id",img_find_img_by_id},
	{"sec_tail",img_sec_tail},
	{"prev",img_prev},
	{"is_main_executable",img_is_main_executable},
	{"next",img_next},
	{"regsym_head",img_regsym_head},

  {NULL, NULL}
};

#endif
