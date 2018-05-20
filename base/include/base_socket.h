#ifndef BASE_SOCKET_H
#define BASE_SOCKET_H

#include "base_util.h"

class SocketApi
{
public:
	static bool IsValid(SOCKET fd);

	static SOCKET Socket_ex(int32 domain, int type, int protocol);

	static bool Bind_ex(SOCKET& s, uint32 nIP, uint16 nPort);

	static bool Bind_ex(SOCKET& s, struct sockaddr* addr, uint16 len);

	static bool Connect_ex(SOCKET& s,uint32 nIP, uint16 nPort);

	static bool Listen_ex(SOCKET& s, uint32 nConnMax = SOMAXCONN);

	static bool SetNonBlocking(SOCKET& s, bool bNoBlock = true);

	static bool SetReuseAddr(SOCKET& s, bool on = true);

	static bool SetSendBufferSize(SOCKET& s, int size);

	static bool SetRecvBufferSize(SOCKET& s, int size);

	static void Reset(SOCKET& s);

	static void Close(SOCKET& s);

	static int Recv_ex(SOCKET s, char* buf, int len);

	static int Send_ex(SOCKET s, char* str, int len);

	static int GetHostByName(const char* host);
};

#endif