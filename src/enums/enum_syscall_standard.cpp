#include "pin.H"
extern "C" {
#include <lua.h>
}
#include <map>
using namespace std;
static void error(lua_State* L, string val){
lua_pushstring(L,("unable to find define "+val+" in enum SYSCALL_STANDARD").c_str());
lua_error(L);
}
static map<string,SYSCALL_STANDARD> init_map(){
  map<string,SYSCALL_STANDARD> smap;

#ifdef TARGET_IA32E
  smap["IA32E_BSD"]=SYSCALL_STANDARD_IA32E_BSD;
#endif
  smap["IA32_WINDOWS_FAST"]=SYSCALL_STANDARD_IA32_WINDOWS_FAST;
  smap["WINDOWS_INT"]=SYSCALL_STANDARD_WINDOWS_INT;
  smap["IA32E_MAC"]=SYSCALL_STANDARD_IA32E_MAC;
  smap["INVALID"]=SYSCALL_STANDARD_INVALID;
  smap["IA32_WINDOWS_ALT"]=SYSCALL_STANDARD_IA32_WINDOWS_ALT;
  smap["IA32_MAC"]=SYSCALL_STANDARD_IA32_MAC;
  smap["IA32E_LINUX"]=SYSCALL_STANDARD_IA32E_LINUX;
  smap["IA32_LINUX"]=SYSCALL_STANDARD_IA32_LINUX;
  smap["IA32E_WINDOWS_FAST"]=SYSCALL_STANDARD_IA32E_WINDOWS_FAST;
  smap["WOW64"]=SYSCALL_STANDARD_WOW64;
  return smap;
}
SYSCALL_STANDARD lookup_string_to_syscall_standard(lua_State *L, string str){
  static const map<string,SYSCALL_STANDARD> sym_map = init_map();
  if(sym_map.find(str)!=sym_map.end()){
    return sym_map.find(str)->second;
  }
 error(L,str);
 return sym_map.begin()->second; //this will never be reached just to prevent compiler warning
}
string lookup_syscall_standard_to_string(lua_State* L,SYSCALL_STANDARD sym) {
 switch (sym) {
#ifdef TARGET_IA32E
    case(SYSCALL_STANDARD_IA32E_BSD): return "IA32E_BSD";
#endif
#ifdef TARGET_IA32
    case(SYSCALL_STANDARD_IA32E_BSD): return "SYSCALL_STANDARD_IA32E_BSD";
#endif
    case(SYSCALL_STANDARD_IA32_WINDOWS_FAST): return "IA32_WINDOWS_FAST";
    case(SYSCALL_STANDARD_WINDOWS_INT): return "WINDOWS_INT";
    case(SYSCALL_STANDARD_IA32E_MAC): return "IA32E_MAC";
    case(SYSCALL_STANDARD_INVALID): return "INVALID";
    case(SYSCALL_STANDARD_IA32_WINDOWS_ALT): return "IA32_WINDOWS_ALT";
    case(SYSCALL_STANDARD_IA32_MAC): return "IA32_MAC";
    case(SYSCALL_STANDARD_IA32E_LINUX): return "IA32E_LINUX";
    case(SYSCALL_STANDARD_IA32_LINUX): return "IA32_LINUX";
    case(SYSCALL_STANDARD_IA32E_WINDOWS_FAST): return "IA32E_WINDOWS_FAST";
    case(SYSCALL_STANDARD_WOW64): return "WOW64";
  }
error(L, "unknown enum value");
return "never reached";
}
