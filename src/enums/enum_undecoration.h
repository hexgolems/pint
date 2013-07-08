#ifndef __PINT_ENUM_UNDECORATION__
#define __PINT_ENUM_UNDECORATION__
extern "C" {
#include "lua.h"
}
#include "pin.H"
UNDECORATION lookup_string_to_undecoration(lua_State* L,string str);
string lookup_undecoration_to_string(lua_State* L,UNDECORATION);
#endif
