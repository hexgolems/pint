#include "lua_ins.h"
#include "lua_sec.h"
#include "lua_rtn.h"
#include "lua_sym.h"
#include "../enums/enum_probe_mode.h"

#include "../gen_fn/lua_rtn.h"
#include "lua.h"
#include "pin.H"

extern "C" {
    #include <lua.h>
    #include <lauxlib.h>
    #include <lualib.h>
}
int RTN_to_lua(lua_State *L, RTN rtn) {
    if(!RTN_Valid(rtn)) {
        lua_pushnil(L);
        return 1;
      }
    RTN *i = (RTN *)lua_newuserdata(L, sizeof(RTN));
    *i = rtn;
    luaL_getmetatable(L, "pin.Rtn");
    lua_setmetatable(L, -2);

  return 1;
}

RTN *check_rtn (lua_State *L, int pos) {
  void *ud = luaL_checkudata(L, pos, "pin.Rtn");
  luaL_argcheck(L, ud != NULL, pos, "`Rtn' expected");
  return (RTN *)ud;
}

int luaopen_rtn (lua_State *L) {
  luaL_newmetatable(L, "pin.Rtn");
  lua_pushstring(L, "__index");
  lua_pushvalue(L, -2);  /* pushes the metatable */
  lua_settable(L, -3);  /* metatable.__index = metatable */
  luaL_openlib(L, NULL, rtn_lib_m, 0);
  luaL_openlib(L, "Rtn", rtn_lib, 0);
  return 1;
}
int rtn_is_safe_for_probed_replacement_ex (lua_State *L) {
  RTN* v1 = check_rtn(L,1);
  PROBE_MODE v2 = lookup_string_to_probe_mode(L,lua_tostring(L,2));
  BOOL r = RTN_IsSafeForProbedReplacementEx(*v1,v2);
  lua_pushboolean(L, r);
  return 1;
}
int rtn_is_safe_for_probed_insertion_ex (lua_State *L) {
  RTN* v1 = check_rtn(L,1);
  PROBE_MODE v2 = lookup_string_to_probe_mode(L,lua_tostring(L,2));
  BOOL r = RTN_IsSafeForProbedInsertionEx(*v1,v2);
  lua_pushboolean(L, r);
  return 1;
}
int rtn_ins_head (lua_State *L) {
  RTN* v1 = check_rtn(L,1);
  INS_to_lua(L, RTN_InsHead(*v1));
  return 1;
}
int rtn_replace (lua_State *L) {
  RTN* v1 = check_rtn(L,1);
  AFUNPTR v2 = (VOID(*)())((UINT64)lua_tonumber(L,2));
  AFUNPTR r = RTN_Replace(*v1,v2);
  lua_pushnumber(L, (UINT64)r);
  return 1;
}
int rtn_is_safe_for_probed_insertion (lua_State *L) {
  RTN* v1 = check_rtn(L,1);
  BOOL r = RTN_IsSafeForProbedInsertion(*v1);
  lua_pushboolean(L, r);
  return 1;
}
int rtn_is_safe_for_probed_replacement (lua_State *L) {
  RTN* v1 = check_rtn(L,1);
  BOOL r = RTN_IsSafeForProbedReplacement(*v1);
  lua_pushboolean(L, r);
  return 1;
}
int rtn_find_by_address (lua_State *L) {
  ADDRINT v1 = lua_tonumber(L,1);
  RTN_to_lua(L, RTN_FindByAddress(v1));
  return 1;
}
int rtn_sec (lua_State *L) {
  RTN* v1 = check_rtn(L,1);
  SEC_to_lua(L, RTN_Sec(*v1));
  return 1;
}
int rtn_num_ins (lua_State *L) {
  RTN* v1 = check_rtn(L,1);
  UINT32 r = RTN_NumIns(*v1);
  lua_pushnumber(L, r);
  return 1;
}
int rtn_funptr (lua_State *L) {
  RTN* v1 = check_rtn(L,1);
  AFUNPTR r = RTN_Funptr(*v1);
  lua_pushnumber(L, (UINT64)r);
  return 1;
}
int rtn_ins_head_only (lua_State *L) {
  RTN* v1 = check_rtn(L,1);
  INS_to_lua(L, RTN_InsHeadOnly(*v1));
  return 1;
}
int rtn_open (lua_State *L) {
  RTN* v1 = check_rtn(L,1);
   RTN_Open(*v1);
  return 0;
}
int rtn_id (lua_State *L) {
  RTN* v1 = check_rtn(L,1);
  INT32 r = RTN_Id(*v1);
  lua_pushnumber(L, r);
  return 1;
}
int rtn_find_name_by_address (lua_State *L) {
  ADDRINT v1 = lua_tonumber(L,1);
  string r = RTN_FindNameByAddress(v1);
  lua_pushstring(L, r.c_str());
  return 1;
}
int rtn_size (lua_State *L) {
  RTN* v1 = check_rtn(L,1);
  USIZE r = RTN_Size(*v1);
  lua_pushnumber(L, r);
  return 1;
}
int rtn_range (lua_State *L) {
  RTN* v1 = check_rtn(L,1);
  USIZE r = RTN_Range(*v1);
  lua_pushnumber(L, r);
  return 1;
}
int rtn_replace_probed_ex (lua_State *L) {
  RTN* v1 = check_rtn(L,1);
  PROBE_MODE v2 = lookup_string_to_probe_mode(L,lua_tostring(L,2));
  AFUNPTR v3 = (VOID(*)())((UINT64)lua_tonumber(L,3));
  AFUNPTR r = RTN_ReplaceProbedEx(*v1,v2,v3);
  lua_pushnumber(L, (UINT64)r);
  return 1;
}
int rtn_sym (lua_State *L) {
  RTN* v1 = check_rtn(L,1);
  SYM_to_lua(L, RTN_Sym(*v1));
  return 1;
}
int rtn_name (lua_State *L) {
  RTN* v1 = check_rtn(L,1);
  string r = RTN_Name(*v1);
  lua_pushstring(L, r.c_str());
  return 1;
}
int rtn_next (lua_State *L) {
  RTN* v1 = check_rtn(L,1);
  RTN_to_lua(L, RTN_Next(*v1));
  return 1;
}
int rtn_close (lua_State *L) {
  RTN* v1 = check_rtn(L,1);
   RTN_Close(*v1);
  return 0;
}
int rtn_prev (lua_State *L) {
  RTN* v1 = check_rtn(L,1);
  RTN_to_lua(L, RTN_Prev(*v1));
  return 1;
}
int rtn_replace_probed (lua_State *L) {
  RTN* v1 = check_rtn(L,1);
  AFUNPTR v2 = (VOID(*)())((UINT64)lua_tonumber(L,2));
  AFUNPTR r = RTN_ReplaceProbed(*v1,v2);
  lua_pushnumber(L, (UINT64)r);
  return 1;
}
int rtn_create_at (lua_State *L) {
  ADDRINT v1 = lua_tonumber(L,1);
  string v2 = lua_tostring(L,2);
  RTN_to_lua(L, RTN_CreateAt(v1,v2));
  return 1;
}
int rtn_address (lua_State *L) {
  RTN* v1 = check_rtn(L,1);
  ADDRINT r = RTN_Address(*v1);
  lua_pushnumber(L, r);
  return 1;
}
int rtn_ins_tail (lua_State *L) {
  RTN* v1 = check_rtn(L,1);
  INS_to_lua(L, RTN_InsTail(*v1));
  return 1;
}
