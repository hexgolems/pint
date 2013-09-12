  #ifndef __PINT_LUA_INSTRUMENTATION_CALLBACKS__
  #define __PINT_LUA_INSTRUMENTATION_CALLBACKS__

  extern "C" {
      #include <lua.h>
      #include <lauxlib.h>
      #include <lualib.h>
  }

  #include "lua_callback.h"
  #include "gen_fn/lua_ins.h"
  #include "pin.H"

#define ADD_INSTRUMENTATION_FUNCTION_HEADERS(name_lower, name_up)\
    int  name_lower##_instrumentation_function(lua_State *L);\
    void name_lower##_instrumentation_callback_pin(name_up, VOID* v);\
    int  name_lower##_instrumentation_callback_lua(lua_State* L, VOID* v);\

ADD_INSTRUMENTATION_FUNCTION_HEADERS(ins, INS)
ADD_INSTRUMENTATION_FUNCTION_HEADERS(trace, TRACE)
ADD_INSTRUMENTATION_FUNCTION_HEADERS(rtn, RTN)

#endif
