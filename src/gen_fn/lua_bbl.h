
#ifndef __PINT_LUA_BBL_WRAPPER__
#define __PINT_LUA_BBL_WRAPPER__

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

int BBL_to_lua(lua_State *L, BBL bbl);
  BBL *check_bbl (lua_State *L, int);
int luaopen_bbl (lua_State *L);
int bbl_has_fall_through (lua_State *L) ;
int bbl_next (lua_State *L) ;
int bbl_size (lua_State *L) ;
int bbl_ins_tail (lua_State *L) ;
int bbl_address (lua_State *L) ;
int bbl_original (lua_State *L) ;
int bbl_num_ins (lua_State *L) ;
int bbl_move_all_attributes (lua_State *L) ;
int bbl_ins_head (lua_State *L) ;
int bbl_prev (lua_State *L) ;
const struct luaL_reg bbl_lib [] = {
  {"has_fall_through",bbl_has_fall_through},
  {"next",bbl_next},
  {"size",bbl_size},
  {"ins_tail",bbl_ins_tail},
  {"address",bbl_address},
  {"original",bbl_original},
  {"num_ins",bbl_num_ins},
  {"move_all_attributes",bbl_move_all_attributes},
  {"ins_head",bbl_ins_head},
  {"prev",bbl_prev},
  {"add_callback",add_bbl_call},

  {NULL, NULL}
};

const struct luaL_reg bbl_lib_m [] = {
  {"has_fall_through",bbl_has_fall_through},
  {"next",bbl_next},
  {"size",bbl_size},
  {"ins_tail",bbl_ins_tail},
  {"address",bbl_address},
  {"original",bbl_original},
  {"num_ins",bbl_num_ins},
  {"move_all_attributes",bbl_move_all_attributes},
  {"ins_head",bbl_ins_head},
  {"prev",bbl_prev},
  {"add_callback",add_bbl_call},

  {NULL, NULL}
};


#endif
