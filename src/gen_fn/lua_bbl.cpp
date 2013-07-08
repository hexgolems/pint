#include "lua_img.h"
#include "lua_ins.h"
#include "lua_sec.h"
#include "lua_rtn.h"
#include "lua_reg.h"
#include "lua_trace.h"
#include "lua_bbl.h"
#include "lua_sym.h"
#include "../enums/enum_img_type.h"
#include "../enums/enum_memory_type.h"
#include "../enums/enum_syscall_standard.h"
#include "../enums/enum_predicate_ia32.h"
#include "../enums/enum_ins_prop_ipf.h"
#include "../enums/enum_sec_type.h"
#include "../enums/enum_probe_mode.h"
#include "../enums/enum_reg.h"
#include "../enums/enum_reg.h"
#include "../enums/enum_regname.h"
#include "../enums/enum_undecoration.h"
#include "../enums/enum_ipoint.h"
#include "../enums/enum_call_order.h"
#include "../enums/enum_iarg_type.h"

#include "../gen_fn/lua_bbl.h"
#include "lua.h"
#include "pin.H"

extern "C" {
    #include <lua.h>
    #include <lauxlib.h>
    #include <lualib.h>
}
int BBL_to_lua(lua_State *L, BBL bbl) {
    if(!BBL_Valid(bbl)) {
        lua_pushnil(L);
        return 1;
      }
    BBL *i = (BBL *)lua_newuserdata(L, sizeof(BBL));
    *i = bbl;
    luaL_getmetatable(L, "pin.Bbl");
    lua_setmetatable(L, -2);

  return 1;
}

BBL *check_bbl (lua_State *L, int pos) {
  void *ud = luaL_checkudata(L, pos, "pin.Bbl");
  luaL_argcheck(L, ud != NULL, pos, "`Bbl' expected");
  return (BBL *)ud;
}

int luaopen_bbl (lua_State *L) {
  luaL_newmetatable(L, "pin.Bbl");
  luaL_openlib(L, "Bbl", bbl_lib, 0);
  return 1;
}
int bbl_has_fall_through (lua_State *L) { 
	BBL* v1 = check_bbl(L,1);
	BOOL r = BBL_HasFallThrough(*v1);
	lua_pushboolean(L, r);
	return 1;
}
int bbl_next (lua_State *L) { 
	BBL* v1 = check_bbl(L,1);
	BBL_to_lua(L, BBL_Next(*v1));
	return 1;
}
int bbl_size (lua_State *L) { 
	BBL* v1 = check_bbl(L,1);
	USIZE r = BBL_Size(*v1);
	lua_pushnumber(L, r);
	return 1;
}
int bbl_ins_tail (lua_State *L) { 
	BBL* v1 = check_bbl(L,1);
	INS_to_lua(L, BBL_InsTail(*v1));
	return 1;
}
int bbl_address (lua_State *L) { 
	BBL* v1 = check_bbl(L,1);
	ADDRINT r = BBL_Address(*v1);
	lua_pushnumber(L, r);
	return 1;
}
int bbl_original (lua_State *L) { 
	BBL* v1 = check_bbl(L,1);
	BOOL r = BBL_Original(*v1);
	lua_pushboolean(L, r);
	return 1;
}
int bbl_num_ins (lua_State *L) { 
	BBL* v1 = check_bbl(L,1);
	UINT32 r = BBL_NumIns(*v1);
	lua_pushnumber(L, r);
	return 1;
}
int bbl_move_all_attributes (lua_State *L) { 
	BBL* v1 = check_bbl(L,1);
	BBL* v2 = check_bbl(L,2);
	 BBL_MoveAllAttributes(*v1,*v2);
	return 0;
}
int bbl_ins_head (lua_State *L) { 
	BBL* v1 = check_bbl(L,1);
	INS_to_lua(L, BBL_InsHead(*v1));
	return 1;
}
int bbl_prev (lua_State *L) { 
	BBL* v1 = check_bbl(L,1);
	BBL_to_lua(L, BBL_Prev(*v1));
	return 1;
}
