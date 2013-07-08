#include "pin.H"
extern "C" {
#include "lua.h"
}
#include <map>
using namespace std;
static void error(lua_State* L, string val){
lua_pushstring(L,("unable to find define "+val+" in enum REGNAME").c_str());
lua_error(L);
}
static map<string,REGNAME> init_map(){
	map<string,REGNAME> smap;
	smap["LAST"]=REGNAME_LAST;
	return smap;
}
REGNAME lookup_string_to_regname(lua_State *L, string str){
  static const map<string,REGNAME> sym_map = init_map();
  if(sym_map.find(str)!=sym_map.end()){
    return sym_map.find(str)->second;
  }
 error(L,str);
 return sym_map.begin()->second; //this will never be reached just to prevent compiler warning
}
string lookup_regname_to_string(lua_State* L,REGNAME sym) {
 switch (sym) {
    case(REGNAME_LAST): return "LAST";
  }
error(L, "unknown enum value");
return "never reached";
}
