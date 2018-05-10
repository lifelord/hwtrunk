#include "base_unpack.h"

UnPackHandler::UnPackHandler()
{

}

UnPackHandler::~UnPackHandler()
{

}

int UnPackHandler::Run()
{
	while(GetbActive())
	{
		{
			AutoLock safe(&m_lock);

			for(vector<BaseUser*>::iterator itr = m_User.begin(); itr != m_User.end();++itr)
			{
				(*itr)->read();
			}
		}
	}
	return 0;
}

void UnPackHandler::accept_handler(uint32 fd)
{
	{
		AutoLock safe(&m_lock);

		BaseUser* pUser = new BaseUser;

		m_Pool.insert(make_pair(fd,pUser));
	}
}

void UnPackHandler::recv_handler(uint32 fd,void* buff,uint32 nlen)
{
	{
		AutoLock safe(&m_lock);

		map<uint32,BaseUser*>::iterator itr = m_Pool.find(fd);

		if(itr != m_Pool.end())
		{
			(itr->second)->push_data(buff,nlen);

			m_User.push_back(itr->second);
		}	
	}
}

void UnPackHandler::close_handler(uint32 fd)
{
	{
		AutoLock safe(&m_lock);

		map<uint32,BaseUser*>::iterator itr = m_Pool.find(fd);

		if(itr != m_Pool.end())
		{
			BaseUser* pUser = itr->second;

			m_Pool.erase(fd);

			delete pUser;

			pUser = NULL;
		}
	}
}

void UnPackHandler::write_handler(uint32 fd)
{
	//这里还有点问题
	//int32 size = send(fd, &pData->wbuffer[0], pData->wbuffer.length(), MSG_DONTWAIT );//发送之
}