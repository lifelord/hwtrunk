#ifndef _BASE_SOCKET_SERVER_H_
#define _BASE_SOCKET_SERVER_H_

#include"base_util.h"
#include"base_thread.h"
#include"base_epoll.h"
#include"base_client_pool.h"
#include"base_lock.h"

struct SocketData
{
	uint32 fd;
	Event ev;
	CStream rbuffer;
	CStream wbuffer;
	void* cb;

	SocketData()
	{
		memset(this,0,sizeof(SocketData));
	}
};

typedef map<uint32,SocketData*> MAPSOCKETDATA;

class CSocketServer:public BaseThread
{
public:
	CSocketServer();
	~CSocketServer();

	int Run();
public:
	void Init(uint16 nIP,uint16 nPort,bool et = false);
	void DoRead(Event& ev);
	void DoWrite(Event& ev);
	void Write(uint32 fd,void* buffer,uint32 nlen);
private:
	SocketData* NewSocketData(uint32 fd);
	SocketData* GetSocketData(uint32 fd);
	void DelSocketData(uint32 fd);
private:
	CEpoll m_epoll;
	uint32 m_listenfd;
	MAPSOCKETDATA m_SocketData;
	BaseLock m_Lock;
	bool m_Et;			//是否边缘模式
};

#endif