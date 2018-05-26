local table=table
local math=math
local pairs=pairs

function OnLogin(vfd,ProtoMsg)
	print("OnLogin,vfd,ProtoMsg:" .. tostring(vfd) .. "," .. tostring(ProtoMsg))
end

function __init__()
	print("login.lua,__init__")
	ProtoRegister("C2s_hero_login","OnLogin")
end

__init__()