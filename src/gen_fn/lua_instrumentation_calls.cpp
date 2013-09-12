
#include "gen_fn/lua_instrumentation_calls.h"
#include <stdarg.h>
#include <vector>
#include "enums/enum_iarg_type.h"
#include "enums/enum_ipoint.h"
#include "lua_typed_callback.h"
#include "gen_fn/lua_ins.h"
#include "gen_fn/lua_bbl.h"
#include "pintool_defines.h"

using namespace std;

extern "C" {
    #include <lua.h>
    #include <lauxlib.h>
    #include <lualib.h>
}

#include "pin.H"

//This function will be called from lua. It installs a callback for every execution of the given INS/BBL/TRACE/ROUTINE
#define ADD_INSTRUMENTATION_CALL(Name,InsertCall,CheckCall) int Name(lua_State *L) {\
  IARGLIST arglist = get_instrument_arglist(L,1);\
  InsertCall(\
      *CheckCall(L,1),\
      lookup_string_to_ipoint(L,lua_get_string(L,3)),\
      (AFUNPTR)instrument_callback,\
      IARG_IARGLIST,\
      arglist,\
      IARG_END);\
  IARGLIST_Free(arglist);\
  return 0;\
}

ADD_INSTRUMENTATION_CALL(add_ins_call, INS_InsertCall, check_ins)
ADD_INSTRUMENTATION_CALL(add_bbl_call, BBL_InsertCall, check_bbl)
ADD_INSTRUMENTATION_CALL(add_trace_call, TRACE_InsertCall, check_trace)
ADD_INSTRUMENTATION_CALL(add_rtn_call, RTN_InsertCall, check_rtn)
