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

#include "../gen_fn/lua_reg.h"
#include "lua.h"
#include "pin.H"

extern "C" {
    #include <lua.h>
    #include <lauxlib.h>
    #include <lualib.h>
}
int REG_to_lua(lua_State *L, REG reg) {
    if(!REG_valid(reg)) {
        lua_pushnil(L);
        return 1;
      }
    REG *i = (REG *)lua_newuserdata(L, sizeof(REG));
    *i = reg;
    luaL_getmetatable(L, "pin.Reg");
    lua_setmetatable(L, -2);

  return 1;
}

REG *check_reg (lua_State *L, int pos) {
  void *ud = luaL_checkudata(L, pos, "pin.Reg");
  luaL_argcheck(L, ud != NULL, pos, "`Reg' expected");
  return (REG *)ud;
}

int luaopen_reg (lua_State *L) {
  luaL_newmetatable(L, "pin.Reg");
  luaL_openlib(L, "Reg", reg_lib, 0);
  return 1;
}
int reg_is_half32 (lua_State *L) { 
	REG v1 = lookup_string_to_reg(L,lua_tostring(L,1));
	BOOL r = REG_is_Half32(v1);
	lua_pushboolean(L, r);
	return 1;
}
int reg_is_partialreg (lua_State *L) { 
	REG v1 = lookup_string_to_reg(L,lua_tostring(L,1));
	BOOL r = REG_is_partialreg(v1);
	lua_pushboolean(L, r);
	return 1;
}
int reg_is_lower8 (lua_State *L) { 
	REG v1 = lookup_string_to_reg(L,lua_tostring(L,1));
	BOOL r = REG_is_Lower8(v1);
	lua_pushboolean(L, r);
	return 1;
}
int reg_is_ymm (lua_State *L) { 
	REG v1 = lookup_string_to_reg(L,lua_tostring(L,1));
	BOOL r = REG_is_ymm(v1);
	lua_pushboolean(L, r);
	return 1;
}
int reg_is_pin64 (lua_State *L) { 
	REG v1 = lookup_string_to_reg(L,lua_tostring(L,1));
	BOOL r = REG_is_pin64(v1);
	lua_pushboolean(L, r);
	return 1;
}
int reg_is_gr64 (lua_State *L) { 
	REG v1 = lookup_string_to_reg(L,lua_tostring(L,1));
	BOOL r = REG_is_gr64(v1);
	lua_pushboolean(L, r);
	return 1;
}
int reg_is_xmm (lua_State *L) { 
	REG v1 = lookup_string_to_reg(L,lua_tostring(L,1));
	BOOL r = REG_is_xmm(v1);
	lua_pushboolean(L, r);
	return 1;
}
int reg_is_gr8 (lua_State *L) { 
	REG v1 = lookup_string_to_reg(L,lua_tostring(L,1));
	BOOL r = REG_is_gr8(v1);
	lua_pushboolean(L, r);
	return 1;
}
int reg_is_gr16 (lua_State *L) { 
	REG v1 = lookup_string_to_reg(L,lua_tostring(L,1));
	BOOL r = REG_is_gr16(v1);
	lua_pushboolean(L, r);
	return 1;
}
int reg_is_gr32 (lua_State *L) { 
	REG v1 = lookup_string_to_reg(L,lua_tostring(L,1));
	BOOL r = REG_is_gr32(v1);
	lua_pushboolean(L, r);
	return 1;
}
int reg_is_gr (lua_State *L) { 
	REG v1 = lookup_string_to_reg(L,lua_tostring(L,1));
	BOOL r = REG_is_gr(v1);
	lua_pushboolean(L, r);
	return 1;
}
int reg_is_any_mxcsr (lua_State *L) { 
	REG v1 = lookup_string_to_reg(L,lua_tostring(L,1));
	BOOL r = REG_is_any_mxcsr(v1);
	lua_pushboolean(L, r);
	return 1;
}
int reg_is_mxcsr (lua_State *L) { 
	REG v1 = lookup_string_to_reg(L,lua_tostring(L,1));
	BOOL r = REG_is_mxcsr(v1);
	lua_pushboolean(L, r);
	return 1;
}
int reg_string_short (lua_State *L) { 
	REG v1 = lookup_string_to_reg(L,lua_tostring(L,1));
	string r = REG_StringShort(v1);
	lua_pushstring(L, r.c_str());
	return 1;
}
int reg_is_mm (lua_State *L) { 
	REG v1 = lookup_string_to_reg(L,lua_tostring(L,1));
	BOOL r = REG_is_mm(v1);
	lua_pushboolean(L, r);
	return 1;
}
int reg_is_fr_or_x87 (lua_State *L) { 
	REG v1 = lookup_string_to_reg(L,lua_tostring(L,1));
	BOOL r = REG_is_fr_or_x87(v1);
	lua_pushboolean(L, r);
	return 1;
}
int reg_is_half16 (lua_State *L) { 
	REG v1 = lookup_string_to_reg(L,lua_tostring(L,1));
	BOOL r = REG_is_Half16(v1);
	lua_pushboolean(L, r);
	return 1;
}
int reg_corresponding_ymm_reg (lua_State *L) { 
	REG v1 = lookup_string_to_reg(L,lua_tostring(L,1));
	string r = lookup_reg_to_string(L,REG_corresponding_ymm_reg(v1));
	lua_pushstring(L, r.c_str());
	return 1;
}
int reg_is_fr_for_get_context (lua_State *L) { 
	REG v1 = lookup_string_to_reg(L,lua_tostring(L,1));
	BOOL r = REG_is_fr_for_get_context(v1);
	lua_pushboolean(L, r);
	return 1;
}
int reg_is_fr (lua_State *L) { 
	REG v1 = lookup_string_to_reg(L,lua_tostring(L,1));
	BOOL r = REG_is_fr(v1);
	lua_pushboolean(L, r);
	return 1;
}
int reg_is_upper8 (lua_State *L) { 
	REG v1 = lookup_string_to_reg(L,lua_tostring(L,1));
	BOOL r = REG_is_Upper8(v1);
	lua_pushboolean(L, r);
	return 1;
}
int reg_is_any_x87 (lua_State *L) { 
	REG v1 = lookup_string_to_reg(L,lua_tostring(L,1));
	BOOL r = REG_is_any_x87(v1);
	lua_pushboolean(L, r);
	return 1;
}
int reg_is_seg (lua_State *L) { 
	REG v1 = lookup_string_to_reg(L,lua_tostring(L,1));
	BOOL r = REG_is_seg(v1);
	lua_pushboolean(L, r);
	return 1;
}
int reg_is_br (lua_State *L) { 
	REG v1 = lookup_string_to_reg(L,lua_tostring(L,1));
	BOOL r = REG_is_br(v1);
	lua_pushboolean(L, r);
	return 1;
}
int reg_full_reg_name (lua_State *L) { 
	REG v1 = lookup_string_to_reg(L,lua_tostring(L,1));
	string r = lookup_reg_to_string(L,REG_FullRegName(v1));
	lua_pushstring(L, r.c_str());
	return 1;
}
