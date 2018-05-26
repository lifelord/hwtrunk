#ifndef BASE_CLIENT_POOL_H
#define BASE_CLIENT_POOL_H

#include "base_util.h"
#include "base_net_define.h"
#include "base_stream.h"
#include "base_sandbox.h"

class BaseUser
{
public:
	BaseUser();
	virtual ~BaseUser();
	virtual bool OnRecv(char* pData,uint32 sz);
	virtual void OnClose(){};
	virtual void OnReset();
	bool push_data(CStream& data);
	bool ReadData();
public:
	int32& GetSockfd() { return m_Sockfd; }
	uint32& GetRoleId() { return m_RoleId; }
	uint32& GetHost() { return m_Host; }
	uint32& GetIndex() { return m_Index; }
	uint32& GetServerType(){ return m_servertype;}
	void    SetSandBox(CSandBox* pSendBox){m_pSandBox = pSendBox;}
private:
	char* m_buff;
	char* m_data;
	uint32 m_size;
private:
	int32 m_Sockfd;
	uint32 m_RoleId;
	uint32 m_Host;
	uint32 m_Index;
	uint32 m_servertype;	//根据服务器定解包类型
	CSandBox* m_pSandBox;
};

#endif