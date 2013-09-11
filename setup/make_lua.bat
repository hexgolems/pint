cl  /O2 /W3 /D_CRT_SECURE_NO_WARNINGS /c *.c
del *.o
ren lua.obj lua.o
ren luac.obj luac.o
ren print.obj print.o
link /DLL /IMPLIB:lua5.2.lib /OUT:lua5.2.dll *.obj
link /OUT:lua.exe lua.o lua5.2.lib
lib /out:lua5.2-static.lib *.obj
link /OUT:luac.exe luac.o print.o lua5.2-static.lib