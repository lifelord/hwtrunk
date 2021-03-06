#ifndef _BASE_SANDBOX_H
#define _BASE_SANDBOX_H

#include "base_util.h"

class CSandBox
{
public:
	CSandBox();
	~CSandBox();
public:
	bool Init();
	bool Load(const char* path);
	bool CallFunc(const char* protoname,uint32 vfd,uint32 cmd,void* buff);
	bool CallLuaFunc(const char* funcname,uint32 vfd,uint32 cmd,void* buff);
	void PrintLuaStack(lua_State *L);
private:
	lua_State* m_pState;
};

#endif