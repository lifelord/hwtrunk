--热更思路
_G._ImportModule = _G._ImportModule or {}

function Import(pathFile)
	if _G._ImportModule[pathFile] then
		return _G._ImportModule[pathFile]
	end

	local func, err = loadfile(pathFile)
	local New = {}
	_G._ImportModule[pathFile] = New
	setmetatable(New, {__index = _G})
	setfenv(func, New)()
	if New.__init__ then
		New.__init__()
	end
	return New
end

--某些关键函数不进行替换
local protection = {
    setmetatable = true,
    pairs = true,
    ipairs = true,
    next = true,
    require = true,
    --_ENV = true,
}

local visited_sig = {}
function Upd_table(oldTable,newTable,name,deepth)
	if protection[oldTable] or protection[newTable] then return end
	if oldTable == newTable then return end

	local signature = tostring(oldTable) .. tostring(newTable)
	if visited_sig[signature] then return end

	visited_sig[signature] = true
	--遍历对比值，如进行遍历oldTable类似的步骤
    for name, value in pairs(newTable) do
    	local old_value = oldTable[name]
    	if type(value) ~= type(old_value) then
    		if type(value) == 'function' then
    			Upd_func(old_value, value, name, deepth..'  '..name..'  ')
    			oldTable[name] = value
    		elseif type(value) == 'table' then
    			Upd_table(old_value,value,name,deepth..'  '..name..'  ')
    		end
    	else
    		oldTable[name] = value
    	end
    end

    --遍历table的元表，进行对比
    local old_meta = debug.getmetatable(oldTable)
    local new_meta = debug.getmetatable(newTable)

    if type(old_meta) == 'table' and type(new_meta) == 'table' then
        update_table(new_meta, old_meta, name..'s Meta', deepth..'  '..name..'s Meta'..'  ' )
    end
end

--热更upvalue,由于新加载的文件函数是newfunc
--newfunc与oldfunc名字应该相同,地址不同而已,要将oldfunc中的数据传回给newfunc中,才能保证热更数据不被破坏
function Upd_func(oldfunc,newfunc,name,deepth)
	local OldUpvalueMap = {}

	local OldExistName = {}

	--记录oldfunc的upvalue表
	for i = 1,math.huge do
		local name,value = debug.getupvalue(oldfunc,i)
		if not name then break end
		OldUpvalueMap[name] = value
		OldExistName[name] = true
	end

	--newfunc与oldfunc相同部分更新,不同部分newfunc维持原样
	for i = 1,math.huge do
		local name,value = debug.getupvalue(newfunc,i)
		if not name then break end

		if OldExistName[name] then
			local oldValue = OldUpvalueMap[name]
			--类型不一致,用旧值
			if type(oldValue) ~= type(value) then
				debug.setupvalue(newfunc,i,oldValue)
			--类型为函数
			elseif type(oldValue) == "function" then
				Upd_func(oldValue,value,name,nil,deepth.."    ") 
			--类型为表
			elseif type(oldValue) == "table" then
				Upd_table(oldValue,value,name,deepth.."    ")  
	            debug.setupvalue(newfunc,i,oldValue)
			else
				--其他数据类型没有变
				debug.setupvalue(newfunc,i,oldValue)
			end
		end
	end
end

--Oldfunc为老环境,New为新环境
function HotFix(pathFile)
	local Oldfunc = _G._ImportModule[pathFile]

	--重新load文件,返回Proto
	local func, err = loadfile(pathFile)

    if not err then
    	--热更文件
    	local New = {}
	    setmetatable(New, {__index = Oldfunc})
	    setfenv(func,New)()

	    for name,value in pairs(New) do
	    	--新老环境变量名相同的
	    	local oldvalue = Oldfunc[name]
	    	if oldvalue then
	   			if type(oldvalue) ~= type(value) then
	        		Oldfunc[name] = value --新值覆盖老值,热更的代码最好不要改变变量(name)对应值的类型
	    		elseif type(value) == 'function' then
	    			--函数类型,用[老函数oldvalue]中upvalue变量的值覆盖[新函数value]中upvalue中变量的值
	        		Upd_func(oldvalue,value,name,'G'..'  ')
	        		--Oldfunc[name]=value指向热更文件加载在内存中新函数的地址
	        		Oldfunc[name] = value
	    		elseif type(value) == 'table' then--table类型，合并新老table及其元表
	        		Upd_table(oldvalue,value,name,'G'..'  ')
	    		end
	    	else
	    		Oldfunc[name] = value--新增元素
	    	end
	    end

	    if Oldfunc.__init__ then
	    	Oldfunc.__init__()
	    end
	else
		print(err)
	end
end