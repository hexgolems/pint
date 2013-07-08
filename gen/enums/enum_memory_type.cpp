#include "pin.H"
extern "C" {
#include "lua.h"
}
#include <map>
using namespace std;
static void error(lua_State* L, string val){
lua_pushstring(L,("unable to find define "+val+" in enum MEMORY_TYPE").c_str());
lua_error(L);
}
static map<string,MEMORY_TYPE> init_map(){
	map<string,MEMORY_TYPE> smap;
	smap["READ"]=MEMORY_TYPE_READ;
	smap["READ2"]=MEMORY_TYPE_READ2;
	smap["WRITE"]=MEMORY_TYPE_WRITE;
	return smap;
}
MEMORY_TYPE lookup_string_to_memory_type(lua_State *L, string str){
  static const map<string,MEMORY_TYPE> sym_map = init_map();
  if(sym_map.find(str)!=sym_map.end()){
    return sym_map.find(str)->second;
  }
 error(L,str);
 return sym_map.begin()->second; //this will never be reached just to prevent compiler warning
}
string lookup_memory_type_to_string(lua_State* L,MEMORY_TYPE sym) {
 switch (sym) {
    case(MEMORY_TYPE_READ): return "READ";
    case(MEMORY_TYPE_READ2): return "READ2";
    case(MEMORY_TYPE_WRITE): return "WRITE";
  }
error(L, "unknown enum value");
return "never reached";
}
