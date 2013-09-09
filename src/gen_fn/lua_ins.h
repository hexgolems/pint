
#ifndef __PINT_LUA_INS_WRAPPER__
#define __PINT_LUA_INS_WRAPPER__

extern "C" {
    #include <lua.h>
    #include <lauxlib.h>
    #include <lualib.h>
}

#include "pin.H"
#include "lua_ins_instr.h"

int INS_to_lua(lua_State *L, INS ins);
  INS *check_ins (lua_State *L, int);
int luaopen_ins (lua_State *L);

#ifdef TARGET_IA32E
int ins_has_property (lua_State *L) ;
#endif

int ins_operand_memory_scale (lua_State *L) ;
int ins_is_mask_mov (lua_State *L) ;
int ins_is_i_ret (lua_State *L) ;
int ins_is_predicated (lua_State *L) ;
int ins_is_sysret (lua_State *L) ;
int ins_insert_indirect_jump (lua_State *L) ;
int ins_address_size_prefix (lua_State *L) ;
int ins_mnemonic (lua_State *L) ;
int ins_operand_immediate (lua_State *L) ;
int ins_operand_count (lua_State *L) ;
int ins_operand_written (lua_State *L) ;
int ins_has_memory_read2 (lua_State *L) ;
int ins_is_sub (lua_State *L) ;
int ins_full_reg_r_contain (lua_State *L) ;
int ins_reg_r (lua_State *L) ;
int ins_operand_memory_segment_reg (lua_State *L) ;
int ins_memory_operand_index_to_operand_index (lua_State *L) ;
int ins_memory_operand_is_read (lua_State *L) ;
int ins_is_r_d_t_s_c (lua_State *L) ;
int ins_get_far_pointer (lua_State *L) ;
int ins_operand_size_prefix (lua_State *L) ;
int ins_is_mov_full_reg_reg_same (lua_State *L) ;
int ins_operand_written_only (lua_State *L) ;
int ins_is_sysenter (lua_State *L) ;
int ins_is_syscall (lua_State *L) ;
int ins_delete (lua_State *L) ;
int ins_is_stringop (lua_State *L) ;
int ins_has_real_rep (lua_State *L) ;
int ins_is_stack_write (lua_State *L) ;
int ins_operand_is_reg (lua_State *L) ;
int ins_is_procedure_call (lua_State *L) ;
int ins_memory_operand_size (lua_State *L) ;
int ins_is_pc_materialization (lua_State *L) ;
int ins_memory_operand_count (lua_State *L) ;
int ins_segment_reg_prefix (lua_State *L) ;
int ins_rtn (lua_State *L) ;
int ins_is_direct_branch_or_call (lua_State *L) ;
int ins_max_num_w_regs (lua_State *L) ;
int ins_category (lua_State *L) ;
int ins_next (lua_State *L) ;
int ins_is_atomic_update (lua_State *L) ;
int ins_is_far_ret (lua_State *L) ;
int ins_operand_reg (lua_State *L) ;
int ins_memory_displacement (lua_State *L) ;
int ins_disassemble (lua_State *L) ;
int ins_is_interrupt (lua_State *L) ;
int ins_is_direct_call (lua_State *L) ;
int ins_operand_name_id (lua_State *L) ;
int ins_reg_r_contain (lua_State *L) ;
int ins_operand_read_and_written (lua_State *L) ;
int ins_next_address (lua_State *L) ;
int ins_reg_w (lua_State *L) ;
int ins_has_fall_through (lua_State *L) ;
int ins_is_ip_rel_read (lua_State *L) ;
int ins_memory_scale (lua_State *L) ;
int ins_operand_memory_base_reg (lua_State *L) ;
int ins_operand_is_implicit (lua_State *L) ;
int ins_is_direct_far_jump (lua_State *L) ;
int ins_seg_prefix_is_memory_read (lua_State *L) ;
int ins_is_branch (lua_State *L) ;
int ins_operand_is_address_generator (lua_State *L) ;
int ins_effective_address_width (lua_State *L) ;
int ins_memory_read_size (lua_State *L) ;
int ins_is_memory_write (lua_State *L) ;
int ins_operand_memory_index_reg (lua_State *L) ;
int ins_change_reg (lua_State *L) ;
int ins_is_mov (lua_State *L) ;
int ins_operand_is_fixed_memop (lua_State *L) ;
int ins_operand_is_memory (lua_State *L) ;
int ins_branch_not_taken_prefix (lua_State *L) ;
int ins_is_lea (lua_State *L) ;
int ins_operand_is_branch_displacement (lua_State *L) ;
int ins_size (lua_State *L) ;
int ins_operand_read_only (lua_State *L) ;
int ins_extension (lua_State *L) ;
int ins_segment_prefix (lua_State *L) ;
int ins_memory_write_size (lua_State *L) ;
int ins_is_call (lua_State *L) ;
int ins_syscall_std (lua_State *L) ;
int ins_reg_w_contain (lua_State *L) ;
int ins_max_num_r_regs (lua_State *L) ;
int ins_is_far_call (lua_State *L) ;
int ins_memory_index_reg (lua_State *L) ;
int ins_address (lua_State *L) ;
int ins_rep_prefix (lua_State *L) ;
int ins_is_direct_branch (lua_State *L) ;
int ins_operand_width (lua_State *L) ;
int ins_lock_prefix (lua_State *L) ;
int ins_is_nop (lua_State *L) ;
int ins_rep_count_register (lua_State *L) ;
int ins_is_prefetch (lua_State *L) ;
int ins_memory_base_reg (lua_State *L) ;
int ins_branch_taken_prefix (lua_State *L) ;
int ins_operand_is_immediate (lua_State *L) ;
int ins_full_reg_w_contain (lua_State *L) ;
int ins_is_stack_read (lua_State *L) ;
int ins_is_far_jump (lua_State *L) ;
int ins_is_branch_or_call (lua_State *L) ;
int ins_operand_memory_displacement (lua_State *L) ;
int ins_memory_operand_is_written (lua_State *L) ;
int ins_is_original (lua_State *L) ;
int ins_stutters (lua_State *L) ;
int ins_seg_prefix_is_memory_write (lua_State *L) ;
int ins_is_ip_rel_write (lua_State *L) ;
int ins_insert_direct_jump (lua_State *L) ;
int ins_operand_read (lua_State *L) ;
int ins_is_memory_read (lua_State *L) ;
int ins_repne_prefix (lua_State *L) ;
int ins_prev (lua_State *L) ;
int ins_rewrite_memory_operand (lua_State *L) ;
int ins_is_indirect_branch_or_call (lua_State *L) ;
int ins_direct_branch_or_call_target_address (lua_State *L) ;
int ins_is_halt (lua_State *L) ;
int ins_is_xchg (lua_State *L) ;
int ins_is_ret (lua_State *L) ;

