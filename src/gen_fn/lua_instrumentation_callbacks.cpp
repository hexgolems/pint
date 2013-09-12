extern "C" {
    #include <lua.h>
    #include <lauxlib.h>
    #include <lualib.h>
}

#include "lua_callback.h"
#include "gen_fn/lua_ins.h"
#include "gen_fn/lua_bbl.h"
#include "pin.H"
#include "pintool_defines.h"

//this function is called as a lua_c function and has a stack
#define ADD_INSTRUMENTATION_LUA_CALLBACK(name_lower,name_up)\
int name_lower##_instrumentation_callback_lua(lua_State* L){\
  LUA_CALLBACK* callback = (LUA_CALLBACK*)lua_touserdata(L,1);\
  get_callback(L, callback->id);\
  name_up##_to_lua(L, *(name_up*)(callback->trampoline_data) );\
  lua_call(L, 1, 0);\
  return 0;\
}

//this function is registered as callback to PIN
#define ADD_INSTRUMENTATION_PIN_CALLBACK(name_lower, name_up) \
void name_lower##_instrumentation_callback_pin(name_up data, VOID* v){\
  AQUIRE_PINTOOL_MUTEX\
  LUA_CALLBACK* callback = (LUA_CALLBACK*)(v);\
  callback->trampoline_data = &data;\
  lua_State *L = callback->L;\
  if( lua_cpcall(L,name_lower##_instrumentation_callback_lua,callback) != 0) {\
    lua_error(L);\
  }\
  callback->trampoline_data = NULL;\
  RELEASE_PINTOOL_MUTEX\
}

// this function is called from lua and registers a callback in pin
#define ADD_INSTRUMENTATION_REGISTER_CALL(name_lower, name_up) \
int name_lower##_instrumentation_function(lua_State *L){\
  LUA_CALLBACK* callback = new_callback(L);\
  store_callback(L, 1, callback->id);\
  name_up##_AddInstrumentFunction (name_lower##_instrumentation_callback_pin, callback);\
  return 0;\
}

#define ADD_INSTRUMENTATION_FUNCTIONS(name_lower, name_up)\
  ADD_INSTRUMENTATION_LUA_CALLBACK(name_lower,name_up)\
  ADD_INSTRUMENTATION_PIN_CALLBACK(name_lower, name_up) \
  ADD_INSTRUMENTATION_REGISTER_CALL(name_lower, name_up) \

ADD_INSTRUMENTATION_FUNCTIONS(ins,INS)
ADD_INSTRUMENTATION_FUNCTIONS(trace,TRACE)
ADD_INSTRUMENTATION_FUNCTIONS(rtn,RTN)
