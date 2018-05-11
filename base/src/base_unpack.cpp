#include "base_unpack.h"

UnPackHandler::UnPackHandler()
{
	//m_sem.CreateSema();
}

UnPackHandler::~UnPackHandler()
{

}

int UnPackHandler::Run()
{
	cout << "UnPackHandler Start" << endl;
	while(GetbActive())
	{
		/*if (m_sem.WaitSema(100) != 1)
        {
        	cout << "time out" << endl;
            continue;
        }*/

        vector<BaseUser*> vUserVec;
		{
			AutoLock safe(&m_lock);

			if(m_MsgCount.empty())
        	{
        		//cout << "m_MsgCount.empty()" << endl;
        		continue;
        	}

			for(map<uint32,uint32>::iterator itr = m_MsgCount.begin(); itr != m_MsgCount.end();++itr)
			{
				map<uint32,UnPack*>::iterator itor = m_Pool.find(itr->first);

				BaseUser* pUser = itor->second->pUser;

				pUser->push_data(itor->second->stream);

				vUserVec.push_back(pUser);
			}

			m_MsgCount.clear();
		}

 		//解包数据时不需要锁
		for (uint32 i = 0; i < vUserVec.size(); ++i)
        {
            BaseUser* pUser = vUserVec[i];

            if (pUser->ReadData()) 
                continue;

            pUser->OnClose();
        }
	}
	cout << "UnPackHandler End" << endl;
	return 0;
}

void UnPackHandler::accept_handler(uint32 fd,uint32 nhost)
{
	{
		AutoLock safe(&m_lock);

		UnPack* pUnPack = new UnPack;

		pUnPack->pUser = new BaseUser;

		pUnPack->pUser->GetSockfd() = fd;

		pUnPack->pUser->GetHost() = nhost;

		m_Pool.insert(make_pair(fd,pUnPack));
	}
}

void UnPackHandler::recv_handler(uint32 fd,void* buff,uint32 nlen)
{
	{
		AutoLock safe(&m_lock);

		map<uint32,UnPack*>::iterator itr = m_Pool.find(fd);

		if(itr != m_Pool.end())
		{
			CStream& stream = itr->second->stream;

			stream.position(stream.length());

			stream.write(buff,nlen);

			m_MsgCount[fd]++;

			cout << "recv_handler:" << fd << "," << m_MsgCount[fd] << endl;
		}else
		{
			cout << "fd=" << fd << ",UnPack not exist" << endl; 
		}	
	}
	//m_sem.ReleaseSema();
}

void UnPackHandler::close_handler(uint32 fd)
{
	{
		AutoLock safe(&m_lock);

		map<uint32,UnPack*>::iterator itr = m_Pool.find(fd);

		if(itr != m_Pool.end())
		{
			UnPack* pUnPack = itr->second;

			m_Pool.erase(fd);

			SAFE_DEL_POINT(pUnPack->pUser);

			SAFE_DEL_POINT(pUnPack);
		}
	}
}

void UnPackHandler::write_handler(uint32 fd)
{
}