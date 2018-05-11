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
		uint32 fd = *(uint32*)ev.ud;
		cout << "DoError" << endl;
		m_epoll.Efd_del(fd);
		close(fd);
		return true;
	}
	return false;
}

bool CSocketServer::DoRead(Event& ev)
{
	//处理读事件
	if(ev.read)
	{
		uint32 fd = *(uint32*)ev.ud;
		//1、接收新socket
		if (fd == m_listenfd)
		{
			//accept a new socket
			uint32 newfd = accept(fd,NULL,NULL);

			m_epoll.Efd_add(newfd,&newfd,m_Et);

			cout << "accept:" << newfd << endl;

			//新连接
			m_pHandler->accept_handler(newfd,0);

			cout << "DoRead:accept" << endl;

			if(m_writebuffer.find(newfd) != m_writebuffer.end())
			{
				writebuffer* pBuffer = new writebuffer;

				pBuffer->fd = newfd;

				m_writebuffer.insert(make_pair(newfd,pBuffer));
			}

			return true;
		}else
		{
			for(;;)
			{
				static char buff[1024];

				int32 nSize = recv(fd, buff, sizeof(buff), MSG_DONTWAIT);

				if( nSize > 0)
				{
					//接收数据
					m_pHandler->recv_handler(fd,buff,nSize);
				}else if (nSize <= 0)
				{
					//1、recv返回0有两种情况,一种是请求接收的字节只有0了(这里显示不是),一种是对端socket close或shutdown了,
					//2、小于0是错误,EAGAIN错误不处理,其他错误关闭连接
					if (errno != EAGAIN || nSize == 0)
					{
						cout << "DoRead:close" << endl;
						//关闭
						m_epoll.Efd_del(fd);

						close(fd);

						m_pHandler->close_handler(fd);

						return true;
					}else
					{
						break;
					}
				}
				//非Et模式只执行一次
				if (!m_Et){break;}
			}	
		}
	}
	return true;
}

bool CSocketServer::DoWrite(Event& ev)
{
	if(ev.write)
	{
		cout << "DoWrite" << endl;

		for(;;)
		{
			uint32 fd = *(uint32*)ev.ud;

			//处理写事件
			map<uint32, writebuffer*>::iterator itr = m_writebuffer.find(fd);

			if(itr != m_writebuffer.end())
			{
				CStream& sBuff = itr->second->buff;

				uint32 nSize = send(fd,&sBuff[0],sBuff.length(),0);

				if(nSize > 0)
				{
					sBuff.position(nSize);
					sBuff.erase();
				}else
				{
					sBuff.clear();
					break;
				}
			}

			//非Et模式只执行一次
			if(!m_Et){break;}
		}
	}
	return true;
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

	m_epoll.Efd_add(m_listenfd,&m_listenfd,m_Et);
}

//有无方法实现不加锁的发送?????思考队列方式
uint32 CSocketServer::Send(uint32 fd,void* buff, uint32 nLen)
{
	//把消息丢到队列里面，主动触发epoll_out去处理发送数据
	map<uint32, writebuffer*>::iterator itr = m_writebuffer.find(fd);

	uint32 nSize = 0;

	if(itr != m_writebuffer.end())
	{
		CStream& sbuff = itr->second->buff;

		sbuff.write(buff,nLen);

		nSize = send(fd, buff, nLen, 0);
	
		if(nSize > 0)
		{
			uint32 nDiff = nSize - nLen;

			//not all send
			if(nDiff>0)
			{
				sbuff.position(nLen);

				sbuff.erase();

				m_epoll.Efd_write(fd, &fd, true);
			}
		}else if (errno == EAGAIN)
		{
			m_epoll.Efd_write(fd, &fd, true);

			return 0;
		}
	}
	return nSize;
}