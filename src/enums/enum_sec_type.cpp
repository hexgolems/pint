#include "pin.H"
extern "C" {
#include <lua.h>
}
#include <map>
using namespace std;
static void error(lua_State* L, string val){
lua_pushstring(L,("unable to find define "+val+" in enum SEC_TYPE").c_str());
lua_error(L);
}
static map<string,SEC_TYPE> init_map(){
	map<string,SEC_TYPE> smap;
	smap["SYMSTR"]=SEC_TYPE_SYMSTR;
	smap["BSS"]=SEC_TYPE_BSS;
	smap["USER"]=SEC_TYPE_USER;
	smap["UNUSED"]=SEC_TYPE_UNUSED;
	smap["LOOS"]=SEC_TYPE_LOOS;
	smap["DYNSTR"]=SEC_TYPE_DYNSTR;
	smap["UNWINDINFO"]=SEC_TYPE_UNWINDINFO;
	smap["STACK"]=SEC_TYPE_STACK;
	smap["REGSYM"]=SEC_TYPE_REGSYM;
	smap["LSDA"]=SEC_TYPE_LSDA;
	smap["INVALID"]=SEC_TYPE_INVALID;
	smap["PLTOFF"]=SEC_TYPE_PLTOFF;
	smap["LAST"]=SEC_TYPE_LAST;
	smap["OPD"]=SEC_TYPE_OPD;
	smap["DYNSYM"]=SEC_TYPE_DYNSYM;
	smap["REGREL"]=SEC_TYPE_REGREL;
	smap["HASH"]=SEC_TYPE_HASH;
	smap["DYNREL"]=SEC_TYPE_DYNREL;
	smap["DEBUG"]=SEC_TYPE_DEBUG;
	smap["DATA"]=SEC_TYPE_DATA;
	smap["SECSTR"]=SEC_TYPE_SECSTR;
	smap["GOT"]=SEC_TYPE_GOT;
	smap["EXEC"]=SEC_TYPE_EXEC;
	smap["DYNAMIC"]=SEC_TYPE_DYNAMIC;
	smap["COMMENT"]=SEC_TYPE_COMMENT;
	smap["UNWIND"]=SEC_TYPE_UNWIND;
	return smap;
}
SEC_TYPE lookup_string_to_sec_type(lua_State *L, string str){
  static const map<string,SEC_TYPE> sym_map = init_map();
  if(sym_map.find(str)!=sym_map.end()){
    return sym_map.find(str)->second;
  }
 error(L,str);
 return sym_map.begin()->second; //this will never be reached just to prevent compiler warning
}
string lookup_sec_type_to_string(lua_State* L,SEC_TYPE sym) {
 switch (sym) {
    case(SEC_TYPE_SYMSTR): return "SYMSTR";
    case(SEC_TYPE_BSS): return "BSS";
    case(SEC_TYPE_USER): return "USER";
    case(SEC_TYPE_UNUSED): return "UNUSED";
    case(SEC_TYPE_LOOS): return "LOOS";
    case(SEC_TYPE_DYNSTR): return "DYNSTR";
    case(SEC_TYPE_UNWINDINFO): return "UNWINDINFO";
    case(SEC_TYPE_STACK): return "STACK";
    case(SEC_TYPE_REGSYM): return "REGSYM";
    case(SEC_TYPE_LSDA): return "LSDA";
    case(SEC_TYPE_INVALID): return "INVALID";
    case(SEC_TYPE_PLTOFF): return "PLTOFF";
    case(SEC_TYPE_LAST): return "LAST";
    case(SEC_TYPE_OPD): return "OPD";
    case(SEC_TYPE_DYNSYM): return "DYNSYM";
    case(SEC_TYPE_REGREL): return "REGREL";
    case(SEC_TYPE_HASH): return "HASH";
    case(SEC_TYPE_DYNREL): return "DYNREL";
    case(SEC_TYPE_DEBUG): return "DEBUG";
    case(SEC_TYPE_DATA): return "DATA";
    case(SEC_TYPE_SECSTR): return "SECSTR";
    case(SEC_TYPE_GOT): return "GOT";
    case(SEC_TYPE_EXEC): return "EXEC";
    case(SEC_TYPE_DYNAMIC): return "DYNAMIC";
    case(SEC_TYPE_COMMENT): return "COMMENT";
    case(SEC_TYPE_UNWIND): return "UNWIND";
  }
error(L, "unknown enum value");
return "never reached";
}
