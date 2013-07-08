#ifndef __PINT_ENUM_SEC_TYPE__
#define __PINT_ENUM_SEC_TYPE__
extern "C" {
#include "lua.h"
}
#include "pin.H"
SEC_TYPE lookup_string_to_sec_type(lua_State* L,string str);
string lookup_sec_type_to_string(lua_State* L,SEC_TYPE);
#endif
