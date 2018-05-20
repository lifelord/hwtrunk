#ifndef _BASE_SOCKET_SERVER_H_
#define _BASE_SOCKET_SERVER_H_

#include"base_util.h"
#include"base_thread.h"
#include"base_epoll.h"
#include"base_client_pool.h"
#include"base_lock.h"
#include"base_queue.h"

//用队列去存待发送的消息
class CSocketServer:public BaseThread
{
	class writebuffer
	{
	public:
		writebuffer(int32 nFd,void* pBuff,uint32 nLen)
		{
			fd = nFd;
			len = nLen;
			buff = new char[nLen];
			memmove(buff,pBuff,nLen);
		}
		~writebuffer()
		{
			SAFE_DEL_POINT(buff);
		}
		int32 fd;
		char* buff;
		uint32 len;
	};

	struct QSocket
	{
		int32 fd;
		uint8 type;
		BaseHandler* m_pHandler;

		QSocket()
		{
			memset(this,0,sizeof(this));
		}
	};
public:
	CSocketServer();
	~CSocketServer();

	int Run();
public:
	void RegListenSocket(uint16 nIP,uint16 nPort,BaseHandler* pHandler);

	void RegAcceptSocket(uint32 fd,BaseHandler* pHandler);

	void Init(uint16 nIP,uint16 nPort,BaseHandler* pHandler,bool et = false);
	//返回true,代表事件处理完毕可以跳到下个循环
	bool DoError(Event& ev);
	bool DoRead(Event& ev);
	bool DoWrite(Event& ev);

	//新版DoRead(Event& ev);
	bool DoReadEx(Event& ev);

	bool& GetEdge(){return m_Et;}
public:
	//队列版本
	uint32 Send(int32 fd,void* buff, uint32 nLen);
private:
	CEpoll m_epoll;
	int32 m_listenfd;	//这里应该有个socket池,通过处理消息来注册其中的socket
	BaseHandler* m_pHandler;

	map<uint32,QSocket*> m_Pool;
	bool m_Et;			//是否边缘模式
	
	BaseQueue<writebuffer*> m_pQueue; 
};

#endif