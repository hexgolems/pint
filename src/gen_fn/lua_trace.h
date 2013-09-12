
#ifndef __PINT_LUA_TRACE_WRAPPER__
#define __PINT_LUA_TRACE_WRAPPER__

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

int TRACE_to_lua(lua_State *L, TRACE trace);
  TRACE *check_trace (lua_State *L, int);
int luaopen_trace (lua_State *L);
int trace_original (lua_State *L) ;
int trace_bbl_tail (lua_State *L) ;
int trace_num_ins (lua_State *L) ;
int trace_num_bbl (lua_State *L) ;
int trace_bbl_head (lua_State *L) ;
int trace_stub_size (lua_State *L) ;
int trace_rtn (lua_State *L) ;
int trace_address (lua_State *L) ;
int trace_has_fall_through (lua_State *L) ;
int trace_size (lua_State *L) ;

const struct luaL_reg trace_lib [] = {
  {"original",trace_original},
  {"bbl_tail",trace_bbl_tail},
  {"num_ins",trace_num_ins},
  {"num_bbl",trace_num_bbl},
  {"bbl_head",trace_bbl_head},
  {"stub_size",trace_stub_size},
  {"rtn",trace_rtn},
  {"address",trace_address},
  {"has_fall_through",trace_has_fall_through},
  {"size",trace_size},

  {NULL, NULL}
};

const struct luaL_reg trace_lib_m [] = {
  {"original",trace_original},
  {"bbl_tail",trace_bbl_tail},
  {"num_ins",trace_num_ins},
  {"num_bbl",trace_num_bbl},
  {"bbl_head",trace_bbl_head},
  {"stub_size",trace_stub_size},
  {"rtn",trace_rtn},
  {"address",trace_address},
  {"has_fall_through",trace_has_fall_through},
  {"size",trace_size},

  {NULL, NULL}
};

#endif
