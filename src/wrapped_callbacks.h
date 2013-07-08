#ifndef __PINT_LUA_WRAPPED_CALLBACKS__
#define __PINT_LUA_WRAPPED_CALLBACKS__

extern "C" {
    #include <lua.h>
    #include <lauxlib.h>
    #include <lualib.h>
}


#include "gen_fn/lua_img_callbacks.h"
#include "gen_fn/lua_ins_callbacks.h"
#include "gen_fn/lua_rtn_callbacks.h"
#include "gen_fn/lua_trace_callbacks.h"

const struct luaL_reg callbacks_lib [] = {
{"img_load",register_img_load},
{"img_unload",register_img_unload},
{"instruction",register_ins_instruction},
{"routine",register_rtn_routine},
{"trace",register_trace_trace},
{NULL, NULL}
};

int luaopen_callbacks (lua_State *L) {
  luaL_newmetatable(L, "pin.CB");
  luaL_openlib(L, "CB", callbacks_lib, 0);
  return 1;
}

#endif