const struct luaL_reg ins_lib_m [] = {
  {"add_callback",add_ins_call},
  #ifdef TARGET_IA32E
  {"has_property",ins_has_property},
  #endif
  {"operand_memory_scale",ins_operand_memory_scale},
  {"is_mask_mov",ins_is_mask_mov},
  {"is_i_ret",ins_is_i_ret},
  {"is_predicated",ins_is_predicated},
  {"is_sysret",ins_is_sysret},
  {"insert_indirect_jump",ins_insert_indirect_jump},
  {"address_size_prefix",ins_address_size_prefix},
  {"mnemonic",ins_mnemonic},
  {"operand_immediate",ins_operand_immediate},
  {"operand_count",ins_operand_count},
  {"operand_written",ins_operand_written},
  {"has_memory_read2",ins_has_memory_read2},
  {"is_sub",ins_is_sub},
  {"full_reg_r_contain",ins_full_reg_r_contain},
  {"reg_r",ins_reg_r},
  {"operand_memory_segment_reg",ins_operand_memory_segment_reg},
  {"memory_operand_index_to_operand_index",ins_memory_operand_index_to_operand_index},
  {"memory_operand_is_read",ins_memory_operand_is_read},
  {"is_rdtsc",ins_is_r_d_t_s_c},
  {"get_far_pointer",ins_get_far_pointer},
  {"operand_size_prefix",ins_operand_size_prefix},
  {"is_mov_full_reg_reg_same",ins_is_mov_full_reg_reg_same},
  {"operand_written_only",ins_operand_written_only},
  {"is_sysenter",ins_is_sysenter},
  {"is_syscall",ins_is_syscall},
  {"delete",ins_delete},
  {"is_stringop",ins_is_stringop},
  {"has_real_rep",ins_has_real_rep},
  {"is_stack_write",ins_is_stack_write},
  {"operand_is_reg",ins_operand_is_reg},
  {"is_procedure_call",ins_is_procedure_call},
  {"memory_operand_size",ins_memory_operand_size},
  {"is_pc_materialization",ins_is_pc_materialization},
  {"memory_operand_count",ins_memory_operand_count},
  {"segment_reg_prefix",ins_segment_reg_prefix},
  {"rtn",ins_rtn},
  {"is_direct_branch_or_call",ins_is_direct_branch_or_call},
  {"max_num_w_regs",ins_max_num_w_regs},
  {"category",ins_category},
  {"next",ins_next},
  {"is_atomic_update",ins_is_atomic_update},
  {"is_far_ret",ins_is_far_ret},
  {"operand_reg",ins_operand_reg},
  {"memory_displacement",ins_memory_displacement},
  {"disassemble",ins_disassemble},
  {"is_interrupt",ins_is_interrupt},
  {"is_direct_call",ins_is_direct_call},
  {"operand_name_id",ins_operand_name_id},
  {"reg_r_contain",ins_reg_r_contain},
  {"operand_read_and_written",ins_operand_read_and_written},
  {"next_address",ins_next_address},
  {"reg_w",ins_reg_w},
  {"has_fall_through",ins_has_fall_through},
  {"is_ip_rel_read",ins_is_ip_rel_read},
  {"memory_scale",ins_memory_scale},
  {"operand_memory_base_reg",ins_operand_memory_base_reg},
  {"operand_is_implicit",ins_operand_is_implicit},
  {"is_direct_far_jump",ins_is_direct_far_jump},
  {"seg_prefix_is_memory_read",ins_seg_prefix_is_memory_read},
  {"is_branch",ins_is_branch},
  {"operand_is_address_generator",ins_operand_is_address_generator},
  {"effective_address_width",ins_effective_address_width},
  {"memory_read_size",ins_memory_read_size},
  {"is_memory_write",ins_is_memory_write},
  {"operand_memory_index_reg",ins_operand_memory_index_reg},
  {"change_reg",ins_change_reg},
  {"is_mov",ins_is_mov},
  {"operand_is_fixed_memop",ins_operand_is_fixed_memop},
  {"operand_is_memory",ins_operand_is_memory},
  {"branch_not_taken_prefix",ins_branch_not_taken_prefix},
  {"is_lea",ins_is_lea},
  {"operand_is_branch_displacement",ins_operand_is_branch_displacement},
  {"size",ins_size},
  {"operand_read_only",ins_operand_read_only},
  {"extension",ins_extension},
  {"segment_prefix",ins_segment_prefix},
  {"memory_write_size",ins_memory_write_size},
  {"is_call",ins_is_call},
  {"syscall_std",ins_syscall_std},
  {"reg_w_contain",ins_reg_w_contain},
  {"max_num_r_regs",ins_max_num_r_regs},
  {"is_far_call",ins_is_far_call},
  {"memory_index_reg",ins_memory_index_reg},
  {"address",ins_address},
  {"rep_prefix",ins_rep_prefix},
  {"is_direct_branch",ins_is_direct_branch},
  {"operand_width",ins_operand_width},
  {"lock_prefix",ins_lock_prefix},
  {"is_nop",ins_is_nop},
  {"rep_count_register",ins_rep_count_register},
  {"is_prefetch",ins_is_prefetch},
  {"memory_base_reg",ins_memory_base_reg},
  {"branch_taken_prefix",ins_branch_taken_prefix},
  {"operand_is_immediate",ins_operand_is_immediate},
  {"full_reg_w_contain",ins_full_reg_w_contain},
  {"is_stack_read",ins_is_stack_read},
  {"is_far_jump",ins_is_far_jump},
  {"is_branch_or_call",ins_is_branch_or_call},
  {"operand_memory_displacement",ins_operand_memory_displacement},
  {"memory_operand_is_written",ins_memory_operand_is_written},
  {"is_original",ins_is_original},
  {"stutters",ins_stutters},
  {"seg_prefix_is_memory_write",ins_seg_prefix_is_memory_write},
  {"is_ip_rel_write",ins_is_ip_rel_write},
  {"insert_direct_jump",ins_insert_direct_jump},
  {"operand_read",ins_operand_read},
  {"is_memory_read",ins_is_memory_read},
  {"repne_prefix",ins_repne_prefix},
  {"prev",ins_prev},
  {"rewrite_memory_operand",ins_rewrite_memory_operand},
  {"is_indirect_branch_or_call",ins_is_indirect_branch_or_call},
  {"direct_branch_or_call_target_address",ins_direct_branch_or_call_target_address},
  {"is_halt",ins_is_halt},
  {"is_xchg",ins_is_xchg},
  {"is_ret",ins_is_ret},
  {NULL, NULL}
};

