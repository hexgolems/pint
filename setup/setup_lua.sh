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
cd ..
make linux
make local
