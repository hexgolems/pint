
io.write("Running pinrunner from ",_VERSION,"!\n")
Pin.set_syntax_intel()

function hex(num)
	return string.format("%x",num)
end



local function csplit(str,sep)
	local ret={}
	local n=1
	for w in str:gmatch("([^"..sep.."]*)") do
		ret[n]=ret[n] or w -- only set once (so the blank after a string is ignored)
		if w=="" then n=n+1 end -- step forwards on a blank but not a string
	end
	return ret
end

function get_addr_repr(addr)

	if addr == "begin" then
		return "START"
	end

	addr = tonumber(addr)
	local img = Img.find_by_address(addr)
	if not img then
		return hex(addr)
	end
		
	local sec = img:sec_head()
	while sec do
		local secaddr = sec:address()
		local secsize = sec:size()
		if secaddr<=addr and secaddr+secsize >= addr then
			break
		end
		sec = sec:next()
	end

	local func_name = Rtn.find_name_by_address(addr)
	local img_name = img:name()
	local path = csplit(img_name,"/")
	local file_name = path[#path]
	local sec_name = sec:name()
	if func_name and func_name ~= sec_name then
		return file_name..sec_name.."."..func_name
	else
		return file_name..sec_name.."."..hex(addr)
	end
end
