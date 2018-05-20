#include "base_socket.h"

bool SocketApi::IsValid(int32 fd)
{
	return fd != SOCKET_ERROR;
}

int32 SocketApi::Socket_ex(int domain, int type, int protocol)
{
	return socket(domain, type, protocol);
}

bool SocketApi::Bind_ex(SOCKET& s, uint32 nIP, uint16 nPort)
{
	sockaddr_in _sockaddr_in;
	_sockaddr_in.sin_family = AF_INET;
	_sockaddr_in.sin_addr.s_addr = nIP;
	_sockaddr_in.sin_port = htons(nPort);

	return (bind(s,(struct sockaddr*)&_sockaddr_in,sizeof(_sockaddr_in)) != SOCKET_ERROR );
}

bool SocketApi::Bind_ex(SOCKET& s, struct sockaddr* addr, uint16 len)
{
	return (bind(s,addr,len) != SOCKET_ERROR);
}

bool SocketApi::Connect_ex(SOCKET& s,uint32 nIP, uint16 nPort)
{
	sockaddr_in _sockaddr_in;
	_sockaddr_in.sin_family = AF_INET;
	_sockaddr_in.sin_addr.s_addr = nIP;
	_sockaddr_in.sin_port = htons(nPort);

	return (connect(s,(struct sockaddr*)&_sockaddr_in,sizeof(_sockaddr_in)) != SOCKET_ERROR);
}

bool SocketApi::Listen_ex(SOCKET& s, uint32 nConnMax)
{
	return listen(s, nConnMax) != SOCKET_ERROR;
}

bool SocketApi::SetNonBlocking(SOCKET& s, bool bNoBlock)
{
	int flags = fcntl(s,F_GETFL,0);

	if(flags < 0) return false;

	if(bNoBlock)
	{
		flags |= O_NONBLOCK;
	}else
	{
		flags &= ~O_NONBLOCK;
	}

	return fcntl(s, F_SETFL, flags) != -1;
}

bool SocketApi::SetReuseAddr(SOCKET& s, bool on)
{
	int opt = on ? 1 : 0;
	return (setsockopt(s,SOL_SOCKET,SO_REUSEADDR,(char*)&opt,sizeof(opt)) != SOCKET_ERROR);
}

bool SocketApi::SetSendBufferSize(SOCKET& s, int size)
{
	return (setsockopt(s,SOL_SOCKET,SO_SNDBUF,(char*)&size,sizeof(size)) != SOCKET_ERROR);
}

bool SocketApi::SetRecvBufferSize(SOCKET& s, int size)
{
	return (setsockopt(s, SOL_SOCKET, SO_RCVBUF, (char*)&size, sizeof(size)) != SOCKET_ERROR);
}

void SocketApi::Reset(SOCKET& s)
{
	s = INVALID_SOCKET;
}

void SocketApi::Close(SOCKET& s)
{
	if(IsValid(s))
	{
		Close(s);
		Reset(s);
	}
}

int SocketApi::Recv_ex(SOCKET s, char* buf, int len)
{
	errno = 0;
	int ret = ::recv(s, buf, len, 0);
	if(ret < 0)
	{
		 int error = errno;
		 if(error == 0 || error == EAGAIN) return 0;
		 return (~0);
	}

	return ret;
}

int SocketApi::Send_ex(SOCKET s, char* str, int len)
{
	int ret = 0;
	while(ret < len)
	{
		errno = 0;
		int real = send(s,str+ret,len-ret,MSG_NOSIGNAL);
		if( real <= 0)
		{
			int nError = errno;
			if(nError == 0) continue;
			if( nError == EAGAIN) //写缓冲队列已满
			{
				SleepTime(1);
				continue;
			}
			return (~0);
		}
		ret += real;
	}
	return ret;
}

int SocketApi::GetHostByName(const char* host)
{
	int nHost = 0x00;
    struct addrinfo *result = NULL;
    struct addrinfo hints;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = PF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    int nret = getaddrinfo(host, NULL, &hints, &result);
    if (nret != 0)
        return nHost;

    if (result != NULL)
    {
        nHost = ((struct sockaddr_in*)result->ai_addr)->sin_addr.s_addr;
    }

    freeaddrinfo(result);
    return nHost;
}