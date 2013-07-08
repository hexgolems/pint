def header(base,wrapped, functions)
bl,bu = base.downcase, base.upcase
pre = <<EOF
#ifndef __PINT_LUA_#{bu}_WRAPPER__
#define __PINT_LUA_#{bu}_WRAPPER__

extern "C" {
    #include <lua.h>
    #include <lauxlib.h>
    #include <lualib.h>
}

#include "pin.H"
#{
wrapped.map{|key| "#include \"lua_#{key.downcase}.h\"\n"}.join("")
}
#{if wrapped.include?(bu) then
  "int #{bu}_to_lua(lua_State *L, #{bu} #{bl});
  #{bu} *check_#{bl} (lua_State *L, int);"
  end
}
int luaopen_#{bl} (lua_State *L);
EOF

body = functions.join("")

names = functions.map {|func| func=~ /\A\s*int\s*([a-z_0-9]+)/; $1}
puts names.inspect
lua_names=names.map{|name| [name.split("_")[1..-1].join("_"), name]}

post = <<EOF
const struct luaL_reg #{bl}_lib [] = {
  #{lua_names.map{|(n,f)| "\t{#{n.inspect},#{f}},\n"}.join("")}
  {NULL, NULL}
};

#endif
EOF
return pre+body+post
end


def default_impl(base)
bl,bu = base.downcase, base.upcase
test_for_validity = true unless %w{TRACE}.include? bu
str = <<EOF
int #{bu}_to_lua(lua_State *L, #{bu} #{bl}) {
    #{
      if test_for_validity then
        "#{ if bu == "REG" then "if(!#{bu}_valid(#{bl})) {" else  "if(!#{bu}_Valid(#{bl})) {" end}
        lua_pushnil(L);
        return 1;
      }"
    end}
    #{bu} *i = (#{bu} *)lua_newuserdata(L, sizeof(#{bu}));
    *i = #{bl};
    luaL_getmetatable(L, "pin.#{bl.capitalize}");
    lua_setmetatable(L, -2);

  return 1;
}

#{bu} *check_#{bl} (lua_State *L, int pos) {
  void *ud = luaL_checkudata(L, pos, "pin.#{bl.capitalize}");
  luaL_argcheck(L, ud != NULL, pos, "`#{bl.capitalize}' expected");
  return (#{bu} *)ud;
}

EOF
return str
end

