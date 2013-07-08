
#ifndef __PINT_LUA_RTN_WRAPPER__
#define __PINT_LUA_RTN_WRAPPER__

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

int RTN_to_lua(lua_State *L, RTN rtn);
  RTN *check_rtn (lua_State *L, int);
int luaopen_rtn (lua_State *L);
int rtn_is_safe_for_probed_replacement_ex (lua_State *L) ; 
int rtn_is_safe_for_probed_insertion_ex (lua_State *L) ; 
int rtn_ins_head (lua_State *L) ; 
int rtn_replace (lua_State *L) ; 
int rtn_is_safe_for_probed_insertion (lua_State *L) ; 
int rtn_is_safe_for_probed_replacement (lua_State *L) ; 
int rtn_find_by_address (lua_State *L) ; 
int rtn_sec (lua_State *L) ; 
int rtn_num_ins (lua_State *L) ; 
int rtn_funptr (lua_State *L) ; 
int rtn_ins_head_only (lua_State *L) ; 
int rtn_open (lua_State *L) ; 
int rtn_id (lua_State *L) ; 
int rtn_find_name_by_address (lua_State *L) ; 
int rtn_size (lua_State *L) ; 
int rtn_range (lua_State *L) ; 
int rtn_replace_probed_ex (lua_State *L) ; 
int rtn_sym (lua_State *L) ; 
int rtn_name (lua_State *L) ; 
int rtn_next (lua_State *L) ; 
int rtn_close (lua_State *L) ; 
int rtn_prev (lua_State *L) ; 
int rtn_replace_probed (lua_State *L) ; 
int rtn_create_at (lua_State *L) ; 
int rtn_address (lua_State *L) ; 
int rtn_ins_tail (lua_State *L) ; 
const struct luaL_reg rtn_lib [] = {
  	{"is_safe_for_probed_replacement_ex",rtn_is_safe_for_probed_replacement_ex},
	{"is_safe_for_probed_insertion_ex",rtn_is_safe_for_probed_insertion_ex},
	{"ins_head",rtn_ins_head},
	{"replace",rtn_replace},
	{"is_safe_for_probed_insertion",rtn_is_safe_for_probed_insertion},
	{"is_safe_for_probed_replacement",rtn_is_safe_for_probed_replacement},
	{"find_by_address",rtn_find_by_address},
	{"sec",rtn_sec},
	{"num_ins",rtn_num_ins},
	{"funptr",rtn_funptr},
	{"ins_head_only",rtn_ins_head_only},
	{"open",rtn_open},
	{"id",rtn_id},
	{"find_name_by_address",rtn_find_name_by_address},
	{"size",rtn_size},
	{"range",rtn_range},
	{"replace_probed_ex",rtn_replace_probed_ex},
	{"sym",rtn_sym},
	{"name",rtn_name},
	{"next",rtn_next},
	{"close",rtn_close},
	{"prev",rtn_prev},
	{"replace_probed",rtn_replace_probed},
	{"create_at",rtn_create_at},
	{"address",rtn_address},
	{"ins_tail",rtn_ins_tail},

  {NULL, NULL}
};

#endif
