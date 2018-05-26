#ifndef _BASE_NET_DEFINE_H
#define _BASE_NET_DEFINE_H

#include "base_util.h"

#define MIDDLE_BUFF_SIZE 10240
#define MAX_BUFF_SIZE 102400
#define PACKET_START 0x0AAAAAAA
#define MIN_BUFF_SIZE	0x0800			//= 2K
#define CLT_BUFF_SIZE	0x02000			//= 8K
#define USR_BUFF_SIZE	0x04000			//= 16k
#define PCK_BUFF_SIZE	0x08000			//= 32k
#define APP_BUFF_SIZE	0x020000		//= 128K
#define APP2_BUFF_SIZE	0x040000		//= 256K
#define DAT_BUFF_SIZE	0x080000		//= 512K
#define SVR_BUFF_SIZE	0x0100000		//= 1M
#define SYS_BUFF_SIZE	0x010000		//= 64k

#define GATE_BUFF_SIZE 0x08000//32K

#define UNPACK_BUFF_SIZE 0x08000//32K,解包缓存大小

#define QSOCK_LISTEN 1
#define QSOCK_ACCEPT 2
#define QSOCK_CONNECT 3

#define QSERVER_TYPE_DEFAULT 0
#define QSERVER_TYPE_NORMAL	1
#define QSERVER_TYPE_WEB 2

#pragma pack(1)
struct Clt_Head
{
	uint32 pack_start;	//开始符，验证用的
	uint32 pack_len;	//包大小+cltnum*4
	uint32 pack_cmd;	//协议号
	uint32 pack_seqno;	//包编号
	uint32 sessionid;	//验证客户端合法性
};

struct  Svr_Head:public Clt_Head
{
	uint32 roleid;
	uint32 cltnum;
};

#define PCK_OFFSET (sizeof(Svr_Head) - sizeof(Clt_Head))

inline Clt_Head* SrvHeadToCltHead(char* pPack)
{
	Clt_Head* pCltHead = (Clt_Head*)(pPack+PCK_OFFSET);

	Clt_Head cmd = *(Clt_Head*)pPack;
	cmd.pack_len -= PCK_OFFSET;

	memmove(pCltHead, &cmd, sizeof(Clt_Head));
	return pCltHead;
};

inline Svr_Head* CltHeadToSrvHead(char* pPack)
{
	Svr_Head* pSvrHead = (Svr_Head*)(pPack - PCK_OFFSET);
	Clt_Head cmd = *(Clt_Head*)pPack;
	memmove(pSvrHead, &cmd, sizeof(Clt_Head));
	return pSvrHead;
};

//新消息包结构
struct MsgHead
{
	uint32 pack_start;	//开始符,验证用的
	uint32 pack_type;	//消息类型
	uint32 pack_len;	//消息长度
	uint32 pack_cmd;	//消息指令

	MsgHead()
	{
		memset(this,0,sizeof(MsgHead));
	}
};

#pragma pack()

#endif