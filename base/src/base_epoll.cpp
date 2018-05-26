#include "base_epoll.h"

CEpoll::CEpoll()
{
}

CEpoll::~CEpoll()
{
}

//是否有效句柄
bool CEpoll::Efd_invalid(int32 efd)
{
	return (efd == -1);
}

//创建epoll句柄
uint32 CEpoll::Efd_create(int32 nsize)
{
	m_efd = epoll_create(nsize);
	if (m_efd == -1)
	{
		return -1;
	}
	return m_efd;
}

//添加fd句柄到m_efd,默认可读时触发事件
bool CEpoll::Efd_add(int32 fd,void* ud,bool et)
{
	bool binvalid = Efd_invalid(m_efd);
	if (binvalid)
	{
		cout << "Efd_add binvalid = true" << endl;
		return false;
	} 

	struct epoll_event ev;

	ev.events = EPOLLIN;

	//if(ud == NULL)
	//{
		ev.data.fd = fd;
	//}else
	//{
		//ev.data.ptr = ud;
	//}
	
	if (et)
	{
		Efd_nonblocking(fd);
		ev.events |= (EPOLLOUT|EPOLLET);
	}

	if (epoll_ctl(m_efd, EPOLL_CTL_ADD, fd, &ev) == -1) 
	{
		cout << "Efd_add:epoll_ctl failed" << endl;
		return false;
	}
	
	return true;
}

//删除fd
bool CEpoll::Efd_del(int32 fd)
{
	bool binvalid = Efd_invalid(m_efd);

	if (binvalid)
	{
		cout << "Efd_del binvalid = true" << endl;
		return false;
	} 
	if(epoll_ctl(m_efd, EPOLL_CTL_DEL, fd, NULL) == -1)
	{
		cout << "Efd_del epoll_ctl failed" << endl;
		return false;
	}
	return true;
}

//fd可读可写
bool CEpoll::Efd_write(int32 fd,void* ud,bool enable)
{
	bool binvalid = Efd_invalid(m_efd);
	if (binvalid)
	{
		cout << "Efd_write binvalid = true" << endl;
		return false;
	} 
	struct epoll_event ev;

	ev.events = EPOLLIN | (enable ? EPOLLOUT : 0);

	//if(ud == NULL)
	//{
		ev.data.fd = fd;
	//}else
	//{
		//ev.data.ptr = ud;
	//}
	
	if(epoll_ctl(m_efd, EPOLL_CTL_MOD, fd, &ev) == -1)
	{
		cout << "Efd_write epoll_ctl failed" << endl;
		return false;
	}
	return true;
}

//epoll wait
uint32 CEpoll::Efd_wait(struct Event* e,uint32 max)
{
	//监听事件集
	struct epoll_event ev[max];

	uint32 n = epoll_wait(m_efd,ev,max,-1);

	for(uint32 i=0;i<n;++i)
	{
		//if(ev[i].data.ptr != NULL)
		//{
			//e[i].ud = ev[i].data.ptr;
		//}else
		//{
			e[i].fd = ev[i].data.fd;
			cout << "Efd_wait,fd=" << ev[i].data.fd << endl;
		//}
		
		unsigned flag = ev[i].events;//event

		e[i].read = (flag & EPOLLIN) != 0;
		e[i].write = (flag & EPOLLOUT) != 0;
		e[i].error = (flag & EPOLLERR) != 0;
	}
	return n;
}

void CEpoll::Efd_nonblocking(int fd) 
{
	int flag = fcntl(fd, F_GETFL, 0);
	if ( -1 == flag ) {
		return;
	}

	fcntl(fd, F_SETFL, flag | O_NONBLOCK);
}