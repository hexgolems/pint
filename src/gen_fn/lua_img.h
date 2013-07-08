
#ifndef __PINT_LUA_IMG_WRAPPER__
#define __PINT_LUA_IMG_WRAPPER__

extern "C" {
    #include <lua.h>
    #include <lauxlib.h>
    #include <lualib.h>
}

#include "pin.H"

int IMG_to_lua(lua_State *L, IMG img);
  IMG *check_img (lua_State *L, int);
int luaopen_img (lua_State *L);
void img_callback(lua_State *L, IMG img);
int img_next (lua_State *L) ;
int img_prev (lua_State *L) ;
int img_sec_head (lua_State *L) ;
int img_sec_tail (lua_State *L) ;
int img_regsym_head (lua_State *L) ;
int img_entry (lua_State *L) ;
int img_name (lua_State *L) ;
int img_gp (lua_State *L) ;
int img_load_offset (lua_State *L) ;
int img_low_address (lua_State *L) ;
int img_high_address (lua_State *L) ;
int img_start_address (lua_State *L) ;
int img_size_mapped (lua_State *L) ;
int img_type (lua_State *L) ;
int img_is_main_executable (lua_State *L) ;
int img_is_static_executable (lua_State *L) ;
int img_id (lua_State *L) ;
int img_find_img_by_id (lua_State *L) ;
int img_find_by_address (lua_State *L) ;
int img_open (lua_State *L) ;
int img_close (lua_State *L) ;

const struct luaL_reg img_lib_m [] = {
  {"next",img_next},
  {"prev",img_prev},
  {"sec_head",img_sec_head},
  {"sec_tail",img_sec_tail},
  {"regsym_head",img_regsym_head},
  {"entry",img_entry},
  {"name",img_name},
  {"gp",img_gp},
  {"load_offset",img_load_offset},
  {"low_address",img_low_address},
  {"high_address",img_high_address},
  {"start_address",img_start_address},
  {"size_mapped",img_size_mapped},
  {"type",img_type},
  {"is_main_executable",img_is_main_executable},
  {"is_static_executable",img_is_static_executable},
  {"id",img_id},
  {"open",img_open},
  {"close",img_close},

  {NULL, NULL}
};


const struct luaL_reg img_lib [] = {
  {"next",img_next},
  {"prev",img_prev},
  {"sec_head",img_sec_head},
  {"sec_tail",img_sec_tail},
  {"regsym_head",img_regsym_head},
  {"entry",img_entry},
  {"name",img_name},
  {"gp",img_gp},
  {"load_offset",img_load_offset},
  {"low_address",img_low_address},
  {"high_address",img_high_address},
  {"start_address",img_start_address},
  {"size_mapped",img_size_mapped},
  {"type",img_type},
  {"is_main_executable",img_is_main_executable},
  {"is_static_executable",img_is_static_executable},
  {"id",img_id},
  {"find_img_by_id",img_find_img_by_id},
  {"find_by_address",img_find_by_address},
  {"open",img_open},
  {"close",img_close},

  {NULL, NULL}
};

#endif
