#ifndef TARGET_IA32 

	#ifndef __PINT_ENUM_INS_PROP_IPF__
	#define __PINT_ENUM_INS_PROP_IPF__
	extern "C" {
	#include <lua.h>
	}
	#include "pin.H"
	INS_PROP_IPF lookup_string_to_ins_prop_ipf(lua_State* L,string str);
	string lookup_ins_prop_ipf_to_string(lua_State* L,INS_PROP_IPF);
	#endif
#endif