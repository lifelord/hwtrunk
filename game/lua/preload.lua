local old_path = package.path

--将protobuffer.lua加入到package.path中
local p = "3rd/pbc/binding/lua/" 
package.path = string.format("%s;%s/?.lua;%s/?/init.lua;",old_path,p,p)

--将将protobuffer.so加入到package.cpath
local protobuff_path = "3rd/pbc/binding/lua/?.so;"
package.cpath = string.format("%s;%s",protobuff_path,package.cpath)

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

print("load preload.lua")

dofile("../game/lua/login.lua")

package.path