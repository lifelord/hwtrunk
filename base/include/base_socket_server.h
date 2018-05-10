#ifndef _BASE_SOCKET_SERVER_H_
#define _BASE_SOCKET_SERVER_H_

#include"base_util.h"
#include"base_thread.h"
#include"base_epoll.h"
#include"base_client_pool.h"
#include"base_lock.h"
#include"base_queue.h"

class CSocketServer:public BaseThread
{
public:
	CSocketServer();
	~CSocketServer();

	int Run();
public:
	void Init(uint16 nIP,uint16 nPort,BaseHandler* pHandler,bool et = false);
	void DoError(Event& ev);
	void DoRead(Event& ev);
	void DoWrite(Event& ev);
private:
	CEpoll m_epoll;
	uint32 m_listenfd;
	bool m_Et;			//是否边缘模式
	BaseHandler* m_pHandler;
};

#endif