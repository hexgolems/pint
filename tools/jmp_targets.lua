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
