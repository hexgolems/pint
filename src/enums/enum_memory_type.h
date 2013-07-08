#ifndef __PINT_ENUM_MEMORY_TYPE__
#define __PINT_ENUM_MEMORY_TYPE__
extern "C" {
#include "lua.h"
}
#include "pin.H"
MEMORY_TYPE lookup_string_to_memory_type(lua_State* L,string str);
string lookup_memory_type_to_string(lua_State* L,MEMORY_TYPE);
#endif
