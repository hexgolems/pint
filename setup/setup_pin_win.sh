rm -rf pin/win
wget "http://software.intel.com/sites/landingpage/pintool/downloads/pin-2.12-58423-msvc10-windows.zip"
unzip "pin-2.12-58423-msvc10-windows.zip"
rm "pin-2.12-58423-msvc10-windows.zip"
mv pin-2.12-58423-msvc10-windows pin/win
cp pin/win/ia32/bin/* .