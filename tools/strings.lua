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
