#include <iostream>
#include "lua.h"
#include "gen_fn/lua_app.h"
#include "gen_fn/lua_bbl.h"
#include "gen_fn/lua_category.h"
#include "gen_fn/lua_extension.h"
#include "gen_fn/lua_img.h"
#include "gen_fn/lua_ins.h"
#include "gen_fn/lua_opcode.h"
#include "gen_fn/lua_pin.h"
#include "gen_fn/lua_reg.h"
#include "gen_fn/lua_rtn.h"
#include "gen_fn/lua_sec.h"
#include "gen_fn/lua_sym.h"
#include "gen_fn/lua_trace.h"
#include "lib.h"

#ifdef linux
  #include "unistd.h"
#endif

#include "wrapped_callbacks.h"
#include "gen_fn/lua_typed_callback.h"

extern "C" {
    #include <lua.h>
    #include <lauxlib.h>
    #include <lualib.h>
}
  void Lua::open_all(){

    luaopen_app(L);
    luaopen_bbl(L);
    luaopen_category(L);
    luaopen_extension(L);
    luaopen_img(L);
    luaopen_ins(L);
    luaopen_opcode(L);
    luaopen_pin(L);
    luaopen_reg(L);
    luaopen_rtn(L);
    luaopen_sec(L);
    luaopen_sym(L);
    luaopen_typed_callback(L);
    luaopen_trace(L);
    luaopen_helper(L);

    luaopen_callbacks(L);
  }

  void Lua::setup(std::string filename){

#ifdef linux
    lua_std_in = fdopen(dup(STDIN_FILENO), "r");
    lua_std_out = fdopen(dup(STDOUT_FILENO), "a");
    lua_std_err = fdopen(dup(STDERR_FILENO), "a");

    fprintf(lua_std_err,"-- Loading Lua libs\n");
#else
    printf("-- Loading Lua libs\n");
#endif
    luaL_openlibs(L);

    open_all();
    if(lua_cpcall(L,init_callback_table,0) != 0) {
      lua_error(L);
    }

    lua_register(L, "add_ins_callback", add_ins_call);

#ifdef linux
    fprintf(lua_std_err,"-- Loading file: %s \n",filename.c_str());
#else
    printf("-- Loading file: %s \n",filename.c_str());
#endif

    lua_getglobal(L, "debug"); //addes debug backtrace as formater for errors
    lua_getfield(L, -1, "traceback");
    int s = luaL_loadfile(L, filename.c_str());
    if ( s==0 ) {
      s = lua_pcall(L, 0, LUA_MULTRET, -2); // LAST 0 is the traceback
    }
    report_errors(s);
    std::cerr << std::endl;
  }

  void Lua::done(int exitstatus){

#ifdef linux
    fflush(stdin);
    fflush(stdout);
    fflush(stderr);
    dup2(fileno(lua_std_in),STDIN_FILENO); //this stuff recovers stdin/stdout/stderr after the instrumentated process closed them
    dup2(fileno(lua_std_out),STDOUT_FILENO);
    dup2(fileno(lua_std_err),STDERR_FILENO);
#else
    freopen ("closing_log_stdout.txt","w",stdout);
    freopen ("closing_log_stderr.txt","w",stderr);
    fprintf(stderr,"error output:\n");
    printf("std output:\n");
#endif

    luaopen_debug(L);

    //lua_pushcfunction(L, errorHandler);

    lua_getglobal(L, "debug"); //addes debug backtrace as formater for errors
    lua_getfield(L, -1, "traceback");

    lua_getglobal(L, "at_exit");
    lua_pushnumber(L, exitstatus);
    report_errors(lua_pcall(L, 1, 0, -3)); // last -3 = debug.backtrace is used as error function
    fclose(stdout);
    fclose(stderr);
  }

  void Lua::report_errors(int status)
  {
    if ( status!=0 ) {
      #ifdef linux
      fprintf(lua_std_out,"--* %s\n", lua_tostring(L, -1));
      #else
      fprintf(stdout,"--* %s\n", lua_tostring(L, -1));
      #endif
      lua_pop(L, 1); // remove error message
    }
  }

