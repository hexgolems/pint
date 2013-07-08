#include "pin.H"
extern "C" {
#include "lua.h"
}
#include <map>
using namespace std;
static void error(lua_State* L, string val){
lua_pushstring(L,("unable to find define "+val+" in enum IMG_TYPE").c_str());
lua_error(L);
}
static map<string,IMG_TYPE> init_map(){
	map<string,IMG_TYPE> smap;
	smap["RELOCATABLE"]=IMG_TYPE_RELOCATABLE;
	smap["INVALID"]=IMG_TYPE_INVALID;
	smap["LAST"]=IMG_TYPE_LAST;
	smap["STATIC"]=IMG_TYPE_STATIC;
	smap["SHARED"]=IMG_TYPE_SHARED;
	smap["SHAREDLIB"]=IMG_TYPE_SHAREDLIB;
	return smap;
}
IMG_TYPE lookup_string_to_img_type(lua_State *L, string str){
  static const map<string,IMG_TYPE> sym_map = init_map();
  if(sym_map.find(str)!=sym_map.end()){
    return sym_map.find(str)->second;
  }
 error(L,str);
 return sym_map.begin()->second; //this will never be reached just to prevent compiler warning
}
string lookup_img_type_to_string(lua_State* L,IMG_TYPE sym) {
 switch (sym) {
    case(IMG_TYPE_RELOCATABLE): return "RELOCATABLE";
    case(IMG_TYPE_INVALID): return "INVALID";
    case(IMG_TYPE_LAST): return "LAST";
    case(IMG_TYPE_STATIC): return "STATIC";
    case(IMG_TYPE_SHARED): return "SHARED";
    case(IMG_TYPE_SHAREDLIB): return "SHAREDLIB";
  }
error(L, "unknown enum value");
return "never reached";
}
