#include "lua_img.h"
#include "lua_sec.h"
#include "lua_sym.h"
#include "../enums/enum_img_type.h"

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
  lua_pushstring(L, "__index");
  lua_pushvalue(L, -2);  /* pushes the metatable */
  lua_settable(L, -3);  /* metatable.__index = metatable */
  luaL_openlib(L, NULL, img_lib_m, 0);
  luaL_openlib(L, "Img", img_lib, 0);
  return 1;
}

void img_callback(lua_State *L, IMG img){
  lua_getglobal(L, "img_callback");
  if(!lua_isfunction(L,-1)) { lua_pop(L,1); return; }

  IMG_to_lua(L, img);
  /* do the call (1 argument, 0 result) */
  if (lua_pcall(L, 1, 0, 0) != 0) {
      printf("error running function `img_callback': %s\n",lua_tostring(L, -1));
      return;
  }
}

int img_next (lua_State *L) {
  IMG* v1 = check_img(L,1);
  IMG_to_lua(L, IMG_Next(*v1));
  return 1;
}
int img_prev (lua_State *L) {
  IMG* v1 = check_img(L,1);
  IMG_to_lua(L, IMG_Prev(*v1));
  return 1;
}
int img_sec_head (lua_State *L) {
  IMG* v1 = check_img(L,1);
  SEC_to_lua(L, IMG_SecHead(*v1));
  return 1;
}
int img_sec_tail (lua_State *L) {
  IMG* v1 = check_img(L,1);
  SEC_to_lua(L, IMG_SecTail(*v1));
  return 1;
}
int img_regsym_head (lua_State *L) {
  IMG* v1 = check_img(L,1);
  SYM_to_lua(L, IMG_RegsymHead(*v1));
  return 1;
}
int img_entry (lua_State *L) {
  IMG* v1 = check_img(L,1);
  ADDRINT r = IMG_Entry(*v1);
  lua_pushnumber(L, r);
  return 1;
}
int img_name (lua_State *L) {
  IMG* v1 = check_img(L,1);
  string r = IMG_Name(*v1);
  lua_pushstring(L, r.c_str());
  return 1;
}
int img_gp (lua_State *L) {
  IMG* v1 = check_img(L,1);
  ADDRINT r = IMG_Gp(*v1);
  lua_pushnumber(L, r);
  return 1;
}
int img_load_offset (lua_State *L) {
  IMG* v1 = check_img(L,1);
  ADDRINT r = IMG_LoadOffset(*v1);
  lua_pushnumber(L, r);
  return 1;
}
int img_low_address (lua_State *L) {
  IMG* v1 = check_img(L,1);
  ADDRINT r = IMG_LowAddress(*v1);
  lua_pushnumber(L, r);
  return 1;
}
int img_high_address (lua_State *L) {
  IMG* v1 = check_img(L,1);
  ADDRINT r = IMG_HighAddress(*v1);
  lua_pushnumber(L, r);
  return 1;
}
int img_start_address (lua_State *L) {
  IMG* v1 = check_img(L,1);
  ADDRINT r = IMG_StartAddress(*v1);
  lua_pushnumber(L, r);
  return 1;
}
int img_size_mapped (lua_State *L) {
  IMG* v1 = check_img(L,1);
  USIZE r = IMG_SizeMapped(*v1);
  lua_pushnumber(L, r);
  return 1;
}
int img_type (lua_State *L) {
  IMG* v1 = check_img(L,1);
  string r = lookup_img_type_to_string(L,IMG_Type(*v1));
  lua_pushstring(L, r.c_str());
  return 1;
}
int img_is_main_executable (lua_State *L) {
  IMG* v1 = check_img(L,1);
  BOOL r = IMG_IsMainExecutable(*v1);
  lua_pushboolean(L, r);
  return 1;
}
int img_is_static_executable (lua_State *L) {
  IMG* v1 = check_img(L,1);
  BOOL r = IMG_IsStaticExecutable(*v1);
  lua_pushboolean(L, r);
  return 1;
}
int img_id (lua_State *L) {
  IMG* v1 = check_img(L,1);
  UINT32 r = IMG_Id(*v1);
  lua_pushnumber(L, r);
  return 1;
}
int img_find_img_by_id (lua_State *L) {
  UINT32 v1 = lua_tonumber(L,1);
  IMG_to_lua(L, IMG_FindImgById(v1));
  return 1;
}
int img_find_by_address (lua_State *L) {
  ADDRINT v1 = lua_tonumber(L,1);
  PIN_LockClient();
  IMG_to_lua(L, IMG_FindByAddress(v1));
  PIN_UnlockClient();
  return 1;
}
int img_open (lua_State *L) {
  string v1 = lua_tostring(L,1);
  IMG_to_lua(L, IMG_Open(v1));
  return 1;
}
int img_close (lua_State *L) {
  IMG* v1 = check_img(L,1);
   IMG_Close(*v1);
  return 0;
}
