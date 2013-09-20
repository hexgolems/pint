$pin = "./pin/pin"
$target = "/bin/ls"
$target  =%w{/usr/bin/md5sum /usr/bin/md5sum}

$name = "runner"
$tool = $name
$enums =Dir.glob("src/enums/*.cpp").map{|x| x.gsub(/(.cpp|src\/)/,"")}
$fns =Dir.glob("src/gen_fn/*.cpp").map{|x| x.gsub(/(.cpp|src\/)/,"")}
$files= %w{runner lua_class lua_callback pintool_defines}+$enums+$fns
$pin_path="./pin/"
$lua_path="./lua/"
$pin_include_paths = %w{InstLib source/include/pin source/include/pin/gen extras/components/include extras/xed2-intel64/include }

$cc = "clang++" #compiler
$ll = "clang++" #linker

$include_paths = $pin_include_paths.map{|p| $pin_path+p}+[$lua_path+"include"]+%w{src}

$pin_lib_paths = %w{intel64/lib intel64/lib-ext extras/xed2-intel64/lib}
$lib_paths = $pin_lib_paths.map{|p| $pin_path+p}+[$lua_path+"lib"]

$ccflags ="-DBIGARRAY_MULTIPLIER=1 -DUSING_XED -Wall -Werror -DTARGET_IA32E -DHOST_IA32E -fPIC -DTARGET_LINUX -O3 -fomit-frame-pointer -fno-strict-aliasing -g"

$ldflags = "-shared -Wl,--hash-style=sysv -Wl,-Bsymbolic -Wl,--version-script=../../../source/include/pin/pintool.ver -g"

$libs =   %w{pin xed dwarf elf dl lua}

def default
  build
  run
end

def get_cpp_deps(file)
  deps = ["src/#{file}.cpp"]
  File.read("src/#{file}.cpp").lines.each do |line|
    if line =~ /#include\s*"([^"]+)"/
      inc = $1
      ($include_paths+["./src"]).each do |path|
        pt = path + "/" +inc
        deps << pt if File.exists?(pt)
      end
    end
  end
  return deps
end

def check_deps(deps,file)
  return true if !File.exists?(file)
  return deps.any?{ |dep| File.ctime(dep) > File.ctime(file) }
end

def build
  puts "making objects"
  sh("mkdir","-p","output/enums")
  sh("mkdir","-p","output/gen_fn")
  $files.each do |file|
    deps = get_cpp_deps(file)
    puts "dependencies for #{file} : #{deps.inspect}"
    if check_deps(deps, "output/#{file}.o")
      puts "making #{file}"
      cmd = "#{$cc} #{$ccflags} #{
          $include_paths.map{|i| "-I"+i}.join(" ")} -c -o output/#{file}.o src/#{file}.cpp"
      sh(cmd)
      exit 1 unless $?.exitstatus==0
    else
      puts "nothing to be done for #{file}.o"
    end
  end

  puts "making link"
  if check_deps($files.map{|f| "output/#{f}.o"}, "#{$name}.so")
    cmd = "#{$ll} #{$ldflags} -o #{$name}.so #{
        $files.map{|f| "output/#{f}.o"}.join(" ")} #{
        $lib_paths.map{|l| "-L"+l}.join(" ")} #{
        $libs.map{|x| "-l"+x}.join(" ")}"
    sh(cmd)
  else
    puts "nothing to be done for #{$name}.so"
  end
end

def run
  sh($pin, "-injection","child","-t",$tool,"--",*$target)
end

def setup
  deps = %w{libreadline-dev lib32ncurses5-dev lib32stdc++6 clang}
  puts "I'm going to install the following dependencies, you will need sudo for that"
  puts deps
  puts "Do you want me to do that? y/N"
  if STDIN.gets =~/y/
    sh("sudo apt-get install #{deps.join(" ")}")
  end
  sh("sh", "./setup/setup_pin.sh")
  sh("sh", "./setup/setup_lua.sh")
  try_sh("rm","-r", "output")
  sh("mkdir","output")
  build
  run
end

def clean
  try_sh("rm","-r","output")
  try_sh("rm","-r","runner.so")
end

def sh(*cmd)
  puts cmd.join(" ")
  system(*cmd)
  unless $?.exitstatus == 0
    puts "failed .. exiting"
    exit $?.exitstatus
  end
end

def try_sh(*cmd)
  puts cmd.join(" ")
  system(*cmd)
  puts "failed .. ignoring" unless $?.exitstatus == 0
end

if ARGV.length == 0
  default
else
  ARGV.each do |arg|
    self.send(arg)
  end
end
