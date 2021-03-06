#include"base_socket_server.h"


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
		CloseSocket(ev.fd);

		return true;
	}
	return false;
}

bool CSocketServer::DoRead(Event& ev)
{
	if(ev.read)
	{
		map<uint32,QSocket*>::iterator itor = m_Pool.find(ev.fd);
		if(itor != m_Pool.end())
		{
			QSocket* pSocket = itor->second;
			if( NULL != pSocket )
			{
				switch(pSocket->type)
				{
					case QSOCK_LISTEN:
					{
						uint32 newfd = accept(ev.fd,NULL,NULL);

						RegAcceptSocket(newfd);

						m_pHandler->accept_handler(newfd,0,pSocket->servertype);
					}break;
					case QSOCK_ACCEPT:
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
									CloseSocket(ev.fd);
									
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
					}break;
					default:
						break;
				} 
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

void CSocketServer::RegListenSocket(uint16 nIP,uint16 nPort,uint8 servertype)
{
	int32 listenfd = SocketApi::Socket_ex(AF_INET,SOCK_STREAM,IPPROTO_TCP);

	int32 nret = SocketApi::Bind_ex(listenfd,nIP,nPort);

	SocketApi::Listen_ex(listenfd);

	cout << "listenfd = " << listenfd << ",ip=" << nIP << ",port=" << nPort << endl;

	//暂时不做重复检测,以后用对象池替换
	QSocket* pSocket = new QSocket;
	pSocket->fd = listenfd;
	pSocket->type = QSOCK_LISTEN;
	pSocket->servertype = servertype;

	m_Pool.insert(make_pair(listenfd,pSocket));

	m_epoll.Efd_add(listenfd,NULL,m_Et);
}

void CSocketServer::RegAcceptSocket(int32 fd)
{
	QSocket* pSocket = new QSocket;
	pSocket->fd = fd;
	pSocket->type = QSOCK_ACCEPT;
	pSocket->servertype = QSERVER_TYPE_DEFAULT;

	cout << "acceptfd =" << fd << endl;

	m_Pool.insert(make_pair(fd,pSocket));

	m_epoll.Efd_add(fd,NULL,m_Et);
}

void CSocketServer::RegConnectSocket(uint16 nIP,uint16 nPort,uint8 servertype)
{
	int32 fd = SocketApi::Socket_ex(AF_INET,SOCK_STREAM,IPPROTO_TCP);

	if(SocketApi::IsValid(fd))
	{
		bool bret = SocketApi::Connect_ex(fd,nIP,nPort);

		if (bret)
		{
			QSocket* pSocket = new QSocket;
			pSocket->fd = fd;
			pSocket->type = QSOCK_CONNECT;
			pSocket->servertype = servertype;

			cout << "Connectfd =" << fd << endl;

			m_Pool.insert(make_pair(fd,pSocket));

			m_epoll.Efd_add(fd,NULL,m_Et);
		}
	}
}

void CSocketServer::CloseSocket(int32 fd)
{
	cout << "CloseSocket fd:" << fd << endl;

	map<uint32,QSocket*>::iterator itor = m_Pool.find(fd);

	if(itor != m_Pool.end())
	{
		QSocket* pSocket = itor->second;
		m_Pool.erase(pSocket->fd);
		SAFE_DEL_POINT(pSocket);
	}

	//关闭
	m_epoll.Efd_del(fd);

	close(fd);

	m_pHandler->close_handler(fd);
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
			cout << "ev:fd=" <<ev[i].fd << ",read=" << ev[i].read << ",write=" << ev[i].write << ",error=" << ev[i].error << endl;

			if( DoError(ev[i]) ){continue;}

			if( DoRead(ev[i]) ){continue;}

			if( DoWrite(ev[i]) ){continue;}
		}
	}

	cout << "CSocketServer End" << endl;

	return 0;
}

void CSocketServer::Init(BaseHandler* pHandler,bool et)
{
	m_epoll.Efd_create(1024);

	m_pHandler = pHandler;

	m_Et = et;
}

//队列版本
uint32 CSocketServer::Send(int32 fd,void* buff, uint32 nLen)
{
	//内存碎片问题,可能得用内存池
	writebuffer* pBuffer = new writebuffer(fd,buff,nLen);

	m_pQueue.Push(pBuffer);

	m_epoll.Efd_write(fd,NULL,true);

	return 0;
}