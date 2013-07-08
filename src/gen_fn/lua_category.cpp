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

#include "../gen_fn/lua_category.h"
#include "lua.h"
#include "pin.H"

extern "C" {
    #include <lua.h>
    #include <lauxlib.h>
    #include <lualib.h>
}
int luaopen_category (lua_State *L) {
  luaL_newmetatable(L, "pin.Category");
  luaL_openlib(L, "Category", category_lib, 0);
  return 1;
}
int category_string_short (lua_State *L) { 
	UINT32 v1 = lua_tonumber(L,1);
	string r = CATEGORY_StringShort(v1);
	lua_pushstring(L, r.c_str());
	return 1;
}
