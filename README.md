pint
====

A debugger backend and LUA wrapper for PIN


run
`./make setup`
this will download pin and lua as well as apply the neccessary patches to the lua sources. 
Then it will compile lua as well as the runner (clang and gcc are both needed)
`./make run`
this will run the runner.so pintool on md5sum. It will execute the src/test.lua script
