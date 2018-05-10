#include "base_client_pool.h"

BaseUser::BaseUser()
{
	m_buff = new char[PCK_OFFSET + GATE_BUFF_SIZE];
	m_data = &m_buff[0] + PCK_OFFSET;
	m_size = 0;
}

BaseUser::~BaseUser()
{
	
}

bool BaseUser::push_data(CStream& data)
{
	if (data.length() == 0)
	{
		m_size = 0;
		return false;
	}
	uint32 nLen = data.position();

	if ((m_size + nLen) > GATE_BUFF_SIZE)
	{
		uint32 pos = GATE_BUFF_SIZE - m_size;

		memmove(m_data, &data[0], pos);
		m_size += pos;
		data.position(pos);
	}
	else
	{
		memmove(m_data, &data[0], nLen);
	}
	data.erase();

	return true;
}

bool BaseUser::read()
{
	if (m_size == 0)
	{
		return false;
	}
	char* pBuffer = m_data;
	uint32 nLastLen = m_size;

	for (;;)
	{
		if (nLastLen < sizeof(Clt_Head))
		{
			break;
		}
		Clt_Head* pCltHead = (Clt_Head*)pBuffer;

		if (pCltHead->pack_start != PACKET_START)
		{
			break;
		}
		if (nLastLen < pCltHead->pack_len)
		{
			break;
		}
		uint32 pack_len = pCltHead->pack_len;

		if (!OnRevice(pBuffer, pack_len))
		{
			return false;
		}
		nLastLen -= pack_len;
		pBuffer += pack_len;
	}

	if (nLastLen != m_size)
	{
		memmove(m_data, pBuffer, nLastLen);
		m_size = nLastLen;
	}
	return true;
}
