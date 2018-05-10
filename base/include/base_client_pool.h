#ifndef BASE_CLIENT_POOL_H
#define BASE_CLIENT_POOL_H

#include "base_util.h"
#include "base_net_define.h"
#include "base_stream.h"

class BaseUser
{
public:
	BaseUser();
	virtual ~BaseUser();
	virtual bool OnRevice(char* pData,uint32 sz) = 0;
	virtual void OnClose() = 0;
	virtual void OnReset() = 0;
	bool push_data(CStream& data);
	bool read();
public:
	uint32& GetSockfd() { return m_Sockfd; }
	uint32& GetRoleId() { return m_RoleId; }
	uint32& GetHost() { return m_Host; }
	uint32& GetIndex() { return m_Index; }
private:
	char* m_buff;
	char* m_data;
	uint32 m_size;
private:
	uint32 m_Sockfd;
	uint32 m_RoleId;
	uint32 m_Host;
	uint32 m_Index;
};

#endif