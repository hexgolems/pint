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

#include "../gen_fn/lua_sym.h"
#include "lua.h"
#include "pin.H"

extern "C" {
    #include <lua.h>
    #include <lauxlib.h>
    #include <lualib.h>
}
int SYM_to_lua(lua_State *L, SYM sym) {
    if(!SYM_Valid(sym)) {
        lua_pushnil(L);
        return 1;
      }
    SYM *i = (SYM *)lua_newuserdata(L, sizeof(SYM));
    *i = sym;
    luaL_getmetatable(L, "pin.Sym");
    lua_setmetatable(L, -2);

  return 1;
}

SYM *check_sym (lua_State *L, int pos) {
  void *ud = luaL_checkudata(L, pos, "pin.Sym");
  luaL_argcheck(L, ud != NULL, pos, "`Sym' expected");
  return (SYM *)ud;
}

int luaopen_sym (lua_State *L) {
  luaL_newmetatable(L, "pin.Sym");
  luaL_openlib(L, "Sym", sym_lib, 0);
  return 1;
}
int sym_next (lua_State *L) { 
	SYM* v1 = check_sym(L,1);
	SYM_to_lua(L, SYM_Next(*v1));
	return 1;
}
int sym_i_func (lua_State *L) { 
	SYM* v1 = check_sym(L,1);
	BOOL r = SYM_IFunc(*v1);
	lua_pushboolean(L, r);
	return 1;
}
int sym_name (lua_State *L) { 
	SYM* v1 = check_sym(L,1);
	string r = SYM_Name(*v1);
	lua_pushstring(L, r.c_str());
	return 1;
}
int sym_prev (lua_State *L) { 
	SYM* v1 = check_sym(L,1);
	SYM_to_lua(L, SYM_Prev(*v1));
	return 1;
}
int sym_address (lua_State *L) { 
	SYM* v1 = check_sym(L,1);
	ADDRINT r = SYM_Address(*v1);
	lua_pushnumber(L, r);
	return 1;
}
int sym_index (lua_State *L) { 
	SYM* v1 = check_sym(L,1);
	UINT32 r = SYM_Index(*v1);
	lua_pushnumber(L, r);
	return 1;
}
int sym_value (lua_State *L) { 
	SYM* v1 = check_sym(L,1);
	ADDRINT r = SYM_Value(*v1);
	lua_pushnumber(L, r);
	return 1;
}
int sym_dynamic (lua_State *L) { 
	SYM* v1 = check_sym(L,1);
	BOOL r = SYM_Dynamic(*v1);
	lua_pushboolean(L, r);
	return 1;
}
