
#include "gen_fn/lua_ins_instr.h"
#include <stdarg.h>
#include <vector>
#include "enums/enum_iarg_type.h"
#include "enums/enum_ipoint.h"
#include "lua_typed_callback.h"
#include "gen_fn/lua_ins.h"
#include "pintool_defines.h"

using namespace std;

extern "C" {
    #include <lua.h>
    #include <lauxlib.h>
    #include <lualib.h>
}

#include "pin.H"

/*
IARGLIST setup_instrument_callback(lua_State *L){
  //TODO add global ppol of IARG_TYPE* buffers
  int len = lua_gettop(L);
  IARGLIST arglist = IARGLIST_Alloc();
  vector<IARG_TYPE> *buffer = new vector<IARG_TYPE>();
  LUA_CALLBACK*  cb = new_callback(L);
  cb -> arg_types = buffer; // the userdata holds the type info for this callback
  //store_callback(L,-1,cb->id); //the last argument is the callback func
  store_callback(L,-1,cb->id);

  IARGLIST_AddArguments(arglist, IARG_PTR, (void*)cb, IARG_END);

  for(int i = 3; i < len; i++){ //note i < len because the last argument is func, and the stack is indexed by (1..len) not (0..len-1)
    IARG_TYPE arg = lookup_string_to_iarg_type(L,lua_tostring(L,i));
    buffer->push_back(arg);
    switch(arg) {
      case IARG_ADDRINT:
      case IARG_UINT32:
      IARGLIST_AddArguments(arglist, arg, lua_tonumber(L,++i), IARG_END); break;
      case IARG_BOOL:
      IARGLIST_AddArguments(arglist, arg, lua_toboolean(L,++i), IARG_END); break;
      case IARG_PTR:
        lua_pushstring(L,"cannot use IARG_PTR for callback currently");lua_error(L); break;
      default:
        IARGLIST_AddArguments(arglist, arg, IARG_END); break;
    }
  }
  return arglist;
} */


int add_ins_call(lua_State *L) {
  IARGLIST arglist = get_instrument_arglist(L,1);

  INS_InsertCall(
      *check_ins(L,1),
      lookup_string_to_ipoint(L,lua_get_string(L,3)),
      (AFUNPTR)instrument_callback,
      IARG_IARGLIST,
      arglist,
      IARG_END);

  IARGLIST_Free(arglist);
  return 0;
}
