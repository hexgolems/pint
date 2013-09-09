rm -rf lua
wget "http://www.lua.org/ftp/lua-5.1.4.tar.gz"
tar -xf lua-5.1.4.tar.gz
rm lua-5.1.4.tar.gz
mv lua-5.1.4 lua
cd lua/src
wget "http://files.luaforge.net/releases/lnum/lnum/lnum-2009/lua514-lnum-20090417.patch.tgz"
tar -xf lua514-lnum-20090417.patch.tgz
mv lua514-lnum-20090417.patch lnum.patch
patch < lnum.patch
patch < ../../setup/lnum64.patch
patch < ../../setup/makefile_fpic.patch
patch < ../../setup/lua_patch_to_old_c.patch
cp ../../setup/make_lua.bat .
./make_lua.bat
cp lua5.2-static.lib ..
cd ..
mkdir "include"
cp src/lua.h src/luaconf.h src/lualib.h src/lauxlib.h etc/lua.hpp include
cd ..
