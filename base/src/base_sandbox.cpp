#include"base_sandbox.h"

CSandBox::CSandBox()
{}

CSandBox::~CSandBox()
{}

bool CSandBox::Init()
{
	if(m_pState != NULL) return false;

	m_pState =  lua_open();

	if(m_pState == NULL)
	{
		cout << "luaL_newstate failed" << endl; 

		return false; 
	}
	luaL_openlibs(m_pState);
	
	//PrintLuaStack(m_pState);

	return true;
}

bool CSandBox::Load(const char* path)
{
	if(m_pState == NULL)
	{
		cout << "load error:m_pState=NULL" << endl;
		return false;
	} 

	int ret = luaL_dofile(m_pState, path);

	if(ret != 0)
	{	
		int t = lua_type(m_pState, -1);  
        const char* err = lua_tostring(m_pState,-1);  
        printf("Error: %s\n", err);  
        lua_pop(m_pState, 1);

		return false;
	}

	//load完file要运行一下,才能实际加载完成
	/*ret = lua_pcall(m_pState, 0, 0, 0);
    if (ret != 0)
    {
    	cout << "do file error:path=" << path << endl;
        return false;
    }*/

	
	//PrintLuaStack(m_pState);

	return true;
}

void CSandBox::PrintLuaStack(lua_State *L)
{  
    fprintf(stderr, "================栈顶================\n");  
    fprintf(stderr, "   索引  类型          值\n");  
    for(int nIndex = lua_gettop(L); nIndex > 0; --nIndex)
    {  
        int nType = lua_type(L, nIndex);
        switch(nType)
        {
        	case LUA_TSTRING:
        	{
        		fprintf(stderr,"   (%d)  %s         %s\n",nIndex,   
        				lua_typename(L,nType), lua_tostring(L,nIndex));  
        	}break;
        	case LUA_TNUMBER:
        	{
        		fprintf(stderr,"   (%d)  %s         %d\n",nIndex,   
        				lua_typename(L,nType), lua_tonumber(L,nIndex));
        	}break;
        	case LUA_TFUNCTION:
        	{
        		fprintf(stderr,"   (%d)  %s         %s\n",nIndex,   
        				lua_typename(L,nType), lua_tostring(L,nIndex));
        	}break;
        	default:
        		break;
        }  
    }  
    fprintf(stderr, "================栈底================\n");
} 

bool CSandBox::CallFunc(const char* protoname,uint32 vfd,uint32 cmd,void* buff)
{
	//PrintLuaStack(m_pState);

	lua_getglobal(m_pState,"PROTO_LISTENER");

	if (!lua_istable(m_pState, -1))
	{
		cout << "PROTO_LISTENER not table" << endl;
		return false;
	}

	lua_getfield(m_pState,-1,protoname);

	//lua_getglobal(m_pState,func);

	lua_pushnumber(m_pState, vfd);

	lua_pushlightuserdata(m_pState, buff);

	//返回结果要从m_pState pop掉
	int ret = lua_pcall(m_pState, 2, 0, 0);

	if ( ret != 0 )  
    {  
        int t = lua_type(m_pState, -1);  
        const char* err = lua_tostring(m_pState,-1);  
        printf("Error: %s\n", err);  
        lua_pop(m_pState, 1);  
     }  
}

bool CSandBox::CallLuaFunc(const char* funcname,uint32 vfd,uint32 cmd,void* buff)
{
	lua_getglobal(m_pState,funcname);
	lua_pushnumber(m_pState, vfd);
	lua_pushnumber(m_pState, cmd);
	lua_pushlightuserdata(m_pState, buff);

	//返回结果要从m_pState pop掉
	int ret = lua_pcall(m_pState, 3, 0, 0);

	if ( ret != 0 )  
    {  
        int t = lua_type(m_pState, -1);  
        const char* err = lua_tostring(m_pState,-1);  
        printf("Error: %s\n", err);  
        lua_pop(m_pState, 1);  
     }  
}