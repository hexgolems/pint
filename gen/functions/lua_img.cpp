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

#include "../gen_fn/lua_img.h"
#include "lua.h"
#include "pin.H"

extern "C" {
    #include <lua.h>
    #include <lauxlib.h>
    #include <lualib.h>
}
int IMG_to_lua(lua_State *L, IMG img) {
    if(!IMG_Valid(img)) {
        lua_pushnil(L);
        return 1;
      }
    IMG *i = (IMG *)lua_newuserdata(L, sizeof(IMG));
    *i = img;
    luaL_getmetatable(L, "pin.Img");
    lua_setmetatable(L, -2);

  return 1;
}

IMG *check_img (lua_State *L, int pos) {
  void *ud = luaL_checkudata(L, pos, "pin.Img");
  luaL_argcheck(L, ud != NULL, pos, "`Img' expected");
  return (IMG *)ud;
}

int luaopen_img (lua_State *L) {
  luaL_newmetatable(L, "pin.Img");
  luaL_openlib(L, "Img", img_lib, 0);
  return 1;
}
int img_find_by_address (lua_State *L) { 
	ADDRINT v1 = lua_tonumber(L,1);
	IMG_to_lua(L, IMG_FindByAddress(v1));
	return 1;
}
int img_is_static_executable (lua_State *L) { 
	IMG* v1 = check_img(L,1);
	BOOL r = IMG_IsStaticExecutable(*v1);
	lua_pushboolean(L, r);
	return 1;
}
int img_sec_head (lua_State *L) { 
	IMG* v1 = check_img(L,1);
	SEC_to_lua(L, IMG_SecHead(*v1));
	return 1;
}
int img_size_mapped (lua_State *L) { 
	IMG* v1 = check_img(L,1);
	USIZE r = IMG_SizeMapped(*v1);
	lua_pushnumber(L, r);
	return 1;
}
int img_entry (lua_State *L) { 
	IMG* v1 = check_img(L,1);
	ADDRINT r = IMG_Entry(*v1);
	lua_pushnumber(L, r);
	return 1;
}
int img_open (lua_State *L) { 
	string v1 = lua_tostring(L,1);
	IMG_to_lua(L, IMG_Open(v1));
	return 1;
}
int img_id (lua_State *L) { 
	IMG* v1 = check_img(L,1);
	UINT32 r = IMG_Id(*v1);
	lua_pushnumber(L, r);
	return 1;
}
int img_type (lua_State *L) { 
	IMG* v1 = check_img(L,1);
	string r = lookup_img_type_to_string(L,IMG_Type(*v1));
	lua_pushstring(L, r.c_str());
	return 1;
}
int img_high_address (lua_State *L) { 
	IMG* v1 = check_img(L,1);
	ADDRINT r = IMG_HighAddress(*v1);
	lua_pushnumber(L, r);
	return 1;
}
int img_close (lua_State *L) { 
	IMG* v1 = check_img(L,1);
	 IMG_Close(*v1);
	return 0;
}
int img_low_address (lua_State *L) { 
	IMG* v1 = check_img(L,1);
	ADDRINT r = IMG_LowAddress(*v1);
	lua_pushnumber(L, r);
	return 1;
}
int img_load_offset (lua_State *L) { 
	IMG* v1 = check_img(L,1);
	ADDRINT r = IMG_LoadOffset(*v1);
	lua_pushnumber(L, r);
	return 1;
}
int img_gp (lua_State *L) { 
	IMG* v1 = check_img(L,1);
	ADDRINT r = IMG_Gp(*v1);
	lua_pushnumber(L, r);
	return 1;
}
int img_start_address (lua_State *L) { 
	IMG* v1 = check_img(L,1);
	ADDRINT r = IMG_StartAddress(*v1);
	lua_pushnumber(L, r);
	return 1;
}
int img_name (lua_State *L) { 
	IMG* v1 = check_img(L,1);
	string r = IMG_Name(*v1);
	lua_pushstring(L, r.c_str());
	return 1;
}
int img_find_img_by_id (lua_State *L) { 
	UINT32 v1 = lua_tonumber(L,1);
	IMG_to_lua(L, IMG_FindImgById(v1));
	return 1;
}
int img_sec_tail (lua_State *L) { 
	IMG* v1 = check_img(L,1);
	SEC_to_lua(L, IMG_SecTail(*v1));
	return 1;
}
int img_prev (lua_State *L) { 
	IMG* v1 = check_img(L,1);
	IMG_to_lua(L, IMG_Prev(*v1));
	return 1;
}
int img_is_main_executable (lua_State *L) { 
	IMG* v1 = check_img(L,1);
	BOOL r = IMG_IsMainExecutable(*v1);
	lua_pushboolean(L, r);
	return 1;
}
int img_next (lua_State *L) { 
	IMG* v1 = check_img(L,1);
	IMG_to_lua(L, IMG_Next(*v1));
	return 1;
}
int img_regsym_head (lua_State *L) { 
	IMG* v1 = check_img(L,1);
	SYM_to_lua(L, IMG_RegsymHead(*v1));
	return 1;
}
