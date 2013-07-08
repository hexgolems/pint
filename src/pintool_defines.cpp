#include "pintool_defines.h"

#include <string>
using namespace std;

extern "C" {
    #include <lua.h>
    #include <lauxlib.h>
    #include <lualib.h>
}

string lua_get_string(lua_State* L, int index){
  const char* str = lua_tostring(L,index);
  if(!str){ lua_pushstring(L,"string expected");lua_error(L);}
  return string(str);
}

void stackdump(lua_State* l)
{
    int i;
    int top = lua_gettop(l);

    printf("total in stack %d\n",top);

    for (i = 1; i <= top; i++)
    {  /* repeat for each level */
        int t = lua_type(l, i);
        switch (t) {
            case LUA_TSTRING:  /* strings */
                printf("string: '%s'\n", lua_tostring(l, i));
                break;
            case LUA_TBOOLEAN:  /* booleans */
                printf("boolean %s\n",lua_toboolean(l, i) ? "true" : "false");
                break;
            case LUA_TNUMBER:  /* numbers */
                printf("number: %g\n", lua_tonumber(l, i));
                break;
            default:  /* other values */
                printf("%s\n", lua_typename(l, t));
                break;
        }
        printf("  ");  /* put a separator */
    }
    printf("\n");  /* end the listing */
}
