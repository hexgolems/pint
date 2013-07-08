#ifndef __PINT_ENUM_REGNAME__
#define __PINT_ENUM_REGNAME__
extern "C" {
#include "lua.h"
}
#include "pin.H"
REGNAME lookup_string_to_regname(lua_State* L,string str);
string lookup_regname_to_string(lua_State* L,REGNAME);
#endif
