#ifndef BASE_UNPACK_H
#define BASE_UNPACK_H

#include "base_util.h"
#include "base_epoll.h"
#include "base_thread.h"
#include "base_client_pool.h"
#include "base_lock.h"
#include "base_stream.h"


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

	int Run();
public:
	virtual void accept_handler(uint32 fd,uint32 nhost);
	virtual void recv_handler(uint32 fd,void* buff,uint32 nlen);
	virtual void close_handler(uint32 fd);
	virtual void write_handler(uint32 fd);
private:
	map<uint32,UnPack*> m_Pool;
	BaseLock m_lock;
	BaseSema m_sem;
	map<uint32,uint32> m_MsgCount;
};

#endif