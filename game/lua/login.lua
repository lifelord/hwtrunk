local table=table
local math=math
local pairs=pairs

function OnPlayerAdd(vfd,ProtoMsg)
	print("OnPlayerAdd,vfd,ProtoMsg:" .. tostring(vfd) .. "," .. tostring(ProtoMsg))
end

function __init__()
	ProtoRegister("C2s_login_player_add","OnPlayerAdd")
end