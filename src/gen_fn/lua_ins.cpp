#include "lua_ins.h"
#include "lua_rtn.h"
#include "lua_reg.h"
#include "../enums/enum_syscall_standard.h"
#include "../enums/enum_reg.h"
#include "../enums/enum_ipoint.h"

#include "../gen_fn/lua_ins.h"
#include "lua.h"
#include "pin.H"

extern "C" {
    #include <lua.h>
    #include <lauxlib.h>
    #include <lualib.h>
}
int INS_to_lua(lua_State *L, INS ins) {
    if(!INS_Valid(ins)) {
        lua_pushnil(L);
        return 1;
      }
    INS *i = (INS *)lua_newuserdata(L, sizeof(INS));
    *i = ins;
    luaL_getmetatable(L, "pin.Ins");
    lua_setmetatable(L, -2);

  return 1;
}

INS *check_ins (lua_State *L, int pos) {
  void *ud = luaL_checkudata(L, pos, "pin.Ins");
  luaL_argcheck(L, ud != NULL, pos, "`Ins' expected");
  return (INS *)ud;
}

int luaopen_ins (lua_State *L) {
  luaL_newmetatable(L, "pin.Ins");
  lua_pushstring(L, "__index");
  lua_pushvalue(L, -2);  /* pushes the metatable */
  lua_settable(L, -3);  /* metatable.__index = metatable */
  luaL_openlib(L, NULL, ins_lib_m, 0);
  luaL_openlib(L, "Ins", ins_lib, 0);
  return 1;
}

#ifdef TARGET_IA32E
int ins_has_property (lua_State *L) {
  INS* v1 = check_ins(L,1);
  INS_PROP v2 = lua_tonumber(L,2);
  BOOL r = INS_HasProperty(*v1,v2);
  lua_pushboolean(L, r);
  return 1;
}
#endif

