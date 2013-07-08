#include "pin.H"

extern "C" {
    #include <lua.h>
    #include <lauxlib.h>
    #include <lualib.h>
}

#include "lua_typed_callback.h"
#include "lua_callback.h"

int CALLBACK_to_lua(lua_State *L, LUA_CALLBACK* cb) {
    if(!cb) {
        lua_pushnil(L);
        return 1;
      }
    LUA_CALLBACK **cbp = (LUA_CALLBACK **)lua_newuserdata(L, sizeof(LUA_CALLBACK*));
    *cbp = cb;
    luaL_getmetatable(L, "pin.TypedCallback");
    lua_setmetatable(L, -2);
  return 1;
}

LUA_CALLBACK* check_typed_callback (lua_State *L, int pos) {
  void **ud = (void**)luaL_checkudata(L, pos, "pin.TypedCallback");
  luaL_argcheck(L, ud != NULL, pos, "`pin.TypedCallback' expected");
  return (LUA_CALLBACK *)(*ud);
}

int luaopen_typed_callback (lua_State *L) {
  luaL_newmetatable(L, "pin.TypedCallback");
  luaL_openlib(L, "TypedCallback", typed_callback_lib, 0);
  return 1;
}


int create_typed_callback(lua_State *L){
  int len = lua_gettop(L);
  vector<IARG_TYPE> *buffer = new vector<IARG_TYPE>();
  LUA_CALLBACK*  cb = new_callback(L);
  cb -> arg_types = buffer; // the userdata holds the type info for this callback
  store_callback(L,-1,cb->id);

  for(int i = 1; i < len; i++){
    //note i < len because the last argument is func, and the stack is indexed by (1..len) not (0..len-1)
    IARG_TYPE arg = lookup_string_to_iarg_type(L,lua_tostring(L,i));
    buffer->push_back(arg);
  }
  CALLBACK_to_lua(L,cb);
  return 1;
}

IARGLIST get_instrument_arglist(lua_State *L, int offset){
  IARGLIST arglist = IARGLIST_Alloc();
  LUA_CALLBACK*  cb = check_typed_callback(L,offset+1);
  IARGLIST_AddArguments(arglist, IARG_PTR, (void*)cb, IARG_END);

  int lua_arg_index = offset+2;
  for(vector<IARG_TYPE>::iterator itr = cb->arg_types->begin(); itr != cb->arg_types->end(); itr ++){
    IARG_TYPE arg = *itr;
    IARGLIST_AddArguments(arglist, arg, IARG_END); break;
    switch(arg) {
      case IARG_ADDRINT:
      case IARG_UINT32:
      IARGLIST_AddArguments(arglist, arg, lua_tonumber(L,lua_arg_index++), IARG_END); break;
      case IARG_BOOL:
      IARGLIST_AddArguments(arglist, arg, lua_toboolean(L,lua_arg_index++), IARG_END); break;
      case IARG_PTR:
        lua_pushstring(L,"cannot use IARG_PTR for callback currently");lua_error(L); break;
      default: break;

    }
  }
  return arglist;
}


int instrument_lua_callback(lua_State *L){
  LUA_CALLBACK* cb = (LUA_CALLBACK*)lua_touserdata(L,1);
  lua_pop(L,1);
  get_callback(L, cb->id);

  va_list *argp = ((va_list*)cb->trampoline_data);

  vector<IARG_TYPE>* args = (vector<IARG_TYPE>*)(cb->arg_types);
  int count = 0;

  if(!args){
    lua_pushstring(L,"no type info given for instrumentation callback");
    lua_error(L);
  }

  for(vector<IARG_TYPE>::iterator itr = args->begin(); itr != args->end() ; itr++){ //WARNING THIS IGNORES THE DO NOT USE FOR IARG_LAST
      count ++;
      switch(*itr){
      case IARG_ADDRINT:
      case IARG_REG_VALUE:
      case IARG_INST_PTR:
      case IARG_MEMORYREAD_EA:
      case IARG_MEMORYREAD2_EA:
      case IARG_MEMORYWRITE_EA:
      case IARG_BRANCH_TARGET_ADDR:
      case IARG_SYSARG_VALUE:
      case IARG_SYSRET_VALUE:
      case IARG_FALLTHROUGH_ADDR:
      case IARG_FUNCARG_CALLSITE_VALUE:
      case IARG_FUNCARG_ENTRYPOINT_VALUE:
      case IARG_FUNCRET_EXITPOINT_VALUE:
      case IARG_RETURN_IP:
      case IARG_SYSCALL_NUMBER:
      case IARG_MEMORYOP_EA:
      case IARG_REG_OUTPUT_FRAME_VALUE:
        lua_pushnumber(L, va_arg(*argp, ADDRINT)); break;
      case IARG_UINT32:
      case IARG_MEMORYREAD_SIZE:
      case IARG_MEMORYWRITE_SIZE:
        lua_pushnumber(L, va_arg(*argp, UINT32)); break;
      case IARG_SYSRET_ERRNO:
        lua_pushnumber(L, va_arg(*argp, INT32)); break;
      case IARG_REG_NAT_VALUE:
      case IARG_BOOL:
      case IARG_BRANCH_TAKEN:
      case IARG_EXECUTING:
      case IARG_FIRST_REP_ITERATION:
        lua_pushboolean(L, va_arg(*argp, int)); break;
      default:
      /* TODO: Implement
      IARG_SYSARG_REFERENCE   Type: "ADDRINT *"
      IARG_FUNCARG_CALLSITE_REFERENCE   Type: "ADDRINT *"
      IARG_FUNCARG_ENTRYPOINT_REFERENCE   Type: "ADDRINT *"
      IARG_FUNCRET_EXITPOINT_REFERENCE  Type: "ADDRINT *"
      IARG_REG_OUTPUT_FRAME_REFERENCE   Type: "ADDRINT *"
      IARG_CONTEXT  Type: "CONTEXT *"
      IARG_CONST_CONTEXT  Type: "CONTEXT *"
      IARG_REG_REFERENCE  Type: "PIN_REGISTER *"
      IARG_REG_CONST_REFERENCE  Type: "PIN_REGISTER *"
      IARG_ORIG_FUNCPTR   Type: AFUNPTR
      IARG_PTR  Type: "VOID *"
      IARG_PROTOTYPE  Type: PROTO
      IARG_THREAD_ID  Type: THREADID
      IARG_CALL_ORDER   Type: CALL_ORDER*/

        lua_pushstring(L,"unknown argtype");
        lua_error(L);
    }
  }

  lua_call(L,count,0);
  return 0;
}

void instrument_callback(LUA_CALLBACK* cb, ...){
  lua_State* L = cb->L;

  va_list argp;
  va_start(argp, cb);
  cb->trampoline_data = &argp;

  if(lua_cpcall(L,instrument_lua_callback,cb)!=0){
    lua_error(L);
  }

  va_end(argp);
}

