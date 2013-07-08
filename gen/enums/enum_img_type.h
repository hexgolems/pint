#ifndef __PINT_ENUM_IMG_TYPE__
#define __PINT_ENUM_IMG_TYPE__
extern "C" {
#include "lua.h"
}
#include "pin.H"
IMG_TYPE lookup_string_to_img_type(lua_State* L,string str);
string lookup_img_type_to_string(lua_State* L,IMG_TYPE);
#endif
