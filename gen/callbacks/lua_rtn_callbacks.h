  #ifndef __PINT_LUA_RTN_CALLBACKS__
  #define __PINT_LUA_RTN_CALLBACKS__

  extern "C" {
      #include <lua.h>
      #include <lauxlib.h>
      #include <lualib.h>
  }

  #include "lua_callback.h"
  #include "gen_fn/lua_rtn.h"
  #include "pin.H"
    // this function is called from lua and registers a callback to rtn_routine_callback
    int register_rtn_routine(lua_State *L);

    //this function calls  rtn_routine_callback_lua such that it can use the lua stack
    void rtn_routine_callback(IMG img, VOID* v);

    //this function is called as a lua_c function and calls the lua script callback
    int rtn_routine_callback_lua(lua_State* L, VOID* v);

#endif
