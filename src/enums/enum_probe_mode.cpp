#include "pin.H"
extern "C" {
#include "lua.h"
}
#include <map>
using namespace std;
static void error(lua_State* L, string val){
lua_pushstring(L,("unable to find define "+val+" in enum PROBE_MODE").c_str());
lua_error(L);
}
static map<string,PROBE_MODE> init_map(){
	map<string,PROBE_MODE> smap;
	smap["DEFAULT"]=PROBE_MODE_DEFAULT;
	smap["ALLOW_RELOCATION"]=PROBE_MODE_ALLOW_RELOCATION;
	return smap;
}
PROBE_MODE lookup_string_to_probe_mode(lua_State *L, string str){
  static const map<string,PROBE_MODE> sym_map = init_map();
  if(sym_map.find(str)!=sym_map.end()){
    return sym_map.find(str)->second;
  }
 error(L,str);
 return sym_map.begin()->second; //this will never be reached just to prevent compiler warning
}
string lookup_probe_mode_to_string(lua_State* L,PROBE_MODE sym) {
 switch (sym) {
    case(PROBE_MODE_DEFAULT): return "DEFAULT";
    case(PROBE_MODE_ALLOW_RELOCATION): return "ALLOW_RELOCATION";
  }
error(L, "unknown enum value");
return "never reached";
}
