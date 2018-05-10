#ifndef BASE_UNPACK_H
#define BASE_UNPACK_H

#include "base_util.h"
#include "base_epoll.h"
#include "base_thread.h"
#include "base_client_pool.h"
#include "base_lock.h"

class UnPackHandler:public BaseHandler,public BaseThread
{
public:
	UnPackHandler();
	~UnPackHandler();

	int Run();
public:
	virtual void accept_handler(uint32 fd);
	virtual void recv_handler(uint32 fd,void* buff,uint32 nlen);
	virtual void close_handler(uint32 fd);
	virtual void write_handler(uint32 fd);
private:
	map<uint32,BaseUser*> m_Pool;
	BaseLock m_lock;
	vector<BaseUser*> m_User;
};

#endif