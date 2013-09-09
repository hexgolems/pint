#ifndef __PINT_ENUM_PREDICATE_IA32__
#define __PINT_ENUM_PREDICATE_IA32__
extern "C" {
#include <lua.h>
}
#include "pin.H"
PREDICATE_IA32 lookup_string_to_predicate_ia32(lua_State* L,string str);
string lookup_predicate_ia32_to_string(lua_State* L,PREDICATE_IA32);
#endif
