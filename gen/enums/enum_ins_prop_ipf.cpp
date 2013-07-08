#include "pin.H"
extern "C" {
#include "lua.h"
}
#include <map>
using namespace std;
static void error(lua_State* L, string val){
lua_pushstring(L,("unable to find define "+val+" in enum INS_PROP_IPF").c_str());
lua_error(L);
}
static map<string,INS_PROP_IPF> init_map(){
	map<string,INS_PROP_IPF> smap;
	smap["LOAD_ORDERED"]=INS_PROP_IPF_LOAD_ORDERED;
	smap["STOP"]=INS_PROP_IPF_STOP;
	smap["LOAD_ADVANCED"]=INS_PROP_IPF_LOAD_ADVANCED;
	smap["ALAT_CLEAR"]=INS_PROP_IPF_ALAT_CLEAR;
	smap["LOAD_BIASED"]=INS_PROP_IPF_LOAD_BIASED;
	smap["LOAD_CHECK"]=INS_PROP_IPF_LOAD_CHECK;
	smap["DOUBLE_SYLLABLE"]=INS_PROP_IPF_DOUBLE_SYLLABLE;
	smap["LOAD_SPECULATIVE"]=INS_PROP_IPF_LOAD_SPECULATIVE;
	return smap;
}
INS_PROP_IPF lookup_string_to_ins_prop_ipf(lua_State *L, string str){
  static const map<string,INS_PROP_IPF> sym_map = init_map();
  if(sym_map.find(str)!=sym_map.end()){
    return sym_map.find(str)->second;
  }
 error(L,str);
 return sym_map.begin()->second; //this will never be reached just to prevent compiler warning
}
string lookup_ins_prop_ipf_to_string(lua_State* L,INS_PROP_IPF sym) {
 switch (sym) {
    case(INS_PROP_IPF_LOAD_ORDERED): return "LOAD_ORDERED";
    case(INS_PROP_IPF_STOP): return "STOP";
    case(INS_PROP_IPF_LOAD_ADVANCED): return "LOAD_ADVANCED";
    case(INS_PROP_IPF_ALAT_CLEAR): return "ALAT_CLEAR";
    case(INS_PROP_IPF_LOAD_BIASED): return "LOAD_BIASED";
    case(INS_PROP_IPF_LOAD_CHECK): return "LOAD_CHECK";
    case(INS_PROP_IPF_DOUBLE_SYLLABLE): return "DOUBLE_SYLLABLE";
    case(INS_PROP_IPF_LOAD_SPECULATIVE): return "LOAD_SPECULATIVE";
  }
error(L, "unknown enum value");
return "never reached";
}
