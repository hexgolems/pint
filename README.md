PINT
====

Pint is a PIN tool that exposes the PIN API to lua scripts.
Pint runs on 64 bit linux and 32 bit windows XP, it should run on 32 bit linux and 64 bit XP as well(untested). 

PIN is a dynmic instrumentation engine developed by intel. Basically its a JIT compiler for binaries. It will disassemble the binary, one basic block at a time, and recompile it with additional instructions inserted in arbitrary positions. Pint makes it possible to add lua code at this point. 

Install
=======
Under Windows
-------------
Make sure you have VC++2010 installed.
Install cygwin and install the following packages: ruby, patch, wget, unzip
Add C:\cygwin\bin to the %PATH& environment variable.
Open a VC++ console.
Move to your prefered directory.
run 
```
git clone "https://github.com/hexgolems/pint"
cd pint
ruby make.rb setup
```
The setup target will download pin & lua, apply patches where necessary and build Pint. The final pintool is called `runner.dll`.

You can then run your lua script as:
`pin.exe -t runner.dll -s path/to/scrip -- binary_to_instrument.exe args for exe`


Under Linux
-----------

make sure you use ruby1.9 and have git installed

```
git clone "https://github.com/hexgolems/pint"
cd pint
ruby make.rb setup
```

The setup target will download pin & lua, apply patches where necessary and build Pint. The final pintool is called `runner.so`.

You can then run your lua script wiht:

`./pin/pin  -injection child -t runner.dll -s path/to/scrip -- /path/to/binary_to_instrument args for prog`


Usage
=====

Most of the original PIN functions are wrapped to lua. Names are changed slightly: `INS_IsSomeThing(INS a)` becomes `Ins.is_some_thing(a)` alternatively given an variable `a` containing an `INS` one can write `a:is_some_thing()`.

Example: Extract Call Graphs
----------------------------

Usecase: You have a C++ program with a shitload of virtual function calls. You want to extract all the targets of any dymic jump (maybe you can use this to annotate you code in IDA or SchemDBG). You will have to register a callback for every newly assembled Instruction. This callback will test if the new instruction is a call/jmp with an unknown target. If so It will add another callback that logs the target of the call / jump.

To begin with, we include a small lib with helper functions:
```lua
require("src.lib")
```

Then we need a table that stors all from, to pairs. We create a new global variable for that:
```lua
jmps = {}
```

The next step is to create a function that is called once for every instruction that we recompile:
```lua
function callback_ins(ins)
	--do something with the instruction
end

CB.instruction(callback_ins)
```

Now we need to create a callback function that is called if we execute the given instruction. It will take a from address, a target and a boolean indicating if the jump was taken. We add the form, to pair to our map.
```lua
function callback_jmp(from, to, was_taken)
	if was_taken then 
		jmps[from] = jmps[from] or {}
		jmps[from][to] = true
	end
end
```

Now we need to add the newly created callback to all instructions that interesst us. To do so we will test if the given instruction is a indirect call or jump (e.G. the target is determined at runtime). Then we add our callback to the instruction. To do so we first need to create a so called TypedCallback. A TypedCallback is an object that knows which values pin needs to pass to the callback. 

```lua
jcall = TypedCallback.new("IARG_INST_PTR","IARG_BRANCH_TARGET_ADDR", "IARG_BRANCH_TAKEN", callback_jmp)

function callback_ins(ins)
		if ins:is_indirect_branch_or_call() then
			ins:add_callback( jcall,"BEFORE")
		end
end
```

To wrap things up, we need to add a function that will be called uppon the debugee exiting. This function will print the list pairs to stdout. Note that this will only properly work under Linux. Under windows the output will be printed into a logfile since the process will close STDOUT/STDIN when exiting. Under Linux this was fixed by duping the fds. Under Windows we only reopen some log files as STDOUT/STDERR.

```lua
function at_exit(status)
	for addr, targets in pairs(jmps) do
		for target, _ in pairs(targets) do
			print( hex(addr),"-->", hex(target))
		end
	end
end
```

Thus the entire code for extracting a list of all call/jmp targets is just 28 lines of lua. Additional samples can be found in `src/tools`
```lua
require("src.lib")

jmps = {}

function callback_jmp(from, to, was_taken)
	if was_taken then 
		jmps[from] = jmps[from] or {}
		jmps[from][to] = true
	end
end

jcall = TypedCallback.new("IARG_INST_PTR","IARG_BRANCH_TARGET_ADDR", "IARG_BRANCH_TAKEN", callback_jmp)

function callback_ins(ins)
		if ins:is_indirect_branch_or_call() then
			ins:add_callback( jcall,"BEFORE")
		end
end

CB.instruction(callback_ins)

function at_exit(status)
	for addr, targets in pairs(jmps) do
		for target, _ in pairs(targets) do
			print( hex(addr),"-->", hex(target))
		end
	end
end
```
