#ifndef __PINT_LIB_HELPERS__
#define __PINT_LIB_HELPERS__

#ifdef linux
  #include <fcntl.h>
#else
#endif

extern "C" {
    #include <lua.h>
    #include <lauxlib.h>
    #include <lualib.h>
}


#ifdef linux
int isValidMem(void *ptr, size_t size) {
  int nullfd = open("/dev/random", O_WRONLY);
  if (write(nullfd, ptr, size) < 0) {
    close(nullfd);
    return 0;
  }
  close(nullfd);
  return -1;
}
#else
int isValidMem(void *ptr, size_t size) {
  return !isBadReadPtr(ptr,size);
}
#endif


int readMemSafe (lua_State *L) {
  void* ptr = (void*)lua_tointeger (L, 1);
  size_t len = (size_t)lua_tointeger (L, 2);
  if(isValidMem(ptr, len)){
    lua_pushlstring(L, (char*)ptr, len);
  }else {
    lua_pushnil(L);
  }
  return 1;
}

int readMem(lua_State *L) {
  void* ptr = (void*)lua_tointeger (L, 1);
  size_t len = (size_t)lua_tointeger (L, 2);
  lua_pushlstring(L, (char*)ptr, len);
  return 1;
}


const struct luaL_reg helper_lib [] = {
  {"read_mem_unsafe",readMem},
  {"read_mem",readMemSafe},
  {NULL, NULL}
};

int luaopen_helper (lua_State *L) {
  luaL_openlib(L, "Helper", helper_lib, 0);
  return 1;
}

#endif //guard header
