#include "base_client_pool.h"

BaseUser::BaseUser()
{
	//将数据放置到m_buff中,供解包用
	m_buff = new char[UNPACK_BUFF_SIZE];
	m_data = &m_buff[0] ;
	m_size = 0;
}

BaseUser::~BaseUser()
{
	
}

void BaseUser::OnReset()
{
	m_size = 0;
}

//暂时这样写的,接客户端的包
bool BaseUser::OnRecv(char* pData,uint32 sz)
{
	MsgHead* pHead = (MsgHead*)pData;

	cout << "BaseUser::OnRecv:Packet=(pHead = " << pHead->pack_start << ",pack_type = " << pHead->pack_type 
		<< ",pack_len = " << pHead->pack_len << ",pack_cmd = " << pHead->pack_cmd <<")"<< endl;
	
    return true;
}

bool BaseUser::push_data(CStream& data)
{
	if (data.length() == 0)
	{
		m_size = 0;
		cout << "BaseUser::push_data:error m_size=" << m_size << endl;
		return false;
	}

	cout << "BaseUser:push_data,step1 start" << endl;

	uint32 nLen = data.position();

	if ((m_size + nLen) > UNPACK_BUFF_SIZE)
	{
		uint32 pos = UNPACK_BUFF_SIZE - m_size;

		memmove(m_data, &data[0], pos);
		m_size += pos;
		data.position(pos);
	}
	else
	{
		memmove(m_data, &data[0], nLen);
		m_size += nLen;
	}

	data.erase();

	return true;
}

bool BaseUser::ReadData()
{
	if (m_size == 0)
	{
		cout << "BaseUser::ReadData,error m_size=" << m_size << endl;
		return false;
	}

	cout << "BaseUser:ReadData,step2 unpack start" << endl;

	char* pBuffer = m_data;
	uint32 nLastLen = m_size;

	for (;;)
	{
		if (nLastLen < sizeof(MsgHead))
		{
			//cout << "BaseUser:ReadData,nLastLen=" << nLastLen << ",sizeof(MsgHead)=" << sizeof(MsgHead) << endl;
			break;
		}
		MsgHead* pHead = (MsgHead*)pBuffer;

		//包长不够
		if (nLastLen < pHead->pack_len)
		{
			//cout << "BaseUser:ReadData,nLastLen=" << nLastLen << ",pHead->pack_len=" << pHead->pack_len;
			break;
		}

		if (pHead->pack_start != PACKET_START)
		{
			//cout << "BaseUser:ReadData,pHead->pack_start=" << pHead->pack_start << ",PACKET_START=" << PACKET_START << endl;
			//包头开始符出错应该直接返回false
			//break;
			return false;
		}

		uint32 pack_len = pHead->pack_len;

		if (!OnRecv(pBuffer, pack_len))
		{
			//解包出错一定返回false
			return false;
		}
		nLastLen -= pack_len;
		pBuffer += pack_len;
	}

	if (nLastLen != m_size)
	{
		memmove(m_data, pBuffer, nLastLen);
		m_size = nLastLen;
		cout << "BaseUser:ReadData,step3 unpack end,m_size =" << m_size << endl;
	}
	return true;
}