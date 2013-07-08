  #ifndef __PINT_LUA_INS_CALLBACKS__
  #define __PINT_LUA_INS_CALLBACKS__

  extern "C" {
      #include <lua.h>
      #include <lauxlib.h>
      #include <lualib.h>
  }

  #include "lua_callback.h"
  #include "gen_fn/lua_ins.h"
  #include "pin.H"
    // this function is called from lua and registers a callback to ins_instruction_callback
    int register_ins_instruction(lua_State *L);

    //this function calls  ins_instruction_callback_lua such that it can use the lua stack
    void ins_instruction_callback(IMG img, VOID* v);

    //this function is called as a lua_c function and calls the lua script callback
    int ins_instruction_callback_lua(lua_State* L, VOID* v);

#endif
