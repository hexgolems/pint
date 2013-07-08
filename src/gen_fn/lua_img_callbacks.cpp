
extern "C" {
    #include <lua.h>
    #include <lauxlib.h>
    #include <lualib.h>
}

#include "lua_callback.h"
#include "gen_fn/lua_img.h"
#include "gen_fn/lua_img_callbacks.h"
#include "pin.H"
#include "pintool_defines.h"

//this function is called as a lua_c function and has a stack
int img_load_callback_lua(lua_State* L){
  LUA_CALLBACK* callback = (LUA_CALLBACK*)lua_touserdata(L,1);
  get_callback(L, callback->id);
  IMG_to_lua(L, *(IMG*)(callback->trampoline_data) );
  lua_call(L, 1, 0);
  return 0;
}

//this function is registered as callback to PIN
void img_load_callback(IMG img, VOID* v){
  AQUIRE_PINTOOL_MUTEX
  LUA_CALLBACK* callback = (LUA_CALLBACK*)(v);
  callback->trampoline_data = &img;
  lua_State *L = callback->L;
  if( lua_cpcall(L,img_load_callback_lua,callback) != 0) {
    lua_error(L);
  }
  callback->trampoline_data = NULL;
  RELEASE_PINTOOL_MUTEX
}

// this function is called from lua and registers a callback to img_load_callback
int register_img_load(lua_State *L){
  LUA_CALLBACK* callback = new_callback(L);
  store_callback(L, 1, callback->id);
  IMG_AddInstrumentFunction (img_load_callback, callback);
  return 0;
}
//this function is called as a lua_c function and has a stack
int img_unload_callback_lua(lua_State* L){
  LUA_CALLBACK* callback = (LUA_CALLBACK*)lua_touserdata(L,1);
  get_callback(L, callback->id);
  IMG_to_lua(L, *(IMG*)(callback->trampoline_data) );
  lua_call(L, 1, 0);
  return 0;
}

//this function is registered as callback to PIN
void img_unload_callback(IMG img, VOID* v){
  AQUIRE_PINTOOL_MUTEX
  LUA_CALLBACK* callback = (LUA_CALLBACK*)(v);
  callback->trampoline_data = &img;
  lua_State *L = callback->L;
  if( lua_cpcall(L,img_unload_callback_lua,callback) != 0) {
    lua_error(L);
  }
  callback->trampoline_data = NULL;
  RELEASE_PINTOOL_MUTEX
}

// this function is called from lua and registers a callback to img_load_callback
int register_img_unload(lua_State *L){
  LUA_CALLBACK* callback = new_callback(L);
  store_callback(L, 1, callback->id);
  IMG_AddUnloadFunction (img_unload_callback, callback);
  return 0;
}
