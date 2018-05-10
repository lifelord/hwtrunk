#ifndef BASE_QUEUE_H
#define BASE_QUEUE_H

#include "base_util.h"
#include "base_lock.h"

//first in first out
template<typename T>
class BaseQueue
{
public:
	BaseQueue(){}
	virtual ~BaseQueue(){}
public:
	void Push(T& elem)
	{
		AutoLock safe(&m_lock);
		m_queue.push_back(elem);
	}
	void Pop()
	{
		AutoLock safe(&m_lock);
		m_queue.pop_front();
	}
	T* Front()
	{	
		AutoLock safe(&m_lock);
		return &(*m_queue.begin());
	}
private:
	BaseLock m_lock;
	list<T> m_queue;
};

#endif