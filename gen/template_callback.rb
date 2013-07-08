def header(value_type, callback_names)
  t=value_type
  td = t.downcase
  str = <<EOF
  #ifndef __PINT_LUA_#{t}_CALLBACKS__
  #define __PINT_LUA_#{t}_CALLBACKS__

  extern "C" {
      #include <lua.h>
      #include <lauxlib.h>
      #include <lualib.h>
  }

  #include "lua_callback.h"
  #include "gen_fn/lua_#{td}.h"
  #include "pin.H"
EOF

  callback_names.each do |name|
    str += <<EOF
    // this function is called from lua and registers a callback to #{td}_#{name}_callback
    int register_#{td}_#{name}(lua_State *L);

    //this function calls  #{td}_#{name}_callback_lua such that it can use the lua stack
    void #{td}_#{name}_callback(IMG img, VOID* v);

    //this function is called as a lua_c function and calls the lua script callback
    int #{td}_#{name}_callback_lua(lua_State* L, VOID* v);

EOF
  end
str += "#endif"
return str
end

def cpp(base,funcs)
  t=base
  td = t.downcase
str = <<EOF

extern "C" {
    #include <lua.h>
    #include <lauxlib.h>
    #include <lualib.h>
}

#include "lua_callback.h"
#include "gen_fn/lua_#{td}.h"
#include "gen_fn/lua_#{td}_callbacks.h"
#include "pin.H"
#include "pintool_defines.h"

EOF
funcs.each do |(name,pin_name)|
str += <<EOF
//this function is called as a lua_c function and has a stack
int #{td}_#{name}_callback_lua(lua_State* L){
  LUA_CALLBACK* callback = (LUA_CALLBACK*)lua_touserdata(L,1);
  get_callback(L, callback->id);
  #{base}_to_lua(L, *(#{base}*)(callback->ud) );
  lua_call(L, 1, 0);
  return 0;
}

//this function is registered as callback to PIN
void #{td}_#{name}_callback(#{base} #{td}, VOID* v){
  AQUIRE_PINTOOL_MUTEX
  LUA_CALLBACK* callback = (LUA_CALLBACK*)(v);
  callback->ud = &#{td};
  lua_State *L = callback->L;
  if( lua_cpcall(L,#{td}_#{name}_callback_lua,callback) != 0) {
    lua_error(L);
  }
  callback->ud = NULL;
  RELEASE_PINTOOL_MUTEX
}

// this function is called from lua and registers a callback to img_load_callback
int register_#{td}_#{name}(lua_State *L){
  LUA_CALLBACK* callback = new_callback(L);
  store_callback(L, 1, callback->id);
  #{pin_name} (#{td}_#{name}_callback, callback);
  return 0;
}
EOF
end
return str
end