const struct luaL_reg ins_lib [] = {
  #ifdef TARGET_IA32E
    {"has_property",ins_has_property},
  #endif
  {"operand_memory_scale",ins_operand_memory_scale},
  {"is_mask_mov",ins_is_mask_mov},
  {"is_i_ret",ins_is_i_ret},
  {"is_predicated",ins_is_predicated},
  {"is_sysret",ins_is_sysret},
  {"insert_indirect_jump",ins_insert_indirect_jump},
  {"address_size_prefix",ins_address_size_prefix},
  {"mnemonic",ins_mnemonic},
  {"operand_immediate",ins_operand_immediate},
  {"operand_count",ins_operand_count},
  {"operand_written",ins_operand_written},
  {"has_memory_read2",ins_has_memory_read2},
  {"is_sub",ins_is_sub},
  {"full_reg_r_contain",ins_full_reg_r_contain},
  {"reg_r",ins_reg_r},
  {"operand_memory_segment_reg",ins_operand_memory_segment_reg},
  {"memory_operand_index_to_operand_index",ins_memory_operand_index_to_operand_index},
  {"memory_operand_is_read",ins_memory_operand_is_read},
  {"is_r_d_t_s_c",ins_is_r_d_t_s_c},
  {"get_far_pointer",ins_get_far_pointer},
  {"operand_size_prefix",ins_operand_size_prefix},
  {"is_mov_full_reg_reg_same",ins_is_mov_full_reg_reg_same},
  {"operand_written_only",ins_operand_written_only},
  {"is_sysenter",ins_is_sysenter},
  {"is_syscall",ins_is_syscall},
  {"delete",ins_delete},
  {"is_stringop",ins_is_stringop},
  {"has_real_rep",ins_has_real_rep},
  {"is_stack_write",ins_is_stack_write},
  {"operand_is_reg",ins_operand_is_reg},
  {"is_procedure_call",ins_is_procedure_call},
  {"memory_operand_size",ins_memory_operand_size},
  {"is_pc_materialization",ins_is_pc_materialization},
  {"memory_operand_count",ins_memory_operand_count},
  {"segment_reg_prefix",ins_segment_reg_prefix},
  {"rtn",ins_rtn},
  {"is_direct_branch_or_call",ins_is_direct_branch_or_call},
  {"max_num_w_regs",ins_max_num_w_regs},
  {"category",ins_category},
  {"next",ins_next},
  {"is_atomic_update",ins_is_atomic_update},
  {"is_far_ret",ins_is_far_ret},
  {"operand_reg",ins_operand_reg},
  {"memory_displacement",ins_memory_displacement},
  {"disassemble",ins_disassemble},
  {"is_interrupt",ins_is_interrupt},
  {"is_direct_call",ins_is_direct_call},
  {"operand_name_id",ins_operand_name_id},
  {"reg_r_contain",ins_reg_r_contain},
  {"operand_read_and_written",ins_operand_read_and_written},
  {"next_address",ins_next_address},
  {"reg_w",ins_reg_w},
  {"has_fall_through",ins_has_fall_through},
  {"is_ip_rel_read",ins_is_ip_rel_read},
  {"memory_scale",ins_memory_scale},
  {"operand_memory_base_reg",ins_operand_memory_base_reg},
  {"operand_is_implicit",ins_operand_is_implicit},
  {"is_direct_far_jump",ins_is_direct_far_jump},
  {"seg_prefix_is_memory_read",ins_seg_prefix_is_memory_read},
  {"is_branch",ins_is_branch},
  {"operand_is_address_generator",ins_operand_is_address_generator},
  {"effective_address_width",ins_effective_address_width},
  {"memory_read_size",ins_memory_read_size},
  {"is_memory_write",ins_is_memory_write},
  {"operand_memory_index_reg",ins_operand_memory_index_reg},
  {"change_reg",ins_change_reg},
  {"is_mov",ins_is_mov},
  {"operand_is_fixed_memop",ins_operand_is_fixed_memop},
  {"operand_is_memory",ins_operand_is_memory},
  {"branch_not_taken_prefix",ins_branch_not_taken_prefix},
  {"is_lea",ins_is_lea},
  {"operand_is_branch_displacement",ins_operand_is_branch_displacement},
  {"size",ins_size},
  {"operand_read_only",ins_operand_read_only},
  {"extension",ins_extension},
  {"segment_prefix",ins_segment_prefix},
  {"memory_write_size",ins_memory_write_size},
  {"is_call",ins_is_call},
  {"syscall_std",ins_syscall_std},
  {"reg_w_contain",ins_reg_w_contain},
  {"max_num_r_regs",ins_max_num_r_regs},
  {"is_far_call",ins_is_far_call},
  {"memory_index_reg",ins_memory_index_reg},
  {"address",ins_address},
  {"rep_prefix",ins_rep_prefix},
  {"is_direct_branch",ins_is_direct_branch},
  {"operand_width",ins_operand_width},
  {"lock_prefix",ins_lock_prefix},
  {"is_nop",ins_is_nop},
  {"rep_count_register",ins_rep_count_register},
  {"is_prefetch",ins_is_prefetch},
  {"memory_base_reg",ins_memory_base_reg},
  {"branch_taken_prefix",ins_branch_taken_prefix},
  {"operand_is_immediate",ins_operand_is_immediate},
  {"full_reg_w_contain",ins_full_reg_w_contain},
  {"is_stack_read",ins_is_stack_read},
  {"is_far_jump",ins_is_far_jump},
  {"is_branch_or_call",ins_is_branch_or_call},
  {"operand_memory_displacement",ins_operand_memory_displacement},
  {"memory_operand_is_written",ins_memory_operand_is_written},
  {"is_original",ins_is_original},
  {"stutters",ins_stutters},
  {"seg_prefix_is_memory_write",ins_seg_prefix_is_memory_write},
  {"is_ip_rel_write",ins_is_ip_rel_write},
  {"insert_direct_jump",ins_insert_direct_jump},
  {"operand_read",ins_operand_read},
  {"is_memory_read",ins_is_memory_read},
  {"repne_prefix",ins_repne_prefix},
  {"prev",ins_prev},
  {"rewrite_memory_operand",ins_rewrite_memory_operand},
  {"is_indirect_branch_or_call",ins_is_indirect_branch_or_call},
  {"direct_branch_or_call_target_address",ins_direct_branch_or_call_target_address},
  {"is_halt",ins_is_halt},
  {"is_xchg",ins_is_xchg},
  {"is_ret",ins_is_ret},

  {NULL, NULL}
};

#endif
