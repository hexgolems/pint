  #ifndef __PINT_LUA_TRACE_CALLBACKS__
  #define __PINT_LUA_TRACE_CALLBACKS__

  extern "C" {
      #include <lua.h>
      #include <lauxlib.h>
      #include <lualib.h>
  }

  #include "lua_callback.h"
  #include "gen_fn/lua_trace.h"
  #include "pin.H"
    // this function is called from lua and registers a callback to trace_trace_callback
    int register_trace_trace(lua_State *L);

    //this function calls  trace_trace_callback_lua such that it can use the lua stack
    void trace_trace_callback(IMG img, VOID* v);

    //this function is called as a lua_c function and calls the lua script callback
    int trace_trace_callback_lua(lua_State* L, VOID* v);

#endif
