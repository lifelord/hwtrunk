#include "base_socket_server.h"

CSocketServer::CSocketServer()
{
}

CSocketServer::~CSocketServer()
{
}

void CSocketServer::DoRead(Event& ev)
{
	//处理读事件
	if(ev.read)
	{
		//1、接收新socket
		if (ev.fd == m_listenfd)
		{
			//accept a new socket
			uint32 newfd = accept(ev.fd,NULL,NULL);
			SocketData* pData = NewSocketData(newfd);
			if(pData)
			{
				m_epoll.Efd_add(newfd,&pData->ev,m_Et);
			}
			cout << "accept:" << newfd << endl;
			return;
		}else
		{
			for(;;)
			{
				static char buff[1024];
				int32 nSize = recv(ev.fd, buff, sizeof(buff), MSG_DONTWAIT);
				if( nSize > 0)
				{
					AutoLock safe(&m_Lock);

					SocketData* pData = GetSocketData(ev.fd);

					if(pData == NULL)
					{
						cout << "error GetSocketData fd=" << ev.fd << endl;
						return;
					}

					pData->rbuffer.write(buff,nSize);

					cout << "recv:" << buff << ",nSize=" << nSize <<endl;

				}else if (nSize <= 0)
				{
					//1、recv返回0有两种情况,一种是请求接收的字节只有0了(这里显示不是),一种是对端socket close或shutdown了,
					//2、小于0是错误,EAGAIN错误不处理,其他错误关闭连接
					if (errno != EAGAIN || nSize == 0)
					{
						DelSocketData(ev.fd);

						cout << "close:fd = " << ev.fd << endl;

						return;
					}else
					{
						break;
					}
				}
				//非Et模式只执行一次
				if (!m_Et)
				{
					break;
				}
			}
			//for test
			char buff2[512] = {"hello,client"};
			Write(ev.fd,buff2,sizeof(buff2));	
		}
	}
	return;
}

void CSocketServer::DoWrite(Event& ev)
{
	if(ev.write)
	{
		cout << "write" << endl;

		for(;;)
		{
			AutoLock safe(&m_Lock);

			SocketData* pData = GetSocketData(ev.fd);

			if(pData == NULL)
			{
				cout << "error fd=" << ev.fd << endl;
				return;
			}

			//处理写事件,send
			int32 size = send(ev.fd, &pData->wbuffer[0], pData->wbuffer.length(), MSG_DONTWAIT );//发送之

			if (size <= 0)
			{
				if(errno == EAGAIN)
				{
					//send操作由于缓冲区满阻塞,fd设置了非阻塞,直接返回,需重新send数据
					m_epoll.Efd_write(ev.fd,&pData->ev,true);
				}else
				{
					//其他操作把数据缓存清空,重置ev[i].fd为EPOLLIN
					pData->wbuffer.clear();
					m_epoll.Efd_write(ev.fd,&pData->ev,false);
				}
				return;
			}else
			{
				//发送了size字节数据
				pData->wbuffer.position(size);
				pData->wbuffer.erase();
			}
			//非Et模式只执行一次
			if(!m_Et)
			{
				break;
			}
		}
	}
}

int CSocketServer::Run()
{
	cout << "RunStart-CSocketServer" << endl;

	while(GetbActive())
	{
		struct Event ev[256];

		uint32 n = m_epoll.Efd_wait(ev,256);

		cout << "event num="<< n << endl;

		for(uint32 i = 0;i<n;++i)
		{
			cout << ev[i].fd << ":" << ev[i].error << ":" << ev[i].read << ":" << ev[i].write << endl;
			if(ev[i].error)
			{
				cout << "error,fd =" << ev[i].fd << endl;
				//处理错误,关闭描述符
				DelSocketData(ev[i].fd);
				continue;
			}

			DoRead(ev[i]);

			DoWrite(ev[i]);
		}
	}
	cout << "RunEnd-CSocketServer" << endl;
	return 0;
}

void CSocketServer::Init(uint16 nIP,uint16 nPort,bool et)
{
	m_epoll.Efd_create(1024);

	m_Et = et;

	sockaddr_in _sockaddr_in;
    _sockaddr_in.sin_family = AF_INET;
    _sockaddr_in.sin_addr.s_addr = nIP;
    _sockaddr_in.sin_port = htons(nPort);

	m_listenfd = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);

	int32 nret = bind(m_listenfd,(struct sockaddr*)&_sockaddr_in,sizeof(_sockaddr_in));

	listen(m_listenfd,10);

	cout << "m_listenfd = " << m_listenfd << ",ip=" << nIP << endl;

	SocketData* pData = NewSocketData(m_listenfd);

	if(pData)
	{
		m_epoll.Efd_add(m_listenfd,&pData->ev,m_Et);
	}
}

void CSocketServer::Write(uint32 fd,void* buffer,uint32 nlen)
{
	AutoLock safe(&m_Lock);

	SocketData* pData = GetSocketData(fd);
	if(pData != NULL)
	{
		pData->wbuffer.write(buffer,nlen);
		m_epoll.Efd_write(fd,&pData->ev,true);
	}
}

SocketData* CSocketServer::NewSocketData(uint32 fd)
{
	AutoLock safe(&m_Lock);

	if ( fd == -1 || fd < 0 )
	{
		return NULL;
	}
	MAPSOCKETDATA::iterator itr = m_SocketData.find(fd);

	if (itr != m_SocketData.end())
	{
		return itr->second;
	}

	SocketData* pData = new SocketData;
	pData->fd = fd;
	pData->ev.fd = fd;
	m_SocketData.insert(make_pair(fd,pData));

	return pData;
}

SocketData* CSocketServer::GetSocketData(uint32 fd)
{
	MAPSOCKETDATA::iterator itr = m_SocketData.find(fd);
	if( itr != m_SocketData.end())
	{
		return itr->second;
	}
	return NULL;
}

void CSocketServer::DelSocketData(uint32 fd)
{
	AutoLock safe(&m_Lock);

	MAPSOCKETDATA::iterator itr = m_SocketData.find(fd);
	if(itr != m_SocketData.end())
	{
		m_epoll.Efd_del(fd);
		close(fd);
		delete itr->second;
		itr->second = NULL;
		m_SocketData.erase(fd);
	}
}