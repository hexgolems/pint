#ifndef __PINT_ENUM_IARG_TYPE__
#define __PINT_ENUM_IARG_TYPE__
extern "C" {
#include "lua.h"
}
#include "pin.H"
IARG_TYPE lookup_string_to_iarg_type(lua_State* L,string str);
string lookup_iarg_type_to_string(lua_State* L,IARG_TYPE);
#endif
