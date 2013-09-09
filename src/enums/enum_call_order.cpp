#include "pin.H"
extern "C" {
#include <lua.h>
}
#include <map>
using namespace std;
static void error(lua_State* L, string val){
lua_pushstring(L,("unable to find define "+val+" in enum CALL_ORDER").c_str());
lua_error(L);
}
static map<string,CALL_ORDER> init_map(){
	map<string,CALL_ORDER> smap;
	smap["LAST"]=CALL_ORDER_LAST;
	smap["DEFAULT"]=CALL_ORDER_DEFAULT;
	smap["FIRST"]=CALL_ORDER_FIRST;
	return smap;
}
CALL_ORDER lookup_string_to_call_order(lua_State *L, string str){
  static const map<string,CALL_ORDER> sym_map = init_map();
  if(sym_map.find(str)!=sym_map.end()){
    return sym_map.find(str)->second;
  }
 error(L,str);
 return sym_map.begin()->second; //this will never be reached just to prevent compiler warning
}
string lookup_call_order_to_string(lua_State* L,CALL_ORDER sym) {
 switch (sym) {
    case(CALL_ORDER_LAST): return "LAST";
    case(CALL_ORDER_DEFAULT): return "DEFAULT";
    case(CALL_ORDER_FIRST): return "FIRST";
  }
error(L, "unknown enum value");
return "never reached";
}
