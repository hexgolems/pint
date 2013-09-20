#include "lua_img.h"
#include "lua_ins.h"
#include "lua_sec.h"
#include "lua_rtn.h"

#include "../enums/enum_sec_type.h"

#include "../gen_fn/lua_sec.h"
#include "lua_class.h"
#include "pin.H"

extern "C" {
    #include <lua.h>
    #include <lauxlib.h>
    #include <lualib.h>
}
int SEC_to_lua(lua_State *L, SEC sec) {
    if(!SEC_Valid(sec)) {
        lua_pushnil(L);
        return 1;
      }
    SEC *i = (SEC *)lua_newuserdata(L, sizeof(SEC));
    *i = sec;
    luaL_getmetatable(L, "pin.Sec");
    lua_setmetatable(L, -2);

  return 1;
}

SEC *check_sec (lua_State *L, int pos) {
  void *ud = luaL_checkudata(L, pos, "pin.Sec");
  luaL_argcheck(L, ud != NULL, pos, "`Sec' expected");
  return (SEC *)ud;
}

int luaopen_sec (lua_State *L) {

      luaL_newmetatable(L, "pin.Sec");
      lua_pushstring(L, "__index");
      lua_pushvalue(L, -2);  /* pushes the metatable */
      lua_settable(L, -3);  /* metatable.__index = metatable */
      luaL_openlib(L, NULL, sec_lib_m, 0);
      luaL_openlib(L, "Sec", sec_lib, 0);
      return 1;
}
int sec_is_executable (lua_State *L) {
  SEC* v1 = check_sec(L,1);
  BOOL r = SEC_IsExecutable(*v1);
  lua_pushboolean(L, r);
  return 1;
}
int sec_img (lua_State *L) {
  SEC* v1 = check_sec(L,1);
  IMG_to_lua(L, SEC_Img(*v1));
  return 1;
}
int sec_next (lua_State *L) {
  SEC* v1 = check_sec(L,1);
  SEC_to_lua(L, SEC_Next(*v1));
  return 1;
}
int sec_size (lua_State *L) {
  SEC* v1 = check_sec(L,1);
  USIZE r = SEC_Size(*v1);
  lua_pushnumber(L, r);
  return 1;
}
int sec_name (lua_State *L) {
  SEC* v1 = check_sec(L,1);
  string r = SEC_Name(*v1);
  lua_pushstring(L, r.c_str());
  return 1;
}
int sec_rtn_head (lua_State *L) {
  SEC* v1 = check_sec(L,1);
  RTN_to_lua(L, SEC_RtnHead(*v1));
  return 1;
}
int sec_is_writeable (lua_State *L) {
  SEC* v1 = check_sec(L,1);
  BOOL r = SEC_IsWriteable(*v1);
  lua_pushboolean(L, r);
  return 1;
}
int sec_rtn_tail (lua_State *L) {
  SEC* v1 = check_sec(L,1);
  RTN_to_lua(L, SEC_RtnTail(*v1));
  return 1;
}
int sec_address (lua_State *L) {
  SEC* v1 = check_sec(L,1);
  ADDRINT r = SEC_Address(*v1);
  lua_pushnumber(L, r);
  return 1;
}
int sec_mapped (lua_State *L) {
  SEC* v1 = check_sec(L,1);
  BOOL r = SEC_Mapped(*v1);
  lua_pushboolean(L, r);
  return 1;
}
int sec_prev (lua_State *L) {
  SEC* v1 = check_sec(L,1);
  SEC_to_lua(L, SEC_Prev(*v1));
  return 1;
}
int sec_is_readable (lua_State *L) {
  SEC* v1 = check_sec(L,1);
  BOOL r = SEC_IsReadable(*v1);
  lua_pushboolean(L, r);
  return 1;
}
int sec_type (lua_State *L) {
  SEC* v1 = check_sec(L,1);
  string r = lookup_sec_type_to_string(L,SEC_Type(*v1));
  lua_pushstring(L, r.c_str());
  return 1;
}
