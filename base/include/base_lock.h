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

#endif