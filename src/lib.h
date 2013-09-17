#ifndef __PINT_LIB_HELPERS__
#define __PINT_LIB_HELPERS__

#ifdef linux
  #include <fcntl.h>
#else
#endif

#include <stdlib.h>

extern "C" {
    #include <lua.h>
    #include <lauxlib.h>
    #include <lualib.h>
}


int readMem(lua_State *L) {
  void* ptr = (void*)lua_tointeger (L, 1);
  size_t len = (size_t)lua_tointeger (L, 2);
  char* buffer = (char*)malloc(len);
  if(!buffer){lua_pushnil(L); return 1;}
  size_t bytes_copied = PIN_SafeCopy(buffer, ptr, len);
  if(bytes_copied == 0) {lua_pushnil(L); return 1;}
  lua_pushlstring(L, (char*)ptr, bytes_copied);
  free(buffer);
  return 1;
}


const struct luaL_reg helper_lib [] = {
  {"read_mem",readMem},
  {NULL, NULL}
};

int luaopen_helper (lua_State *L) {
  luaL_openlib(L, "Helper", helper_lib, 0);
  return 1;
}

#endif //guard header
