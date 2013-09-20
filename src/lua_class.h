#ifndef __PINT_LUA_WRAPPER__
#define __PINT_LUA_WRAPPER__

#include "pin.H"

extern "C" {
    #include <lua.h>
    #include <lauxlib.h>
    #include <lualib.h>
}

class Lua
{
  lua_State *L;
  FILE* lua_std_out;
  FILE* lua_std_in;
  FILE* lua_std_err;


public:
  Lua() : L(lua_open()) { }

  ~Lua() {
    lua_close(L);
  }

  // implicitly act as a lua_State pointer
  inline operator lua_State*() {
    return L;
  }

  void setup(std::string scripn_file_name);
  void open_all();
  void done(int exitstatus);


  void report_errors(int status);

};

#endif
