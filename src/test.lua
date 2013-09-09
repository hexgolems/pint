require("src.lib")
print("hallo world from lua\n")
stack = {"begin"}
calls ={}
names ={ begin = "START"}
call_counter = {}

function callback_ret(addr)
	img = Img.find_by_address(addr)
	if img and img:is_main_executable() then
		table.remove(stack,#stack)
	end
end

function get_function_name(addr)
	if names[addr] then return end
	names[addr] = get_addr_repr(addr)
end

function callback_call(addr)
	img = Img.find_by_address(addr)
	if img and img:is_main_executable() then
		call_counter[addr] = call_counter[addr] or 0
		call_counter[addr] = call_counter[addr] + 1
		current = stack[#stack]
		current = current or 0
		calls[current] = calls[current] or {}
		if calls[addr] == nil then calls[addr]={} end 
		if calls[current][addr] == nil then calls[current][addr]=0 end
		calls[current][addr]= calls[current][addr]+1
		table.insert(stack,addr)
	end
end

tcall = TypedCallback.new("IARG_BRANCH_TARGET_ADDR",callback_call)
rcall = TypedCallback.new("IARG_BRANCH_TARGET_ADDR",callback_ret)

function callback_ins(ins)
		if ins:is_call() then
			ins:add_callback( tcall,"BEFORE")
		end
		if ins:is_ret() then
			ins:add_callback( rcall,"BEFORE")
		end
end

CB.instruction(callback_ins)

function at_exit(status)
	for addr, ctr in pairs(call_counter) do
		print("called", addr, ctr, "times")
	end

	local file = io.open("example.txt", "w")
	file:write("digraph g {\n")
	file:write("splines=true; \n sep=\"+10,10\";\n overlap=scalexy;\n nodesep=0.6;\n")
	ids = {}
	index = 0
	for name, toset in pairs(calls) do
		ids[name]="node_"..index
		if names[name] then
			file:write("\t",ids[name]," [shape=box,label=\"",names[name],"\"];\n")
		else
			file:write("\t",ids[name]," [shape=box,label=\"",hex(name),"\"];\n")
		end
		index=index+1
	end

	for from, toset in pairs(calls) do
		for to, count in pairs(toset) do
			if to ~= "/lib64/ld-linux-x86-64.so.2.text._dl_rtld_di_serinfo" and to ~= "/lib64/ld-linux-x86-64.so.2.text.realloc" then
				file:write("\t",ids[from]," -> ",ids[to]," [len = 2, label=",count,"];\n")
			end
		end
	end
	file:write("}\n")
	file:close()
	os.execute("dot -Tsvg example.txt -o call_graph.svg")
end

print("end of lua script\n")