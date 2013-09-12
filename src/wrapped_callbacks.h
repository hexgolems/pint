#ifndef __PINT_LUA_WRAPPED_CALLBACKS__
#define __PINT_LUA_WRAPPED_CALLBACKS__

extern "C" {
    #include <lua.h>
    #include <lauxlib.h>
    #include <lualib.h>
}


#include "gen_fn/lua_img_callbacks.h"
#include "gen_fn/lua_instrumentation_callbacks.h"

const struct luaL_reg callbacks_lib [] = {
{"img_load",register_img_load},
{"img_unload",register_img_unload},
{"instruction",ins_instrumentation_function},
{"routine",rtn_instrumentation_function},
{"trace",trace_instrumentation_function},
{NULL, NULL}
};

int luaopen_callbacks (lua_State *L) {
  luaL_newmetatable(L, "pin.CB");
  luaL_openlib(L, "CB", callbacks_lib, 0);
  return 1;
}

#endif
