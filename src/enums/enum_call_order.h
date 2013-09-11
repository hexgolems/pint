#ifndef __PINT_ENUM_CALL_ORDER__
#define __PINT_ENUM_CALL_ORDER__
extern "C" {
#include <lua.h>
}
#include "pin.H"
CALL_ORDER lookup_string_to_call_order(lua_State* L,string str);
string lookup_call_order_to_string(lua_State* L,CALL_ORDER);
#endif
