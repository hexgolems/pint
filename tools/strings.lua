require("src.lib")


print("This tool will take some time")

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

strings = {}

function read_string_from(addr)
	local res = ""
	local str = Helper.read_mem(addr,6)
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

function rip_string(ip, read_offset)
	str = read_string_from(read_offset)
	if str then
		if not strings[str] then
		print("--",str)
		end
		strings[str] = strings[str] or {}
		strings[str][ip] = true
	end
end

ins_call = TypedCallback.new("IARG_INST_PTR","IARG_MEMORYREAD_EA",rip_string)

function callback_ins(ins)
	if ins:is_memory_read() and ins:memory_read_size() == 1 then
		addr = ins:address()
		img = Img.find_by_address(addr)
		if img and img:is_main_executable() then
			ins:add_callback( ins_call,"BEFORE")
		end
	end
end

CB.instruction(callback_ins)

function at_exit(status)
	for string, addrs in pairs(strings) do
		print(string, ":")
			for addr,_ in pairs(addrs) do
				print(" from:", "0x"..hex(addr))
		end
	end
end

print("end of lua script\n")
