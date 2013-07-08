#ifndef __PINT_LUA_CALLBACKS__
#define __PINT_LUA_CALLBACKS__

extern "C" {
    #include <lua.h>
    #include <lauxlib.h>
    #include <lualib.h>
}

#include "enums/enum_iarg_type.h"

#include<map>
#include<set>
#include<vector>
#include<string>
using namespace std;

struct LUA_CALLBACK {
  lua_State *L;
  int id;
  vector<IARG_TYPE>* arg_types;
  void* trampoline_data;
};

class callback_mgr {
  public:
  map<string,set<LUA_CALLBACK*> > registered;
  int id;
  callback_mgr();
  LUA_CALLBACK* make(lua_State *L, string tag);
  void clear(string tag);
};


LUA_CALLBACK* new_callback(lua_State* L);

int init_callback_table(lua_State*);

int store_callback(lua_State* L, int index, int callback_id);

int get_callback(lua_State* L, int callback_id);

#endif
