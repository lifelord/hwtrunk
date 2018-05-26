#ifndef BASE_UNPACK_H
#define BASE_UNPACK_H

#include "base_util.h"
#include "base_thread.h"
#include "base_client_pool.h"
#include "base_lock.h"
#include "base_stream.h"
#include "base_sandbox.h"

class BaseHandler
{
public:
	BaseHandler(){}
	virtual ~BaseHandler(){}
public:
	virtual void accept_handler(int32 fd,uint32 nhost,uint8 servertype) = 0;
	virtual void recv_handler(int32 fd,void* buff,uint32 nlen) = 0;
	virtual void close_handler(int32 fd) = 0;
	virtual void write_handler(int32 fd) = 0;
};

class UnPackHandler:public BaseHandler,public BaseThread
{
private:
	struct UnPack
	{
		BaseUser* pUser;//解包类
		CStream stream;//接收网络数据
	};
public:
	UnPackHandler();
	~UnPackHandler();

	void Init(const char* path);

	int Run();
public:
	virtual void accept_handler(int32 fd,uint32 nhost,uint8 servertype);
	virtual void recv_handler(int32 fd,void* buff,uint32 nlen);
	virtual void close_handler(int32 fd);
	virtual void write_handler(int32 fd);
private:
	map<uint32,UnPack*> m_Pool;
	BaseLock m_lock;
	BaseSema m_sem;
	map<uint32,uint32> m_MsgCount;
	//沙盒暂时放这里
	CSandBox m_SandBox;
};

#endif