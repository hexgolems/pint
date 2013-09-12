
io.write("Running pinrunner from ",_VERSION,"!\n")
Pin.set_syntax_intel()


function hex_str(str,spacer)
  return (
    string.gsub(str,"(.)",
    	function (c)
         return string.format("%02X%s",string.byte(c), spacer or "")
        end)
     )
end

function hex(num)
	return string.format("%x",num)
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
	local _,_,file_name = string.find(img_name, "/([^/]*)$") 
	local sec_name = sec:name()
	if func_name and func_name ~= sec_name then
		return file_name..sec_name.."."..func_name
	else
		return file_name..sec_name.."."..hex(addr)
	end
end
