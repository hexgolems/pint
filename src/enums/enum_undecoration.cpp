#include "pin.H"
extern "C" {
#include "lua.h"
}
#include <map>
using namespace std;
static void error(lua_State* L, string val){
lua_pushstring(L,("unable to find define "+val+" in enum UNDECORATION").c_str());
lua_error(L);
}
static map<string,UNDECORATION> init_map(){
	map<string,UNDECORATION> smap;
	smap["NAME_ONLY"]=UNDECORATION_NAME_ONLY;
	smap["COMPLETE"]=UNDECORATION_COMPLETE;
	return smap;
}
UNDECORATION lookup_string_to_undecoration(lua_State *L, string str){
  static const map<string,UNDECORATION> sym_map = init_map();
  if(sym_map.find(str)!=sym_map.end()){
    return sym_map.find(str)->second;
  }
 error(L,str);
 return sym_map.begin()->second; //this will never be reached just to prevent compiler warning
}
string lookup_undecoration_to_string(lua_State* L,UNDECORATION sym) {
 switch (sym) {
    case(UNDECORATION_NAME_ONLY): return "NAME_ONLY";
    case(UNDECORATION_COMPLETE): return "COMPLETE";
  }
error(L, "unknown enum value");
return "never reached";
}
