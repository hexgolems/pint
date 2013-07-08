extern "C" {
    #include <lua.h>
    #include <lauxlib.h>
    #include <lualib.h>
}

#include "lua_callback.h"
#include "pintool_defines.h"
#include "enums/enum_iarg_type.h"

#include<map>
#include<set>
#include<vector>
using namespace std;

int init_callback_table(lua_State* L){
    lua_pushstring(L, CALLBACK_TABLE_REGISTRY_INDEX);
    lua_newtable(L);
    lua_settable(L, LUA_REGISTRYINDEX);
    return 0;
}

  callback_mgr::callback_mgr(){id = 0;}

  LUA_CALLBACK* callback_mgr::make(lua_State *L, string tag){
    LUA_CALLBACK* cb = new LUA_CALLBACK;
    cb->L= L;
    cb -> id = id++;
    cb -> arg_types = NULL;
    cb -> trampoline_data = NULL;
    registered[tag].insert(cb);
    return cb;
  }

  void callback_mgr::clear( string tag){
    for(set<LUA_CALLBACK*>::iterator itr = registered.at(tag).begin(); itr != registered.at(tag).end(); itr ++ ){
      LUA_CALLBACK *cb = (*itr);
      if(cb->arg_types){
          delete cb->arg_types;
      }
      delete(cb);
    }
    registered.at(tag).clear();
  }

LUA_CALLBACK* new_callback(lua_State* L){
  static callback_mgr mgr;
  return mgr.make(L,"callback");
}

int store_callback(lua_State* L, int index, int cbid){
  if (lua_isfunction(L, index)) {
    lua_pushstring(L, CALLBACK_TABLE_REGISTRY_INDEX);
    lua_gettable(L, LUA_REGISTRYINDEX);
    lua_pushnumber(L, cbid); // this is the callback id for this callback
    if(index < 0){
      lua_pushvalue(L, index-2);  // this is the data (-1 because we just added the key -1 because we added the callback_table)
    } else { lua_pushvalue(L,index);}
    lua_settable(L, -3);
    lua_pop(L, 1);  // finished with the callback table
  } else {
    lua_pushstring(L,"call back value was not a function");
    lua_error(L);
  }
  return 0;
}

int get_callback(lua_State* L, int cbid){

  lua_pushstring(L, CALLBACK_TABLE_REGISTRY_INDEX);
  lua_gettable(L, LUA_REGISTRYINDEX);
  lua_pushnumber(L, cbid);
  lua_gettable(L, -2);  /* the callback table is now at -2 */
  lua_remove(L, -2);  /* finished with the callback table */
  //the callback is now onto of the stack
  return 1;
}
