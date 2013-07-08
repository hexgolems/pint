#ifndef __PINT_DEFINES__
#define __PINT_DEFINES__
#define AQUIRE_PINTOOL_MUTEX
#define RELEASE_PINTOOL_MUTEX

#include <string>
using namespace std;

#define CALLBACK_TABLE_REGISTRY_INDEX "pintools_wrapper_callbacks"
extern "C" {
    #include <lua.h>
    #include <lauxlib.h>
    #include <lualib.h>
}

string lua_get_string(lua_State* L, int index);
void stackdump(lua_State* l);
#endif
