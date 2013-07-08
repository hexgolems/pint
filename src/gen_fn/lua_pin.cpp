#include "lua_img.h"
#include "lua_ins.h"
#include "lua_sec.h"
#include "lua_rtn.h"
#include "lua_reg.h"
#include "lua_trace.h"
#include "lua_bbl.h"
#include "lua_sym.h"
#include "../enums/enum_img_type.h"
#include "../enums/enum_memory_type.h"
#include "../enums/enum_syscall_standard.h"
#include "../enums/enum_predicate_ia32.h"
#include "../enums/enum_ins_prop_ipf.h"
#include "../enums/enum_sec_type.h"
#include "../enums/enum_probe_mode.h"
#include "../enums/enum_reg.h"
#include "../enums/enum_reg.h"
#include "../enums/enum_regname.h"
#include "../enums/enum_undecoration.h"
#include "../enums/enum_ipoint.h"
#include "../enums/enum_call_order.h"
#include "../enums/enum_iarg_type.h"

#include "../gen_fn/lua_pin.h"
#include "lua.h"
#include "pin.H"

extern "C" {
    #include <lua.h>
    #include <lauxlib.h>
    #include <lualib.h>
}
int luaopen_pin (lua_State *L) {
  luaL_newmetatable(L, "pin.Pin");
  luaL_openlib(L, "Pin", pin_lib, 0);
  return 1;
}
int pin_set_syntax_x_e_d (lua_State *L) { 
	 PIN_SetSyntaxXED();
	return 0;
}
int pin_set_syntax_intel (lua_State *L) { 
	 PIN_SetSyntaxIntel();
	return 0;
}
int pin_set_syntax_a_t_t (lua_State *L) { 
	 PIN_SetSyntaxATT();
	return 0;
}
int pin_undecorate_symbol_name (lua_State *L) { 
	string v1 = lua_tostring(L,1);
	UNDECORATION v2 = lookup_string_to_undecoration(L,lua_tostring(L,2));
	string r = PIN_UndecorateSymbolName(v1,v2);
	lua_pushstring(L, r.c_str());
	return 1;
}
int pin_claim_tool_register (lua_State *L) { 
	string r = lookup_reg_to_string(L,PIN_ClaimToolRegister());
	lua_pushstring(L, r.c_str());
	return 1;
}
