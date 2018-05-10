#include "base_thread.h"

BaseThread::BaseThread()
{
    tid = 0;
}

BaseThread::~BaseThread()
{
}

bool BaseThread::Start()
{
	bool bStart = CreateTheard();
	if (bStart)
	{
		GetbActive() = true;
	}
	return bStart;
}

void BaseThread::Stop()
{
   pthread_join(tid, NULL);
   tid = 0;
   bActive = false;
}

void* BaseThread::BaseThreadPoc(void* param)
{
	BaseThread* pThread = (BaseThread*)param;
	if (pThread != NULL)
	{
		pThread->Run();
	}
}

bool BaseThread::CreateTheard()
{
	uint32 err = pthread_create( &tid, NULL, &BaseThreadPoc, this );
	if (err != 0)
	{
		return false;
	}
	return true;
}