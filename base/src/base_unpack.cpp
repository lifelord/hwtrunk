#include "base_unpack.h"

UnPackHandler::UnPackHandler()
{
	//m_sem.CreateSema();
}

UnPackHandler::~UnPackHandler()
{

}

void UnPackHandler::Init(const char* path)
{
	m_SandBox.Init();
	m_SandBox.Load(path);
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
            //解包出错,应该关闭socket,这里需要思考如何优雅的移除解包类,释放玩家对象,结束socket,将socket从epoll中移除
            //关闭该socket的引用会触发epoll_out事件
            cout << "pUser->ReadData() = false,socketid =" << pUser->GetSockfd() << endl;

            //暂时这样处理吧
           	pUser->OnReset();

            //直接关掉导致不触发epoll事件
            close(pUser->GetSockfd());

            close_handler(pUser->GetSockfd());
        }
	}
	cout << "UnPackHandler End" << endl;
	return 0;
}

//根据servertype给与不同的解包策略
void UnPackHandler::accept_handler(int32 fd,uint32 nhost,uint8 servertype)
{
	{
		AutoLock safe(&m_lock);

		UnPack* pUnPack = new UnPack;

		pUnPack->pUser = new BaseUser;

		pUnPack->pUser->GetServerType() = servertype;

		pUnPack->pUser->GetSockfd() = fd;

		pUnPack->pUser->GetHost() = nhost;

		pUnPack->pUser->SetSandBox(&m_SandBox);

		m_Pool.insert(make_pair(fd,pUnPack));
	}
}

void UnPackHandler::recv_handler(int32 fd,void* buff,uint32 nlen)
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

			cout << "recv_handler fd,recv cnt=:" << fd << "," << m_MsgCount[fd] << endl;
		}else
		{
			cout << "recv_handler fd=" << fd << ",UnPack not exist" << endl; 
		}	
	}
	//m_sem.ReleaseSema();
}

void UnPackHandler::close_handler(int32 fd)
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

			cout << "close_handler fd =" << fd << endl;
		}
	}
}

void UnPackHandler::write_handler(int32 fd)
{
}