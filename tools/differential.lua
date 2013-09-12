require("src.lib")

basic_blocks = {}

function visit_bbl(ip)
	basic_blocks[ip] = true
end

bbl_call = TypedCallback.new("IARG_INST_PTR",visit_bbl)

function callback_trace(trace)
		addr = trace:address()
		img = Img.find_by_address(addr)
		if img and img:is_main_executable() then
			bbl = trace:bbl_head()
			while bbl do
				bbl:add_callback(bbl_call,"BEFORE")
				bbl = bbl:next()
			end
		end
end

CB.trace(callback_trace)

function at_exit(status)
	for addr, _ in pairs(basic_blocks) do
		print(hex(addr))
	end
end

print("end of lua script\n")
