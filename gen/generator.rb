require 'set'
require './wrapper.rb'

$ENUMS = %w{
IMG_TYPE MEMORY_TYPE SYSCALL_STANDARD PREDICATE_IA32 INS_PROP_IPF SEC_TYPE PROBE_MODE REG REG REGNAME UNDECORATION IPOINT CALL_ORDER IARG_TYPE
}
$WRAPPED =%w{IMG INS SEC RTN REG TRACE BBL SYM}
$BASIC_INT = %w{INT32 UINT32 ADDRINT USIZE UINT16 INT16 ADDRDELTA UINT64 INT64 INS_PROP}
$BASIC_PTR = %w{AFUNPTR}
$BASIC_STRING = %w{string}
$BASIC_BOOL = %w{BOOL}
$BASIC = $BASIC_INT+$BASIC_STRING+$BASIC_BOOL

$cpp_includes = <<EOF
#include "lua.h"
#include "pin.H"

extern "C" {
    #include <lua.h>
    #include <lauxlib.h>
    #include <lualib.h>
}
EOF


def name_conv(name)
  name.gsub(/([A-Z])/){|match| "_"+match.downcase}.gsub(/\A_/,"")
end

def get_inputs(inputs)
  codes = []
  vals =[]
  inputs.each.with_index do |type,index|
    code,val = get_input(type,index+1)
    codes << code
    vals << val
  end
  return codes.map{|c| "\t"+c}.join(";\n"), vals
end

def get_input(input_type,i=1)
  case input_type
    when *$BASIC_PTR then
      code = "#{input_type} v#{i} = (VOID(*)())((UINT64)lua_tonumber(L,#{i}))"
      input_val = "v#{i}"
    when *$BASIC_INT then
      code = "#{input_type} v#{i} = lua_tonumber(L,#{i})"
      input_val = "v#{i}"
    when *$BASIC_BOOL then
      code = "#{input_type} v#{i} = lua_toboolean(L,#{i})"
      input_val = "v#{i}"
    when *$BASIC_STRING then
      code = "#{input_type} v#{i} = lua_tostring(L,#{i})"
      input_val = "v#{i}"
    when *$ENUMS then
      code ="#{input_type} v#{i} = lookup_string_to_#{input_type.downcase}(L,lua_tostring(L,#{i}))"
      input_val = "v#{i}"
    when *$WRAPPED then
      code = "#{input_type}* v#{i} = check_#{input_type.downcase}(L,#{i})"
      input_val = "*v#{i}"
    else raise "unfinished for input #{input_type}"
  end
  return code,input_val
end

def get_call(ret_type,name,vals)
  input_string = vals.join(",")
  puts ret_type.inspect,$ENUMS.inspect
  case ret_type
    when *$BASIC_PTR then
      code = "#{ret_type} r = #{name}(#{input_string})"
      push_str = "(UINT64)r"
    when *$BASIC then
      code = "#{ret_type} r = #{name}(#{input_string})"
      push_str =  case ret_type
                    when "string" then "r.c_str()"
                    else "r"
                  end
    when *$ENUMS then
      puts "found enum"
      code = "string r = lookup_#{ret_type.downcase}_to_string(L,#{name}(#{input_string}))"
      push_str = "r.c_str()"
    when *$WRAPPED then
      code = "#{ret_type}_to_lua(L, #{name}(#{input_string}))"
      push_str=nil
    when "VOID" then
      code = " #{name}(#{input_string})"
      push_str=nil
    else raise "unfinished for return #{ret_type}"
  end
  return code,push_str
end

def get_output(ret_type, push_str)
  return "" unless push_str
  puts "return foo"
  puts ret_type.inspect
  puts *$BASIC_STRING
  case ret_type
    when *$BASIC_PTR then "lua_pushnumber(L, #{push_str})"
    when *$BASIC_INT then "lua_pushnumber(L, #{push_str})"
    when *$BASIC_BOOL then "lua_pushboolean(L, #{push_str})"
    when *$BASIC_STRING then "lua_pushstring(L, #{push_str})"
    when *$ENUMS then "lua_pushstring(L, #{push_str})"
  end
end

def generateto1(ret,base_type, name,input_types)
  input_code, vals = get_inputs(input_types)
  call_code, push_str=get_call(ret,base_type+"_"+name, vals)
  push_code = get_output(ret,push_str)

  function_name = (base_type.downcase+"_"+name_conv(name)).tr_s("_","_")
  res = ""
  res << "int #{function_name} (lua_State *L) { \n"
  res << "#{input_code};\n"
  res << "\t#{call_code};\n"
  res << "\t#{push_code};\n"
  res << if ret=="VOID" then "\treturn 0;\n" else "\treturn 1;\n" end
  res << "}\n"
  return res
end

$unfinished = File.open("unfinished.txt","w")
def unfinished(line, exception=false)
  $unfinished.puts "="*80
  $unfinished.puts($!,$@) if exception
  $unfinished.puts line
  $unfinished.puts "="*80
  $functions_failed +=1
end

$functions_generated = 0
$functions_failed = 0

$functions = {}
File.read("functions.txt").lines.each do |line|
  line.strip!
  line.gsub!("&","")
  next if line.length==0  || line =~/valid/i
  if /(\w+)\s*LEVEL_(CORE|PINCLIENT|BASE)::([A-Z]+)_(\w+)\s*\((([^,]*,)*[^,]*)\)/.match(line)
    ret,ns,base_type,name,args = $1,$2,$3,$4,$5
    args = args.split(",").map{|x| x.gsub("const","").strip.split(" ")[0..-2].join(" ")}
      begin
        $functions[base_type] ||= Set.new
        $functions[base_type].add generateto1(ret, base_type, name, args)
        $functions_generated+=1
      rescue
        unfinished(line, true)
      end
  else
    unfinished(line)
  end
end

$functions.each_pair do |base, set|
  File.open("functions/lua_#{base.downcase}.h","w") do |f|
    f.puts ""
    f.puts header(base, $WRAPPED, set.map { |func| func.lines.first.gsub("{",";") })
  end
end

$functions.each_pair do |base,set|
  bl,bu = base.downcase, base.upcase
  File.open("functions/lua_#{base.downcase}.cpp","w") do |f|
    f.puts $WRAPPED.each.map{|key| "#include \"lua_#{key.downcase}.h\"\n"}
    f.puts $ENUMS.each.map{|key| "#include \"../enums/enum_#{key.downcase}.h\"\n"}
    f.puts ""
    f.puts "#include \"../gen_fn/lua_#{bl}.h\""
    f.puts $cpp_includes
    if $WRAPPED.include? base.upcase
      f.puts default_impl(base)
    end

    f.puts <<EOF
int luaopen_#{bl} (lua_State *L) {
  luaL_newmetatable(L, "pin.#{bl.capitalize}");
  luaL_openlib(L, "#{bl.capitalize}", #{bl}_lib, 0);
  return 1;
}
EOF

    set.each do |func|
      f.puts func.gsub(/$\s*;[\t ]*/,"")
    end

  end
end

puts "finished generating #{$functions_generated} function, #{$functions_failed} failed"
