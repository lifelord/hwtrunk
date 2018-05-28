local old_path = package.path

--将protobuffer.lua加入到package.path中
local p = "/home/game/server/hwtrunk/Trd/pbc"

local workpath = "/home/game/server/hwtrunk/protocal/?.lua;/home/game/server/hwtrunk/game/lua/?.lua;"

package.path = string.format("%s;%s/?.lua;%s",old_path,p,workpath)

--print("luapath = " .. package.path)

--将将protobuffer.so加入到package.cpath
local protobuff_path = "/home/game/server/hwtrunk/Trd/pbc/?.so"

package.cpath = string.format("%s;%s",protobuff_path,package.cpath)

--print("cluapath = ".. package.cpath)

PROTO_ENV = {}
PROTO_LISTENER = {}

function ProtoRegister(protoName, listenerName)
	local env = getfenv(2)
	if not env then
		error(string.format("Register proto:%s not env", protoName))
	end
	if not env[listenerName] or type(env[listenerName]) ~= "function" then
		error(string.format("Register proto:%s not listener:%s, listenerName must be global function name", protoName, listenerName))
	end

	PROTO_ENV[env] = PROTO_ENV[env] or {}
	PROTO_ENV[env][protoName] = listenerName
	PROTO_LISTENER[protoName] = env[listenerName]
end

dofile("../game/lua/update.lua")

PBC = Import("../Trd/pbc/pbc.lua")
PROTOCALINFO = Import("../protocal/protocol_info.lua")
LOGIN = Import("../game/lua/login.lua")

function OnLuaRecv(vfd,cmd,ProtoMsg)
	local protoName = PROTOCALINFO.GET_PROTO_NAME(cmd)

	if protoName and  PROTO_LISTENER[protoName] then
		local DecodeMsg = PBC.decode(protoName, ProtoMsg)

		PROTO_LISTENER[protoName](vfd,ProtoMsg)
	end
end

print("load preload.lua")