PINT
====

Pint is a PIN tool that exposes the PIN API to lua scripts.  Pint runs on 64
bit ubuntu and 32 bit windows XP, it should run on 32 bit ubuntu and 64 bit XP as
well but this is yet untested.

PIN is a dynamic instrumentation engine developed by Intel. Basically, it is a
JIT compiler for binaries. It will disassemble the binary, one basic block at a
time, and recompile it with additional instructions inserted at arbitrary
positions. Pint makes it possible to add lua code at this point.

Installation
============
Under Windows
-------------
Make sure you have VC++2010 installed.
Install cygwin and install the following packages: ruby, patch, wget, unzip
Add C:\cygwin\bin to the %PATH% environment variable.
Open a VC++ console.
Move to your prefered directory and run:

```
git clone "https://github.com/hexgolems/pint"
cd pint
ruby make.rb setup
```

The setup target will download pin & lua, apply patches where necessary and
build Pint. The final pintool is called `runner.dll`.

You can then run your lua script with:
`pin.exe -t runner.dll -s path/to/scrip -- binary_to_instrument.exe args for exe`


Under Ubuntu
-----------
Make sure you use ruby1.9 and have git installed and then run:

```
git clone "https://github.com/hexgolems/pint"
cd pint
ruby make.rb setup
```

The setup target will download pin & lua, apply patches where necessary and
build Pint. The final pintool is called `runner.so`.

You can then run your lua script with:

`./pin/pin  -injection child -t runner.dll -s path/to/scrip -- /path/to/binary_to_instrument args for prog`


Usage
=====

Most of the original PIN functions are wrapped to lua. Names are changed
slightly: `INS_IsSomeThing(INS a)` becomes `Ins.is_some_thing(a)` alternatively
given an variable `a` containing an `INS` one can write `a:is_some_thing()`.

Example: Extract Call Graphs
----------------------------

Usecase: You have a C++ program with a load of virtual function calls and you
would like to to extract all the targets of any dymic jump (maybe you can use
this to annotate you code in IDA or SchemDBG). Then you will have to register a
callback for every newly assembled Instruction. This callback will test if the
new instruction is a call/jmp with an unknown target. If so, it will add another
callback that logs the target of the call / jump.

To begin with, we include a small lib with helper functions:
```lua
require("src.lib")
```

Then we need a table that stores all `from`, `to` pairs. We create a new global variable for that:
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

Now we need to create a callback function that is called if we execute the given instruction. It will take a `from`-address, a target and a boolean indicating if the jump was taken. We add the `form`, `to` pair to our mapping.
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

Example: Extract Used Strings
----------------------------
You have some binary and wonder "what strings does it use". Unfortunately, the `strings` util doesn't show any. Maybe the binary contains encrypted/ziped strings? This example shows a tool that will monitor byte size reads to the memory and log any string found. The setup is pretty much the same as in the previous example: There is a callback that gets called once for every new instruction. It checks if the instruction reads one byte from memory, if so an callback is added to this instruction. The callback will peek at the memory address read from, determine if there is a printable string at the given address and if so log the string and the current IP. During runtime, all newly encountered strings are printed to STDOUT, and a precise listing of (address, strings) strings pairs will be printed `at_exit`


```lua
require("src.lib")

print("This tool will take some time")

-- This function checks if all characters in the given string are printable
-- It returns true if so, false otherwise
function is_printable(str)
	if not str then
		return str
	end
	for c in str:gmatch"." do
		b = c:byte(1)
		if b <8 or b > 127 then
			return false
		end
	end
	return true
end

-- table containing string => address that this string was used from mappings
strings = {}

-- This function will use Helper.read_mem(addr, length) to read a string from memory.
-- It will look both forward and backward until it finds a non printable ASCII character
-- It will return nil if [addr..addre+6] do not contain a printable string
-- It returns a string of length < 128 otherwise
-- This string may start bevor the given address (e.G. address does not necessarily point to begin of the string)
function read_string_from(addr)
	local res = ""
	local str = Helper.read_mem(addr,6)
	if str and str:len() < 6 then return nil end
	while true do
		if not is_printable(str) or res:len() > 64 then break end
		res = res .. str
		str = Helper.read_mem(addr+res:len(),1)
	end

	prev = ""
	str = Helper.read_mem(addr-1,1)
	while true do
		if not is_printable(str) or prev:len() > 64 then break end
		prev = str .. prev
		str = Helper.read_mem(addr-prev:len()-1,1)
	end
	res = prev .. res
	if not (res == "") then
		return res
	else
		return nil
	end
end

-- This function is called once every time a one byte read is performed
-- It will try to read a string from the accessed memory. It adds the (string, IP) pair to the global table of encountered strings.
-- It will print the ip and string if this string was encountered for the first time
function rip_string(ip, read_offset)
	str = read_string_from(read_offset)
	if str then
		if not strings[str] then
		print("-- at ",hex(ip),"used",str)
		end
		strings[str] = strings[str] or {}
		strings[str][ip] = true
	end
end

-- This is our TypedCallback. We need IP (IARG_INSTR_PTR) and the address where memory is read (IARG_MEMORYREAD_EA).
ins_call = TypedCallback.new("IARG_INST_PTR","IARG_MEMORYREAD_EA",rip_string)

-- This function is called everytime the JIT Compiler encounters a new instruction the first time.
function callback_ins(ins)
	if ins:is_memory_read() and ins:memory_read_size() == 1 then
		addr = ins:address()
		img = Img.find_by_address(addr)
		-- check that ins belongs to the Main Image
		if img and img:is_main_executable() then
			-- only add the TypedCallback to rip_strings if 
			-- a) ins reads one byte from memory AND 
			-- b) ins is a instruction from the main image
			ins:add_callback( ins_call,"BEFORE")
		end
	end
end
CB.instruction(callback_ins)

-- Print strings vs address Pairs at exit
function at_exit(status)
	for string, addrs in pairs(strings) do
		print(string, ":")
			for addr,_ in pairs(addrs) do
				print(" from:", "0x"..hex(addr))
		end
	end
end

print("end of lua script\n")
```

Additions To The API
========================

Read Memory
-----------

+ `Helper.read_mem(addr,size)`
It will try to read `size` bytes begining from `addr`. It will return a string of length less then or equal to `size`. The string length will be shorter if some parts could not be read since no memory was mapped or other such errors. It will return nil if no bytes were read.

Instrumentation Callbacks
-------------------------
+ `CB.image_load(func)` registers `func` as a callback for every newly loaded image, func will be called with the newly loaded image as first argument.
+ `CB.image_unload(func)` registers `func` as a callback for every unloaded image, `func` will be called with the unloaded image as first argument.
+ `CB.instruction(func)` registers `func` as a callback for newly JITed Instruction, func will be called with the instruction as first argument.
+ `CB.routine(func)` registers `func` as a callback for newly JITed Routines, `func` will be called with the routine as frst argument.
+ `CB.trace(func)` registers `func` as a callback for newly JITed traces (e.g. a single entry multiple exit basic block) , `func` will be called with the trace as frst argument.

In lib.lua
----------
+ `hex(int)` returns a the hex string representing the given integer
+ `hex_str(str,spacer)` returns a strign containing a hex dump of `str` with bytes seperated by `spacer`. If no spacer is given, the bytes are concatenated without any seperation.
+ `get_addr_repr(addr)` Returns a string describing the function containing addr as `filename.section.function` or `filename.section.hex(addr)`

Renamed Functions
-----------------
+ `PIN_set_syntax_XED` is called `Pin.set_syntax_xed`
+ `PIN_set_syntax_ATT` is called `Pin.set_syntax_att`

