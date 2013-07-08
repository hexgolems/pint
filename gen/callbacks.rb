require './template_callback.rb'
require 'set'

callbacks = {}
File.read("./callbacks.txt").lines.each do |line|
  base,name, func = line.split(" ")
  callbacks[base]||=Set.new
  callbacks[base].add [name,func]
end

includes = []
tbl = []

callbacks.each_pair do |base, funcs|
  bl = base.downcase
  File.open("./callbacks/lua_#{bl}_callbacks.h","w") do |f|
    f.puts header(base,funcs.map{|(name,pin_name)| name})
  end

  File.open("./callbacks/lua_#{bl}_callbacks.cpp","w") do |f|
    f.puts cpp(base,funcs)
  end

  includes << "#include \"gen_fn/lua_#{bl}_callbacks.h\""
  funcs.each do |(name,_)|
    tbl << "{\"#{bl}_#{name}\",register_#{bl}_#{name}},"
  end

end

puts includes
puts ""
puts "const struct luaL_reg callbacks_lib [] = {"
puts tbl
puts "{NULL, NULL}
};"


