#include <iostream>
#include <fstream>
#include "pin.H"
#include "lua.h"
#include "gen_fn/lua_img.h"


#include <iostream>
#include <fstream>
using namespace std;

Lua lua;

KNOB<string> KnobOutputFile(KNOB_MODE_WRITEONCE, "pintool", "o", "runner.out", "specify output file name");
KNOB<string> KnobScriptFile(KNOB_MODE_WRITEONCE, "pintool", "s", "tools/strings.lua", "specify the lua script to be run");

INT32 Usage()
{
    cerr << "This allows to call a lua script on every callback" << endl;
    cerr << endl << KNOB_BASE::StringKnobSummary() << endl;
    return -1;
}

VOID Finish(INT32 code, VOID *v)
{
  lua.done(code);
}

int main(int argc, char * argv[])
{
    // Initialize pin
    if (PIN_Init(argc, argv)) return Usage();

    PIN_AddFiniFunction(Finish, 0);
    printf("setting up lua\n");
    lua.setup(KnobScriptFile.Value());

    printf("running host\n");
    PIN_InitSymbols();
    PIN_StartProgram();

    return 0;
}
