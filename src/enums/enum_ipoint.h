#ifndef __PINT_ENUM_IPOINT__
#define __PINT_ENUM_IPOINT__
extern "C" {
#include "lua.h"
}
#include "pin.H"
IPOINT lookup_string_to_ipoint(lua_State* L,string str);
string lookup_ipoint_to_string(lua_State* L,IPOINT);
#endif
