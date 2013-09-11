#include "pin.H"
extern "C" {
#include <lua.h>
}
#include <map>
using namespace std;
static void error(lua_State* L, string val){
lua_pushstring(L,("unable to find define "+val+" in enum PREDICATE_IA32").c_str());
lua_error(L);
}
static map<string,PREDICATE_IA32> init_map(){
	map<string,PREDICATE_IA32> smap;
	smap["PREDICATE_LAST"]=PREDICATE_LAST;
	smap["PREDICATE_OVERFLOW"]=PREDICATE_OVERFLOW;
	smap["PREDICATE_LESS"]=PREDICATE_LESS;
	smap["PREDICATE_CX_NON_ZERO"]=PREDICATE_CX_NON_ZERO;
	smap["PREDICATE_NOT_SIGN"]=PREDICATE_NOT_SIGN;
	smap["PREDICATE_NOT_BELOW_OR_EQUAL"]=PREDICATE_NOT_BELOW_OR_EQUAL;
	smap["PREDICATE_LESS_OR_EQUAL"]=PREDICATE_LESS_OR_EQUAL;
	smap["PREDICATE_INVALID"]=PREDICATE_INVALID;
	smap["PREDICATE_BELOW_OR_EQUAL"]=PREDICATE_BELOW_OR_EQUAL;
	smap["PREDICATE_BELOW"]=PREDICATE_BELOW;
	smap["PREDICATE_RCX_NON_ZERO"]=PREDICATE_RCX_NON_ZERO;
	smap["PREDICATE_NOT_ZERO"]=PREDICATE_NOT_ZERO;
	smap["PREDICATE_NOT_LESS_OR_EQUAL"]=PREDICATE_NOT_LESS_OR_EQUAL;
	smap["PREDICATE_NOT_LESS"]=PREDICATE_NOT_LESS;
	smap["PREDICATE_NOT_BELOW"]=PREDICATE_NOT_BELOW;
	smap["PREDICATE_SAVED_GCX_NON_ZERO"]=PREDICATE_SAVED_GCX_NON_ZERO;
	smap["PREDICATE_ALWAYS_TRUE"]=PREDICATE_ALWAYS_TRUE;
	smap["PREDICATE_SIGN"]=PREDICATE_SIGN;
	smap["PREDICATE_NOT_OVERFLOW"]=PREDICATE_NOT_OVERFLOW;
	smap["PREDICATE_ECX_NON_ZERO"]=PREDICATE_ECX_NON_ZERO;
	smap["PREDICATE_ZERO"]=PREDICATE_ZERO;
	smap["PREDICATE_PARITY"]=PREDICATE_PARITY;
	smap["PREDICATE_NOT_PARITY"]=PREDICATE_NOT_PARITY;
	return smap;
}
PREDICATE_IA32 lookup_string_to_predicate_ia32(lua_State *L, string str){
  static const map<string,PREDICATE_IA32> sym_map = init_map();
  if(sym_map.find(str)!=sym_map.end()){
    return sym_map.find(str)->second;
  }
 error(L,str);
 return sym_map.begin()->second; //this will never be reached just to prevent compiler warning
}
string lookup_predicate_ia32_to_string(lua_State* L,PREDICATE_IA32 sym) {
 switch (sym) {
    case(PREDICATE_LAST): return "PREDICATE_LAST";
    case(PREDICATE_OVERFLOW): return "PREDICATE_OVERFLOW";
    case(PREDICATE_LESS): return "PREDICATE_LESS";
    case(PREDICATE_CX_NON_ZERO): return "PREDICATE_CX_NON_ZERO";
    case(PREDICATE_NOT_SIGN): return "PREDICATE_NOT_SIGN";
    case(PREDICATE_NOT_BELOW_OR_EQUAL): return "PREDICATE_NOT_BELOW_OR_EQUAL";
    case(PREDICATE_LESS_OR_EQUAL): return "PREDICATE_LESS_OR_EQUAL";
    case(PREDICATE_INVALID): return "PREDICATE_INVALID";
    case(PREDICATE_BELOW_OR_EQUAL): return "PREDICATE_BELOW_OR_EQUAL";
    case(PREDICATE_BELOW): return "PREDICATE_BELOW";
    case(PREDICATE_RCX_NON_ZERO): return "PREDICATE_RCX_NON_ZERO";
    case(PREDICATE_NOT_ZERO): return "PREDICATE_NOT_ZERO";
    case(PREDICATE_NOT_LESS_OR_EQUAL): return "PREDICATE_NOT_LESS_OR_EQUAL";
    case(PREDICATE_NOT_LESS): return "PREDICATE_NOT_LESS";
    case(PREDICATE_NOT_BELOW): return "PREDICATE_NOT_BELOW";
    case(PREDICATE_SAVED_GCX_NON_ZERO): return "PREDICATE_SAVED_GCX_NON_ZERO";
    case(PREDICATE_ALWAYS_TRUE): return "PREDICATE_ALWAYS_TRUE";
    case(PREDICATE_SIGN): return "PREDICATE_SIGN";
    case(PREDICATE_NOT_OVERFLOW): return "PREDICATE_NOT_OVERFLOW";
    case(PREDICATE_ECX_NON_ZERO): return "PREDICATE_ECX_NON_ZERO";
    case(PREDICATE_ZERO): return "PREDICATE_ZERO";
    case(PREDICATE_PARITY): return "PREDICATE_PARITY";
    case(PREDICATE_NOT_PARITY): return "PREDICATE_NOT_PARITY";
  }
error(L, "unknown enum value");
return "never reached";
}
