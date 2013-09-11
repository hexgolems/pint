#ifndef __PINT_ENUM_REG__
#define __PINT_ENUM_REG__
extern "C" {
#include <lua.h>
}
#include "pin.H"
REG lookup_string_to_reg(lua_State* L,string str);
string lookup_reg_to_string(lua_State* L,REG);
#endif
