#ifndef BASE_LOCK_H
#define BASE_LOCK_H

#include "base_util.h"

class BaseLock
{
	inline BaseLock(const BaseLock& rhs);
	BaseLock& operator=(const BaseLock& rhs);
public:
	inline BaseLock()
	{
		pthread_mutexattr_t attr;
		pthread_mutexattr_init(&attr);
		pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE); //设置成递归类型
		pthread_mutex_init(&mutex, &attr);
		pthread_mutexattr_destroy(&attr);
	}
	inline virtual ~BaseLock()
	{
		pthread_mutex_destroy(&mutex);
	}

public:
	uint32 lock() 
	{
		pthread_mutex_lock(&mutex);
	}

	uint32 unLock()
	{
		pthread_mutex_unlock(&mutex);
	}
private:
	pthread_mutex_t mutex;
};

//自动锁
class AutoLock
{
	inline AutoLock(AutoLock& rhs);
	AutoLock& operator= (const AutoLock& rhs);
public:
	inline AutoLock(BaseLock* pLock) :m_pLock(pLock)
	{
		pLock->lock();
	}
	inline virtual ~AutoLock()
	{
		m_pLock->unLock();
	}

private:
	BaseLock* m_pLock;
};

class BaseSema : public BaseLock
{
	BaseSema(const BaseSema &rhs);
	BaseSema& operator=(const BaseSema &rhs);

public:
	inline BaseSema(){};
	inline virtual ~BaseSema(){ CloseSema(); };

	int WaitSema(unsigned long nTime = INFINITE)
	{
		int nResult = sem_wait(&m_Semaphore);
		if (nResult == -1) nResult = (errno == EINTR) ? 0x00 : -1;

        //////////////////////////////////////////////////////////////////////////
        //留着
        /*timeval tv = {0};
        timespec ts = {0};

        gettimeofday(&tv, NULL);
        tv.tv_usec += milli_secs * 1000;
        if ( tv.tv_usec >= 1000000 )
        {
            tv.tv_sec += tv.tv_usec / 1000000;
            tv.tv_usec %= 1000000;
        }
        ts.tv_sec = tv.tv_sec;
        ts.tv_nsec = tv.tv_usec * 1000;

        while (true)
        {
            if (0== sem_timedwait(semaphore,&ts))
                return 1;

            switch(errno)
            {
            case ETIMEDOUT:
                return 0;
            case EINTR:
                continue;
            default:
                return -1;
            }
        }*/
		return nResult;
	}
	//发出几次信号
	inline int ReleaseSema(int nCount = 1)
	{
		int i = nCount;
		while (i-- > 0x00) sem_post(&m_Semaphore);
		return nCount;
	}

	inline int CreateSema()
	{
		int nResult = sem_init(&m_Semaphore, 0, 0);
		if (nResult == -1) return 0x00;
		return 0x01;
	}

	inline void CloseSema(){ sem_destroy(&m_Semaphore); }

protected:
	sem_t m_Semaphore;
};

#endif