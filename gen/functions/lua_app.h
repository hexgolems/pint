
#ifndef __PINT_LUA_APP_WRAPPER__
#define __PINT_LUA_APP_WRAPPER__

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


int luaopen_app (lua_State *L);
int app_img_tail (lua_State *L) ; 
int app_img_head (lua_State *L) ; 
const struct luaL_reg app_lib [] = {
  	{"img_tail",app_img_tail},
	{"img_head",app_img_head},

  {NULL, NULL}
};

#endif
