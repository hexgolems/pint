require("src.lib")

stack = {"begin"}
calls ={}
names ={ begin = "START"}

function callback_ret()
	table.remove(stack,#stack)
end

function get_function_name(addr)
	if names[addr] then return end
	names[addr] = get_addr_repr(addr)
end

function callback_call(addr)
	get_function_name(addr)
	current = stack[#stack]
	if calls[current] == nil then calls[current]={} end
	if calls[addr] == nil then calls[addr]={} end 
	if calls[current][addr] == nil then calls[current][addr]=0 end
	calls[current][addr]= calls[current][addr]+1
	table.insert(stack,addr)
end

tcall = TypedCallback.new("IARG_BRANCH_TARGET_ADDR",callback_call)
rcall = TypedCallback.new(callback_ret)

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
