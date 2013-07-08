require 'set'

enums = {}
File.read("enums.txt").split("enum").each do |body|
  typedef, vals = body.split("{")
  if typedef && vals
#   puts "="*80
    typename = typedef.split("::").last.strip
    vals = vals.split("\n").map{|val|
      val.gsub!(/[ \t{},]/,"")
      next if val==""
      without_ns = val.split("::").last
      without_num = without_ns.split("=").first
      without_num
    }.select{|x| x&&x.length > 0}
    puts "="*80
    puts typename
    puts vals
    enums[typename]||=Set.new
    enums[typename]+=vals.sort.uniq
  end
end
puts "="*80
enums.each_pair do |type,vals|
  tl,tu = type.downcase, type.upcase

  File.open("enums/enum_#{tl}.h","w") do |f|
    f.puts "#ifndef __PINT_ENUM_#{tu}__"
    f.puts "#define __PINT_ENUM_#{tu}__"
    f.puts "extern \"C\" {"
    f.puts "#include \"lua.h\""
    f.puts "}"
    f.puts "#include \"pin.H\""
    f.puts "#{type} lookup_string_to_#{tl}(lua_State* L,string str);"
    f.puts "string lookup_#{tl}_to_string(lua_State* L,#{type});"
    f.puts "#endif"
  end

  pairs = vals.map{|name| [name.gsub(tu+"_",""), name]}
  trie = hashtrie(tl,pairs)

  File.open("enums/enum_#{tl}.cpp","w") do |f|
    error="error(L,str);"

    f.puts "#include \"pin.H\""
    f.puts "extern \"C\" {"
    f.puts "#include \"lua.h\""
    f.puts "}"
    f.puts "#include <map>"
    f.puts "using namespace std;"

    f.puts "static void error(lua_State* L, string val){"
    f.puts "lua_pushstring(L,(\"unable to find define \"+val+\" in enum #{tu}\").c_str());"
    f.puts "lua_error(L);"
    f.puts "}"

#f.puts trie.to_hash_code(error,type, pairs.first.last)
    f.puts "static map<string,#{tu}> init_map(){"
    f.puts "\tmap<string,#{tu}> smap;"
      pairs.each do |str,sym|
        f.puts "\tsmap[#{str.inspect}]=#{sym};"
      end
    f.puts "\treturn smap;"
    f.puts "}"

    f.puts "#{tu} lookup_string_to_#{tl}(lua_State *L, string str){"
    f.puts "  static const map<string,#{tu}> sym_map = init_map();"
    f.puts "  if(sym_map.find(str)!=sym_map.end()){"
    f.puts "    return sym_map.find(str)->second;"
    f.puts "  }"
    f.puts " #{error}"
    f.puts " return sym_map.begin()->second; //this will never be reached just to prevent compiler warning"
    f.puts "}"

    f.puts "string lookup_#{tl}_to_string(lua_State* L,#{type} sym) {"
    f.puts " switch (sym) {"
    pairs.each do |(str,sym)|
      f.puts "    case(#{sym}): return #{str.inspect};"
    end
    f.puts "  }"
    f.puts "error(L, \"unknown enum value\");"
    f.puts "return \"never reached\";"
    f.puts "}"
  end

end
