#ifndef __PINT_ENUM_SYSCALL_STANDARD__
#define __PINT_ENUM_SYSCALL_STANDARD__
extern "C" {
#include <lua.h>
}
#include "pin.H"
SYSCALL_STANDARD lookup_string_to_syscall_standard(lua_State* L,string str);
string lookup_syscall_standard_to_string(lua_State* L,SYSCALL_STANDARD);
#endif
