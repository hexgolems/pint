
extern "C" {
    #include <lua.h>
    #include <lauxlib.h>
    #include <lualib.h>
}

#include "lua_callback.h"
#include "gen_fn/lua_trace.h"
#include "gen_fn/lua_trace_callbacks.h"
#include "pin.H"
#include "pintool_defines.h"

//this function is called as a lua_c function and has a stack
int trace_trace_callback_lua(lua_State* L){
  LUA_CALLBACK* callback = (LUA_CALLBACK*)lua_touserdata(L,1);
  get_callback(L, callback->id);
  TRACE_to_lua(L, *(TRACE*)(callback->ud) );
  lua_call(L, 1, 0);
  return 0;
}

//this function is registered as callback to PIN
void trace_trace_callback(TRACE trace, VOID* v){
  AQUIRE_PINTOOL_MUTEX
  LUA_CALLBACK* callback = (LUA_CALLBACK*)(v);
  callback->ud = &trace;
  lua_State *L = callback->L;
  if( lua_cpcall(L,trace_trace_callback_lua,callback) != 0) {
    lua_error(L);
  }
  callback->ud = NULL;
  RELEASE_PINTOOL_MUTEX
}

// this function is called from lua and registers a callback to img_load_callback
int register_trace_trace(lua_State *L){
  LUA_CALLBACK* callback = new_callback(L);
  store_callback(L, 1, callback->id);
  TRACE_AddInstrumentFunction (trace_trace_callback, callback);
  return 0;
}
