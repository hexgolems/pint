$pin = "pin.exe"
$target = "/bin/ls"
$target  =%w{cmd.exe}

$src ="src"

$name = "runner"
$tool = $name
$enums =Dir.glob("#{$src}/enums/*.cpp").map{|x| x.gsub(/(.cpp|#{$src}\/)/,"")}
$fns =Dir.glob("#{$src}/gen_fn/*.cpp").map{|x| x.gsub(/(.cpp|#{$src}\/)/,"")}
$files= %w{runner lua lua_callback pintool_defines}+$enums+$fns
$pin_path="./pin/win/"
$lua_path="./lua/"


$cc = "cl" #compiler

$ccflags ="/DBIGARRAY_MULTIPLIER=1 /DUSING_XED /D_CRT_SECURE_NO_DEPRECATE /DTARGET_WINDOWS /DHOST_IA32 /MT /EHs- /EHa- /wd4530 /D_SECURE_SCL=0 /nologo /Gy /DTARGET_IA32 /DHOST_IA32 /O2"

$pin_include_paths = %w{source/tools/InstLib source/include/pin source/include/pin/gen extras/components/include extras/xed2-ia32/include }
$lua_include_paths = %w{include}
$include_paths = $pin_include_paths.map{|p| $pin_path+p} + $lua_include_paths.map{|p| $lua_path+p} +[$src]


$ll = "link" #linker

$ldflags = "/DLL /EXPORT:main /NODEFAULTLIB /NOLOGO /INCREMENTAL:NO /MACHINE:x86 /ENTRY:Ptrace_DllMainCRTStartup@12 /BASE:0x55000000 /OPT:REF"

$libs =   %w{pin pinvm libxed libcpmt libcmt kernel32 ntdll-32 lua5.2-static}
$pin_lib_paths = %w{ia32/lib ia32/lib-ext extras/xed2-ia32/lib}
$lib_paths = $pin_lib_paths.map{|p| $pin_path+p}+[$lua_path+"src"]

=begin
cl /I../lua/include /MT /EHs- /EHa- /wd4530 /DTARGET_WINDOWS /DBIGARRAY_MULTIPLIER=1  /DUSING_XED /D_CRT_SECURE_NO_DEPRE
CATE /D_SECURE_SCL=0 /nologo /Gy /DTARGET_IA32 /DHOST_IA32  /I../pin/win/source/include/pin  /I../pin/win/source/include
/pin/gen /I../pin/win/extras/components/include  /I../pin/win/extras/xed2-ia32/include  /I../pin/win/source/tools/InstLi
b /O2  /c /Foobj-ia32/MyPinTool.obj MyPinTool.cpp
MyPinTool.cpp
link /DLL /EXPORT:main /NODEFAULTLIB /NOLOGO /INCREMENTAL:NO /MACHINE:x86 /ENTRY:Ptrace_DllMainCRTStartup@12 /BASE:0x550
00000 /OPT:REF  /out:obj-ia32/MyPinTool.dll obj-ia32/MyPinTool.obj  /LIBPATH:../pin/win/ia32/lib  /LIBPATH:../pin/win/ia
32/lib-ext /LIBPATH:../pin/win/extras/xed2-ia32/lib /LIBPATH:../lua/src pin.lib libxed.lib libcpmt.lib libcmt.lib pinvm.
lib kernel32.lib ntdll-32.lib lua5.2-static.lib
   Creating library obj-ia32/MyPinTool.lib and object obj-ia32/MyPinTool.exp
=end

#cmdlin = "#{$cc} #{$lags} #{$includes} /c /Foobj-ia32/runner.obj runner.cpp"


#libs = "pin.lib libxed.lib libcpmt.lib libcmt.lib pinvm.lib kernel32.lib ntdll-32.lib lua5.2-static.lib"
#cmdline = "#{ll} /out:obj-ia32/runner.dll obj-ia32/runner.obj #{libs}"

def default
  build
  run
end

def get_cpp_deps(file)
  deps = [$src+"/#{file}.cpp"]
  File.read($src+"/#{file}.cpp").lines.each do |line|
    if line =~ /#include\s*"([^"]+)"/
      inc = $1
      ($include_paths+["./"+$src]).each do |path|
        pt = path + "/" +inc
        deps << pt if File.exists?(pt)
      end
    end
  end
  return deps
end

def check_deps(deps,file)
  return true
  return true if !File.exists?(file)
  return deps.any?{ |dep| File.ctime(dep) > File.ctime(file) }
end

def build
  puts "making objects"
  sh("mkdir","-p","output/enums")
  sh("mkdir","-p","output/gen_fn")
  $files.each do |file|
    deps = get_cpp_deps(file)
 #   puts "dependencies for #{file} : #{deps.inspect}"
    if check_deps(deps, "output/#{file}.o")
      puts "making #{file}"
      cmd = "#{$cc} #{$ccflags} #{
          $include_paths.map{|i| "/I"+i}.join(" ")} /c /Fooutput/#{file}.obj #{$src}/#{file}.cpp"
      sh(cmd)
      exit 1 unless $?.exitstatus==0
    else
      puts "nothing to be done for #{file}.o"
    end
  end

  puts "making link"
  if check_deps($files.map{|f| "output/#{f}.obj"}, "#{$name}.dll")
    cmd = "#{$ll} #{$ldflags} /out:#{$name}.dll #{
        $files.map{|f| "output/#{f}.obj"}.join(" ")} #{
        $lib_paths.map{|l| "/LIBPATH:"+l}.join(" ")} #{
        $libs.map{|x| x+".lib"}.join(" ")}"
    sh(cmd)
  else
    puts "nothing to be done for #{$name}.dll"
  end
end

def run
  sh($pin,"-t",$tool+".dll","--",*$target)
  puts "running completed"
end

def setup
  puts "You need to install VC++2010"
  puts "then install cygwin and the following packages: ruby, patch, wget, unzip"
  puts "add C:/cygwin/bin (or whatever your cygwin path is) to the %PATH% variable"
  sh("sh","setup/setup_lua_win.sh")
  sh("sh","setup/setup_pin_win.sh")
end

def clean
  sh("rm *.out")
end

def sh(*cmd)
#  puts cmd.join(" ")
  system(*cmd)
  exit $?.exitstatus unless $?.exitstatus == 0
end

if ARGV.length == 0
  default
else
  ARGV.each do |arg|
    self.send(arg)
  end
end
