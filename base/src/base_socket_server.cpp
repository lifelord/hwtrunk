#include "base_socket_server.h"

CSocketServer::CSocketServer()
{
}

CSocketServer::~CSocketServer()
{
}

bool CSocketServer::DoError(Event& ev)
{
	if(ev.error)
	{
		m_epoll.Efd_del(ev.fd);
		close(ev.fd);

		cout << "DoError close" << ev.fd << endl;
		return true;
	}
	return false;
}

bool CSocketServer::DoRead(Event& ev)
{
	//处理读事件
	if(ev.read)
	{
		//1、接收新socket
		if (ev.fd == m_listenfd)
		{
			//accept a new socket
			uint32 newfd = accept(ev.fd,NULL,NULL);

			m_epoll.Efd_add(newfd,NULL,m_Et);
			//新连接
			m_pHandler->accept_handler(newfd,0);

			cout << "DoRead:accept fd:" << newfd << endl;

			return true;
		}else
		{
			for(;;)
			{
				static char buff[1024];

				int32 nSize = recv(ev.fd, buff, sizeof(buff), MSG_DONTWAIT);

				if( nSize > 0)
				{
					//接收数据
					m_pHandler->recv_handler(ev.fd,buff,nSize);
				}else if (nSize <= 0)
				{
					//1、recv返回0有两种情况,一种是请求接收的字节只有0了(这里显示不是),一种是对端socket close或shutdown了,
					//2、小于0是错误,EAGAIN错误不处理,其他错误关闭连接
					if (errno != EAGAIN || nSize == 0)
					{
						cout << "DoRead:close fd:" << ev.fd << endl;
						//关闭
						m_epoll.Efd_del(ev.fd);

						close(ev.fd);

						m_pHandler->close_handler(ev.fd);

						return true;
					}else
					{
						break;
					}
				}
				//for test
				 
				//char buff2[26] = {"hello,client!"};

				//Send(ev.fd,buff2,sizeof(buff2));

				//非Et模式只执行一次
				if (!m_Et){break;}
			}
		}
	}
	return false;
}

bool CSocketServer::DoWrite(Event& ev)
{
	if(ev.write)
	{
		cout << "DoWrite" << endl;

		writebuffer* pWBuffer = m_pQueue.Front();

		if(pWBuffer == NULL) return false;

		m_pQueue.Pop();

		char* mData = pWBuffer->buff;
		uint32 mLen = pWBuffer->len;

		//无论et还是非et,把所有数据写出去
		for(;;)
		{
			//处理写事件
			uint32 nSize = send(ev.fd,mData,mLen,0);

			if(nSize > 0)
			{
				cout << "DoWrite:Send:" << mData << "," << mLen << endl;
				mData = mData + nSize;
				mLen = mLen - nSize;
			}else
			{
				SAFE_DEL_POINT(pWBuffer);

				m_epoll.Efd_write(ev.fd,NULL,false);

				break;
			}
		}
	}
	return false;
}

int CSocketServer::Run()
{
	cout << "CSocketServer Start" << endl;

	while(GetbActive())
	{
		struct Event ev[256];

		uint32 n = m_epoll.Efd_wait(ev,256);


		for(uint32 i = 0;i<n;++i)
		{
			cout << "ev:fd=" <<ev[0].fd << ",read=" << ev[0].read << ",write=" << ev[0].write << ",error=" << ev[0].error << endl;

			if( DoError(ev[i]) ){break;}

			if( DoRead(ev[i]) ){break;}

			if( DoWrite(ev[i]) ){break;}
		}
	}
	cout << "CSocketServer End" << endl;
	return 0;
}

void CSocketServer::Init(uint16 nIP,uint16 nPort,BaseHandler* pHandler,bool et)
{
	m_epoll.Efd_create(1024);

	m_pHandler = pHandler;

	m_Et = et;

	sockaddr_in _sockaddr_in;
    _sockaddr_in.sin_family = AF_INET;
    _sockaddr_in.sin_addr.s_addr = nIP;
    _sockaddr_in.sin_port = htons(nPort);

	m_listenfd = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);

	int32 nret = bind(m_listenfd,(struct sockaddr*)&_sockaddr_in,sizeof(_sockaddr_in));

	listen(m_listenfd,10);

	cout << "m_listenfd = " << m_listenfd << ",ip=" << nIP << endl;

	m_epoll.Efd_add(m_listenfd,NULL,m_Et);
}

//队列版本
uint32 CSocketServer::Send(uint32 fd,void* buff, uint32 nLen)
{
	//内存碎片问题,可能得用内存池
	writebuffer* pBuffer = new writebuffer(fd,buff,nLen);

	m_pQueue.Push(pBuffer);

	m_epoll.Efd_write(fd,NULL,true);

	return 0;
}