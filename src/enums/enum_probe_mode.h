#ifndef __PINT_ENUM_PROBE_MODE__
#define __PINT_ENUM_PROBE_MODE__
extern "C" {
#include <lua.h>
}
#include "pin.H"
PROBE_MODE lookup_string_to_probe_mode(lua_State* L,string str);
string lookup_probe_mode_to_string(lua_State* L,PROBE_MODE);
#endif
