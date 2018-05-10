#include "base_socket_server.h"

CSocketServer::CSocketServer()
{
}

CSocketServer::~CSocketServer()
{
}

void CSocketServer::DoError(Event& ev)
{
	if(ev.error)
	{
		m_epoll.Efd_del(ev.fd);
		close(ev.fd);
	}
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

			Event newEvt;

			newEvt.fd = newfd;

			m_epoll.Efd_add(newfd,&newfd,m_Et);

			cout << "accept:" << newfd << endl;

			//新连接
			m_pHandler->accept_handler(newfd);

			return;
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

					cout << "recv:" << buff << ",nSize=" << nSize <<endl;

				}else if (nSize <= 0)
				{
					//1、recv返回0有两种情况,一种是请求接收的字节只有0了(这里显示不是),一种是对端socket close或shutdown了,
					//2、小于0是错误,EAGAIN错误不处理,其他错误关闭连接
					if (errno != EAGAIN || nSize == 0)
					{
						//关闭
						m_pHandler->close_handler(ev.fd);

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
		}
	}
}

void CSocketServer::DoWrite(Event& ev)
{
	if(ev.write)
	{
		cout << "write" << endl;

		for(;;)
		{
			//处理写事件
			m_pHandler->write_handler(ev.fd);

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

			DoError(ev[i]);

			DoRead(ev[i]);

			DoWrite(ev[i]);
		}
	}
	cout << "RunEnd-CSocketServer" << endl;
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