local io = io
local tonumber = tonumber
local string = string

local protoid_name={}

function string_split( line, sep, maxsplit )
	if string.len(line) == 0 then
		return {}
	end
	sep = sep or ' '
	maxsplit = maxsplit or 0
	local retval = {}
	local pos = 1   
	local step = 0
	while true do   
		local from, to = string.find(line, sep, pos, true)
		step = step + 1
		if (maxsplit ~= 0 and step > maxsplit) or from == nil then
			local item = string.sub(line, pos)
			table.insert( retval, item )
			break
		else
			local item = string.sub(line, pos, from-1)
			table.insert( retval, item )
			pos = to + 1
		end
	end     
	return retval 
end

--初始所有协议表
function init_all()
	local f = assert(io.open("../protocal/proto.conf", 'r'))
  	for count = 1,math.huge do
		local line = f:read("*line")
		if line == nil then
	        break
	    end
	    local d = string_split(line,",")
	    local n = string_split(d[2],".")
	    local proto_id = tonumber(d[1])
	    local name = n[2]
	    protoid_name[name]=proto_id
		protoid_name[proto_id]=name
	end
	f:close()
	--_RUNTIME(sys.dump(protoid_name))
end

function GET_PROTO_NAME(proto_id)
	return protoid_name[proto_id]
end

function GET_PROTOID(name)
	return protoid_name[name]
end

function __init__()
	init_all()
end
