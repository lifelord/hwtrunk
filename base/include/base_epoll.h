#ifndef BASE_EPOLL_H_
#define BASE_EPOLL_H_

#include"base_util.h"

#define MAX_EVENTS 1024

struct Event
{
	int32 fd;
	//void* ud;
	bool read;
	bool write;
	bool error;
};

class CEpoll
{
public:
	CEpoll();
	~CEpoll();
public:
	//是否有效句柄
	bool Efd_invalid(int32 efd);
	//创建epoll句柄
	uint32 Efd_create(int32 nsize);
	//添加fd句柄到m_efd,fd为待监视的句柄,ud为用户数据
	bool Efd_add(int32 fd,void* ud,bool et=false);
	//删除fd
	bool Efd_del(int32 fd);
	//epoll写事件,fd为待监视的句柄,ud为用户数据
	bool Efd_write(int32 fd, void* ud, bool enable);
	//epoll wait
	uint32 Efd_wait(struct Event* e,uint32 max);
	//set fd nonblocking
	void Efd_nonblocking(int fd); 
private:
	//监听句柄
	uint32 m_efd;
};

class BaseHandler
{
public:
	BaseHandler(){}
	virtual ~BaseHandler(){}
public:
	virtual void accept_handler(uint32 fd,uint32 nhost) = 0;
	virtual void recv_handler(uint32 fd,void* buff,uint32 nlen) = 0;
	virtual void close_handler(uint32 fd) = 0;
	virtual void write_handler(uint32 fd) = 0;
};

#endif