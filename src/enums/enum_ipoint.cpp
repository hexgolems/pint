#include "pin.H"
extern "C" {
#include <lua.h>
}
#include <map>
using namespace std;
static void error(lua_State* L, string val){
lua_pushstring(L,("unable to find define "+val+" in enum IPOINT").c_str());
lua_error(L);
}
static map<string,IPOINT> init_map(){
  map<string,IPOINT> smap;
  smap["INVALID"]=IPOINT_INVALID;
  smap["BEFORE"]=IPOINT_BEFORE;
  smap["ANYWHERE"]=IPOINT_ANYWHERE;
  smap["TAKEN_BRANCH"]=IPOINT_TAKEN_BRANCH;
  smap["AFTER"]=IPOINT_AFTER;
  return smap;
}
IPOINT lookup_string_to_ipoint(lua_State *L, string str){
  static const map<string,IPOINT> sym_map = init_map();
  if(sym_map.find(str)!=sym_map.end()){
    return sym_map.find(str)->second;
  }
 error(L,str);
 return sym_map.begin()->second; //this will never be reached just to prevent compiler warning
}
string lookup_ipoint_to_string(lua_State* L,IPOINT sym) {
 switch (sym) {
    case(IPOINT_INVALID): return "INVALID";
    case(IPOINT_BEFORE): return "BEFORE";
    case(IPOINT_ANYWHERE): return "ANYWHERE";
    case(IPOINT_TAKEN_BRANCH): return "TAKEN_BRANCH";
    case(IPOINT_AFTER): return "AFTER";
  }
error(L, "unknown enum value");
return "never reached";
}
