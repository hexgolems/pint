  #ifndef __PINT_LUA_IMG_CALLBACKS__
  #define __PINT_LUA_IMG_CALLBACKS__

  extern "C" {
      #include <lua.h>
      #include <lauxlib.h>
      #include <lualib.h>
  }

  #include "lua_callback.h"
  #include "gen_fn/lua_img.h"
  #include "pin.H"
    // this function is called from lua and registers a callback to img_load_callback
    int register_img_load(lua_State *L);

    //this function calls  img_load_callback_lua such that it can use the lua stack
    void img_load_callback(IMG img, VOID* v);

    //this function is called as a lua_c function and calls the lua script callback
    int img_load_callback_lua(lua_State* L, VOID* v);

    // this function is called from lua and registers a callback to img_unload_callback
    int register_img_unload(lua_State *L);

    //this function calls  img_unload_callback_lua such that it can use the lua stack
    void img_unload_callback(IMG img, VOID* v);

    //this function is called as a lua_c function and calls the lua script callback
    int img_unload_callback_lua(lua_State* L, VOID* v);

#endif