int ins_operand_memory_scale (lua_State *L) {
  INS* v1 = check_ins(L,1);
  UINT32 v2 = lua_tonumber(L,2);
  UINT32 r = INS_OperandMemoryScale(*v1,v2);
  lua_pushnumber(L, r);
  return 1;
}
int ins_is_mask_mov (lua_State *L) {
  INS* v1 = check_ins(L,1);
  BOOL r = INS_IsMaskMov(*v1);
  lua_pushboolean(L, r);
  return 1;
}
int ins_is_i_ret (lua_State *L) {
  INS* v1 = check_ins(L,1);
  BOOL r = INS_IsIRet(*v1);
  lua_pushboolean(L, r);
  return 1;
}
int ins_is_predicated (lua_State *L) {
  INS* v1 = check_ins(L,1);
  BOOL r = INS_IsPredicated(*v1);
  lua_pushboolean(L, r);
  return 1;
}
int ins_is_sysret (lua_State *L) {
  INS* v1 = check_ins(L,1);
  BOOL r = INS_IsSysret(*v1);
  lua_pushboolean(L, r);
  return 1;
}
int ins_insert_indirect_jump (lua_State *L) {
  INS* v1 = check_ins(L,1);
  IPOINT v2 = lookup_string_to_ipoint(L,lua_tostring(L,2));
  REG v3 = lookup_string_to_reg(L,lua_tostring(L,3));
   INS_InsertIndirectJump(*v1,v2,v3);
  return 0;
}
int ins_address_size_prefix (lua_State *L) {
  INS* v1 = check_ins(L,1);
  BOOL r = INS_AddressSizePrefix(*v1);
  lua_pushboolean(L, r);
  return 1;
}
int ins_mnemonic (lua_State *L) {
  INS* v1 = check_ins(L,1);
  string r = INS_Mnemonic(*v1);
  lua_pushstring(L, r.c_str());
  return 1;
}
int ins_operand_immediate (lua_State *L) {
  INS* v1 = check_ins(L,1);
  UINT32 v2 = lua_tonumber(L,2);
  UINT64 r = INS_OperandImmediate(*v1,v2);
  lua_pushnumber(L, r);
  return 1;
}
int ins_operand_count (lua_State *L) {
  INS* v1 = check_ins(L,1);
  UINT32 r = INS_OperandCount(*v1);
  lua_pushnumber(L, r);
  return 1;
}
int ins_operand_written (lua_State *L) {
  INS* v1 = check_ins(L,1);
  UINT32 v2 = lua_tonumber(L,2);
  BOOL r = INS_OperandWritten(*v1,v2);
  lua_pushboolean(L, r);
  return 1;
}
int ins_has_memory_read2 (lua_State *L) {
  INS* v1 = check_ins(L,1);
  BOOL r = INS_HasMemoryRead2(*v1);
  lua_pushboolean(L, r);
  return 1;
}
int ins_is_sub (lua_State *L) {
  INS* v1 = check_ins(L,1);
  BOOL r = INS_IsSub(*v1);
  lua_pushboolean(L, r);
  return 1;
}
int ins_full_reg_r_contain (lua_State *L) {
  INS* v1 = check_ins(L,1);
  REG v2 = lookup_string_to_reg(L,lua_tostring(L,2));
  BOOL r = INS_FullRegRContain(*v1,v2);
  lua_pushboolean(L, r);
  return 1;
}
int ins_reg_r (lua_State *L) {
  INS* v1 = check_ins(L,1);
  UINT32 v2 = lua_tonumber(L,2);
  string r = lookup_reg_to_string(L,INS_RegR(*v1,v2));
  lua_pushstring(L, r.c_str());
  return 1;
}
int ins_operand_memory_segment_reg (lua_State *L) {
  INS* v1 = check_ins(L,1);
  UINT32 v2 = lua_tonumber(L,2);
  string r = lookup_reg_to_string(L,INS_OperandMemorySegmentReg(*v1,v2));
  lua_pushstring(L, r.c_str());
  return 1;
}
int ins_memory_operand_index_to_operand_index (lua_State *L) {
  INS* v1 = check_ins(L,1);
  UINT32 v2 = lua_tonumber(L,2);
  UINT32 r = INS_MemoryOperandIndexToOperandIndex(*v1,v2);
  lua_pushnumber(L, r);
  return 1;
}
int ins_memory_operand_is_read (lua_State *L) {
  INS* v1 = check_ins(L,1);
  UINT32 v2 = lua_tonumber(L,2);
  BOOL r = INS_MemoryOperandIsRead(*v1,v2);
  lua_pushboolean(L, r);
  return 1;
}
int ins_is_r_d_t_s_c (lua_State *L) {
  INS* v1 = check_ins(L,1);
  BOOL r = INS_IsRDTSC(*v1);
  lua_pushboolean(L, r);
  return 1;
}
int ins_get_far_pointer (lua_State *L) {
  INS* v1 = check_ins(L,1);
  UINT16 v2 = lua_tonumber(L,2);
  UINT32 v3 = lua_tonumber(L,3);
   INS_GetFarPointer(*v1,v2,v3);
  return 0;
}
int ins_operand_size_prefix (lua_State *L) {
  INS* v1 = check_ins(L,1);
  BOOL r = INS_OperandSizePrefix(*v1);
  lua_pushboolean(L, r);
  return 1;
}
int ins_is_mov_full_reg_reg_same (lua_State *L) {
  INS* v1 = check_ins(L,1);
  BOOL r = INS_IsMovFullRegRegSame(*v1);
  lua_pushboolean(L, r);
  return 1;
}
int ins_operand_written_only (lua_State *L) {
  INS* v1 = check_ins(L,1);
  UINT32 v2 = lua_tonumber(L,2);
  BOOL r = INS_OperandWrittenOnly(*v1,v2);
  lua_pushboolean(L, r);
  return 1;
}
int ins_is_sysenter (lua_State *L) {
  INS* v1 = check_ins(L,1);
  BOOL r = INS_IsSysenter(*v1);
  lua_pushboolean(L, r);
  return 1;
}
int ins_is_syscall (lua_State *L) {
  INS* v1 = check_ins(L,1);
  BOOL r = INS_IsSyscall(*v1);
  lua_pushboolean(L, r);
  return 1;
}
int ins_delete (lua_State *L) {
  INS* v1 = check_ins(L,1);
   INS_Delete(*v1);
  return 0;
}
int ins_is_stringop (lua_State *L) {
  INS* v1 = check_ins(L,1);
  BOOL r = INS_IsStringop(*v1);
  lua_pushboolean(L, r);
  return 1;
}
int ins_has_real_rep (lua_State *L) {
  INS* v1 = check_ins(L,1);
  BOOL r = INS_HasRealRep(*v1);
  lua_pushboolean(L, r);
  return 1;
}
int ins_is_stack_write (lua_State *L) {
  INS* v1 = check_ins(L,1);
  BOOL r = INS_IsStackWrite(*v1);
  lua_pushboolean(L, r);
  return 1;
}
int ins_operand_is_reg (lua_State *L) {
  INS* v1 = check_ins(L,1);
  UINT32 v2 = lua_tonumber(L,2);
  BOOL r = INS_OperandIsReg(*v1,v2);
  lua_pushboolean(L, r);
  return 1;
}
int ins_is_procedure_call (lua_State *L) {
  INS* v1 = check_ins(L,1);
  BOOL r = INS_IsProcedureCall(*v1);
  lua_pushboolean(L, r);
  return 1;
}
int ins_memory_operand_size (lua_State *L) {
  INS* v1 = check_ins(L,1);
  UINT32 v2 = lua_tonumber(L,2);
  USIZE r = INS_MemoryOperandSize(*v1,v2);
  lua_pushnumber(L, r);
  return 1;
}
int ins_is_pc_materialization (lua_State *L) {
  INS* v1 = check_ins(L,1);
  BOOL r = INS_IsPcMaterialization(*v1);
  lua_pushboolean(L, r);
  return 1;
}
int ins_memory_operand_count (lua_State *L) {
  INS* v1 = check_ins(L,1);
  UINT32 r = INS_MemoryOperandCount(*v1);
  lua_pushnumber(L, r);
  return 1;
}
int ins_segment_reg_prefix (lua_State *L) {
  INS* v1 = check_ins(L,1);
  string r = lookup_reg_to_string(L,INS_SegmentRegPrefix(*v1));
  lua_pushstring(L, r.c_str());
  return 1;
}
int ins_rtn (lua_State *L) {
  INS* v1 = check_ins(L,1);
  RTN_to_lua(L, INS_Rtn(*v1));
  return 1;
}
int ins_is_direct_branch_or_call (lua_State *L) {
  INS* v1 = check_ins(L,1);
  BOOL r = INS_IsDirectBranchOrCall(*v1);
  lua_pushboolean(L, r);
  return 1;
}
int ins_max_num_w_regs (lua_State *L) {
  INS* v1 = check_ins(L,1);
  UINT32 r = INS_MaxNumWRegs(*v1);
  lua_pushnumber(L, r);
  return 1;
}
int ins_category (lua_State *L) {
  INS* v1 = check_ins(L,1);
  INT32 r = INS_Category(*v1);
  lua_pushnumber(L, r);
  return 1;
}
int ins_next (lua_State *L) {
  INS* v1 = check_ins(L,1);
  INS_to_lua(L, INS_Next(*v1));
  return 1;
}
int ins_is_atomic_update (lua_State *L) {
  INS* v1 = check_ins(L,1);
  BOOL r = INS_IsAtomicUpdate(*v1);
  lua_pushboolean(L, r);
  return 1;
}
int ins_is_far_ret (lua_State *L) {
  INS* v1 = check_ins(L,1);
  BOOL r = INS_IsFarRet(*v1);
  lua_pushboolean(L, r);
  return 1;
}
int ins_operand_reg (lua_State *L) {
  INS* v1 = check_ins(L,1);
  UINT32 v2 = lua_tonumber(L,2);
  string r = lookup_reg_to_string(L,INS_OperandReg(*v1,v2));
  lua_pushstring(L, r.c_str());
  return 1;
}
int ins_memory_displacement (lua_State *L) {
  INS* v1 = check_ins(L,1);
  ADDRDELTA r = INS_MemoryDisplacement(*v1);
  lua_pushnumber(L, r);
  return 1;
}
int ins_disassemble (lua_State *L) {
  INS* v1 = check_ins(L,1);
  string r = INS_Disassemble(*v1);
  lua_pushstring(L, r.c_str());
  return 1;
}
int ins_is_interrupt (lua_State *L) {
  INS* v1 = check_ins(L,1);
  BOOL r = INS_IsInterrupt(*v1);
  lua_pushboolean(L, r);
  return 1;
}
int ins_is_direct_call (lua_State *L) {
  INS* v1 = check_ins(L,1);
  BOOL r = INS_IsDirectCall(*v1);
  lua_pushboolean(L, r);
  return 1;
}
int ins_operand_name_id (lua_State *L) {
  INS* v1 = check_ins(L,1);
  UINT32 v2 = lua_tonumber(L,2);
  UINT32 r = INS_OperandNameId(*v1,v2);
  lua_pushnumber(L, r);
  return 1;
}
int ins_reg_r_contain (lua_State *L) {
  INS* v1 = check_ins(L,1);
  REG v2 = lookup_string_to_reg(L,lua_tostring(L,2));
  BOOL r = INS_RegRContain(*v1,v2);
  lua_pushboolean(L, r);
  return 1;
}
int ins_operand_read_and_written (lua_State *L) {
  INS* v1 = check_ins(L,1);
  UINT32 v2 = lua_tonumber(L,2);
  BOOL r = INS_OperandReadAndWritten(*v1,v2);
  lua_pushboolean(L, r);
  return 1;
}
int ins_next_address (lua_State *L) {
  INS* v1 = check_ins(L,1);
  ADDRINT r = INS_NextAddress(*v1);
  lua_pushnumber(L, r);
  return 1;
}
int ins_reg_w (lua_State *L) {
  INS* v1 = check_ins(L,1);
  UINT32 v2 = lua_tonumber(L,2);
  string r = lookup_reg_to_string(L,INS_RegW(*v1,v2));
  lua_pushstring(L, r.c_str());
  return 1;
}
int ins_has_fall_through (lua_State *L) {
  INS* v1 = check_ins(L,1);
  BOOL r = INS_HasFallThrough(*v1);
  lua_pushboolean(L, r);
  return 1;
}
int ins_is_ip_rel_read (lua_State *L) {
  INS* v1 = check_ins(L,1);
  BOOL r = INS_IsIpRelRead(*v1);
  lua_pushboolean(L, r);
  return 1;
}
int ins_memory_scale (lua_State *L) {
  INS* v1 = check_ins(L,1);
  UINT32 r = INS_MemoryScale(*v1);
  lua_pushnumber(L, r);
  return 1;
}
int ins_operand_memory_base_reg (lua_State *L) {
  INS* v1 = check_ins(L,1);
  UINT32 v2 = lua_tonumber(L,2);
  string r = lookup_reg_to_string(L,INS_OperandMemoryBaseReg(*v1,v2));
  lua_pushstring(L, r.c_str());
  return 1;
}
int ins_operand_is_implicit (lua_State *L) {
  INS* v1 = check_ins(L,1);
  UINT32 v2 = lua_tonumber(L,2);
  BOOL r = INS_OperandIsImplicit(*v1,v2);
  lua_pushboolean(L, r);
  return 1;
}
int ins_is_direct_far_jump (lua_State *L) {
  INS* v1 = check_ins(L,1);
  BOOL r = INS_IsDirectFarJump(*v1);
  lua_pushboolean(L, r);
  return 1;
}
int ins_seg_prefix_is_memory_read (lua_State *L) {
  INS* v1 = check_ins(L,1);
  BOOL r = INS_SegPrefixIsMemoryRead(*v1);
  lua_pushboolean(L, r);
  return 1;
}
int ins_is_branch (lua_State *L) {
  INS* v1 = check_ins(L,1);
  BOOL r = INS_IsBranch(*v1);
  lua_pushboolean(L, r);
  return 1;
}
int ins_operand_is_address_generator (lua_State *L) {
  INS* v1 = check_ins(L,1);
  UINT32 v2 = lua_tonumber(L,2);
  BOOL r = INS_OperandIsAddressGenerator(*v1,v2);
  lua_pushboolean(L, r);
  return 1;
}
int ins_effective_address_width (lua_State *L) {
  INS* v1 = check_ins(L,1);
  UINT32 r = INS_EffectiveAddressWidth(*v1);
  lua_pushnumber(L, r);
  return 1;
}
int ins_memory_read_size (lua_State *L) {
  INS* v1 = check_ins(L,1);
  USIZE r = INS_MemoryReadSize(*v1);
  lua_pushnumber(L, r);
  return 1;
}
int ins_is_memory_write (lua_State *L) {
  INS* v1 = check_ins(L,1);
  BOOL r = INS_IsMemoryWrite(*v1);
  lua_pushboolean(L, r);
  return 1;
}
int ins_operand_memory_index_reg (lua_State *L) {
  INS* v1 = check_ins(L,1);
  UINT32 v2 = lua_tonumber(L,2);
  string r = lookup_reg_to_string(L,INS_OperandMemoryIndexReg(*v1,v2));
  lua_pushstring(L, r.c_str());
  return 1;
}
int ins_change_reg (lua_State *L) {
  INS* v1 = check_ins(L,1);
  REG v2 = lookup_string_to_reg(L,lua_tostring(L,2));
  REG v3 = lookup_string_to_reg(L,lua_tostring(L,3));
  BOOL v4 = lua_toboolean(L,4);
  BOOL r = INS_ChangeReg(*v1,v2,v3,v4);
  lua_pushboolean(L, r);
  return 1;
}
int ins_is_mov (lua_State *L) {
  INS* v1 = check_ins(L,1);
  BOOL r = INS_IsMov(*v1);
  lua_pushboolean(L, r);
  return 1;
}
int ins_operand_is_fixed_memop (lua_State *L) {
  INS* v1 = check_ins(L,1);
  UINT32 v2 = lua_tonumber(L,2);
  BOOL r = INS_OperandIsFixedMemop(*v1,v2);
  lua_pushboolean(L, r);
  return 1;
}
int ins_operand_is_memory (lua_State *L) {
  INS* v1 = check_ins(L,1);
  UINT32 v2 = lua_tonumber(L,2);
  BOOL r = INS_OperandIsMemory(*v1,v2);
  lua_pushboolean(L, r);
  return 1;
}
int ins_branch_not_taken_prefix (lua_State *L) {
  INS* v1 = check_ins(L,1);
  BOOL r = INS_BranchNotTakenPrefix(*v1);
  lua_pushboolean(L, r);
  return 1;
}
int ins_is_lea (lua_State *L) {
  INS* v1 = check_ins(L,1);
  BOOL r = INS_IsLea(*v1);
  lua_pushboolean(L, r);
  return 1;
}
int ins_operand_is_branch_displacement (lua_State *L) {
  INS* v1 = check_ins(L,1);
  UINT32 v2 = lua_tonumber(L,2);
  BOOL r = INS_OperandIsBranchDisplacement(*v1,v2);
  lua_pushboolean(L, r);
  return 1;
}
int ins_size (lua_State *L) {
  INS* v1 = check_ins(L,1);
  USIZE r = INS_Size(*v1);
  lua_pushnumber(L, r);
  return 1;
}
int ins_operand_read_only (lua_State *L) {
  INS* v1 = check_ins(L,1);
  UINT32 v2 = lua_tonumber(L,2);
  BOOL r = INS_OperandReadOnly(*v1,v2);
  lua_pushboolean(L, r);
  return 1;
}
int ins_extension (lua_State *L) {
  INS* v1 = check_ins(L,1);
  INT32 r = INS_Extension(*v1);
  lua_pushnumber(L, r);
  return 1;
}
int ins_segment_prefix (lua_State *L) {
  INS* v1 = check_ins(L,1);
  BOOL r = INS_SegmentPrefix(*v1);
  lua_pushboolean(L, r);
  return 1;
}
int ins_memory_write_size (lua_State *L) {
  INS* v1 = check_ins(L,1);
  USIZE r = INS_MemoryWriteSize(*v1);
  lua_pushnumber(L, r);
  return 1;
}
int ins_is_call (lua_State *L) {
  INS* v1 = check_ins(L,1);
  BOOL r = INS_IsCall(*v1);
  lua_pushboolean(L, r);
  return 1;
}
int ins_syscall_std (lua_State *L) {
  INS* v1 = check_ins(L,1);
  string r = lookup_syscall_standard_to_string(L,INS_SyscallStd(*v1));
  lua_pushstring(L, r.c_str());
  return 1;
}
int ins_reg_w_contain (lua_State *L) {
  INS* v1 = check_ins(L,1);
  REG v2 = lookup_string_to_reg(L,lua_tostring(L,2));
  BOOL r = INS_RegWContain(*v1,v2);
  lua_pushboolean(L, r);
  return 1;
}
int ins_max_num_r_regs (lua_State *L) {
  INS* v1 = check_ins(L,1);
  UINT32 r = INS_MaxNumRRegs(*v1);
  lua_pushnumber(L, r);
  return 1;
}
int ins_is_far_call (lua_State *L) {
  INS* v1 = check_ins(L,1);
  BOOL r = INS_IsFarCall(*v1);
  lua_pushboolean(L, r);
  return 1;
}
int ins_memory_index_reg (lua_State *L) {
  INS* v1 = check_ins(L,1);
  string r = lookup_reg_to_string(L,INS_MemoryIndexReg(*v1));
  lua_pushstring(L, r.c_str());
  return 1;
}
int ins_address (lua_State *L) {
  INS* v1 = check_ins(L,1);
  ADDRINT r = INS_Address(*v1);
  lua_pushnumber(L, r);
  return 1;
}
int ins_rep_prefix (lua_State *L) {
  INS* v1 = check_ins(L,1);
  BOOL r = INS_RepPrefix(*v1);
  lua_pushboolean(L, r);
  return 1;
}
int ins_is_direct_branch (lua_State *L) {
  INS* v1 = check_ins(L,1);
  BOOL r = INS_IsDirectBranch(*v1);
  lua_pushboolean(L, r);
  return 1;
}
int ins_operand_width (lua_State *L) {
  INS* v1 = check_ins(L,1);
  UINT32 v2 = lua_tonumber(L,2);
  UINT32 r = INS_OperandWidth(*v1,v2);
  lua_pushnumber(L, r);
  return 1;
}
int ins_lock_prefix (lua_State *L) {
  INS* v1 = check_ins(L,1);
  BOOL r = INS_LockPrefix(*v1);
  lua_pushboolean(L, r);
  return 1;
}
int ins_is_nop (lua_State *L) {
  INS* v1 = check_ins(L,1);
  BOOL r = INS_IsNop(*v1);
  lua_pushboolean(L, r);
  return 1;
}
int ins_rep_count_register (lua_State *L) {
  INS* v1 = check_ins(L,1);
  string r = lookup_reg_to_string(L,INS_RepCountRegister(*v1));
  lua_pushstring(L, r.c_str());
  return 1;
}
int ins_is_prefetch (lua_State *L) {
  INS* v1 = check_ins(L,1);
  BOOL r = INS_IsPrefetch(*v1);
  lua_pushboolean(L, r);
  return 1;
}
int ins_memory_base_reg (lua_State *L) {
  INS* v1 = check_ins(L,1);
  string r = lookup_reg_to_string(L,INS_MemoryBaseReg(*v1));
  lua_pushstring(L, r.c_str());
  return 1;
}
int ins_branch_taken_prefix (lua_State *L) {
  INS* v1 = check_ins(L,1);
  BOOL r = INS_BranchTakenPrefix(*v1);
  lua_pushboolean(L, r);
  return 1;
}
int ins_operand_is_immediate (lua_State *L) {
  INS* v1 = check_ins(L,1);
  UINT32 v2 = lua_tonumber(L,2);
  BOOL r = INS_OperandIsImmediate(*v1,v2);
  lua_pushboolean(L, r);
  return 1;
}
int ins_full_reg_w_contain (lua_State *L) {
  INS* v1 = check_ins(L,1);
  REG v2 = lookup_string_to_reg(L,lua_tostring(L,2));
  BOOL r = INS_FullRegWContain(*v1,v2);
  lua_pushboolean(L, r);
  return 1;
}
int ins_is_stack_read (lua_State *L) {
  INS* v1 = check_ins(L,1);
  BOOL r = INS_IsStackRead(*v1);
  lua_pushboolean(L, r);
  return 1;
}
int ins_is_far_jump (lua_State *L) {
  INS* v1 = check_ins(L,1);
  BOOL r = INS_IsFarJump(*v1);
  lua_pushboolean(L, r);
  return 1;
}
int ins_is_branch_or_call (lua_State *L) {
  INS* v1 = check_ins(L,1);
  BOOL r = INS_IsBranchOrCall(*v1);
  lua_pushboolean(L, r);
  return 1;
}
int ins_operand_memory_displacement (lua_State *L) {
  INS* v1 = check_ins(L,1);
  UINT32 v2 = lua_tonumber(L,2);
  ADDRDELTA r = INS_OperandMemoryDisplacement(*v1,v2);
  lua_pushnumber(L, r);
  return 1;
}
int ins_memory_operand_is_written (lua_State *L) {
  INS* v1 = check_ins(L,1);
  UINT32 v2 = lua_tonumber(L,2);
  BOOL r = INS_MemoryOperandIsWritten(*v1,v2);
  lua_pushboolean(L, r);
  return 1;
}
int ins_is_original (lua_State *L) {
  INS* v1 = check_ins(L,1);
  BOOL r = INS_IsOriginal(*v1);
  lua_pushboolean(L, r);
  return 1;
}
int ins_stutters (lua_State *L) {
  INS* v1 = check_ins(L,1);
  BOOL r = INS_Stutters(*v1);
  lua_pushboolean(L, r);
  return 1;
}
int ins_seg_prefix_is_memory_write (lua_State *L) {
  INS* v1 = check_ins(L,1);
  BOOL r = INS_SegPrefixIsMemoryWrite(*v1);
  lua_pushboolean(L, r);
  return 1;
}
int ins_is_ip_rel_write (lua_State *L) {
  INS* v1 = check_ins(L,1);
  BOOL r = INS_IsIpRelWrite(*v1);
  lua_pushboolean(L, r);
  return 1;
}
int ins_insert_direct_jump (lua_State *L) {
  INS* v1 = check_ins(L,1);
  IPOINT v2 = lookup_string_to_ipoint(L,lua_tostring(L,2));
  ADDRINT v3 = lua_tonumber(L,3);
   INS_InsertDirectJump(*v1,v2,v3);
  return 0;
}
int ins_operand_read (lua_State *L) {
  INS* v1 = check_ins(L,1);
  UINT32 v2 = lua_tonumber(L,2);
  BOOL r = INS_OperandRead(*v1,v2);
  lua_pushboolean(L, r);
  return 1;
}
int ins_is_memory_read (lua_State *L) {
  INS* v1 = check_ins(L,1);
  BOOL r = INS_IsMemoryRead(*v1);
  lua_pushboolean(L, r);
  return 1;
}
int ins_repne_prefix (lua_State *L) {
  INS* v1 = check_ins(L,1);
  BOOL r = INS_RepnePrefix(*v1);
  lua_pushboolean(L, r);
  return 1;
}
int ins_prev (lua_State *L) {
  INS* v1 = check_ins(L,1);
  INS_to_lua(L, INS_Prev(*v1));
  return 1;
}
int ins_rewrite_memory_operand (lua_State *L) {
  INS* v1 = check_ins(L,1);
  UINT32 v2 = lua_tonumber(L,2);
  REG v3 = lookup_string_to_reg(L,lua_tostring(L,3));
   INS_RewriteMemoryOperand(*v1,v2,v3);
  return 0;
}
int ins_is_indirect_branch_or_call (lua_State *L) {
  INS* v1 = check_ins(L,1);
  BOOL r = INS_IsIndirectBranchOrCall(*v1);
  lua_pushboolean(L, r);
  return 1;
}
int ins_direct_branch_or_call_target_address (lua_State *L) {
  INS* v1 = check_ins(L,1);
  ADDRINT r = INS_DirectBranchOrCallTargetAddress(*v1);
  lua_pushnumber(L, r);
  return 1;
}
int ins_is_halt (lua_State *L) {
  INS* v1 = check_ins(L,1);
  BOOL r = INS_IsHalt(*v1);
  lua_pushboolean(L, r);
  return 1;
}
int ins_is_xchg (lua_State *L) {
  INS* v1 = check_ins(L,1);
  BOOL r = INS_IsXchg(*v1);
  lua_pushboolean(L, r);
  return 1;
}
int ins_is_ret (lua_State *L) {
  INS* v1 = check_ins(L,1);
  BOOL r = INS_IsRet(*v1);
  lua_pushboolean(L, r);
  return 1;
}
