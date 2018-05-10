#ifndef _BASE_THREAD_H
#define _BASE_THREAD_H

#include"base_util.h"

typedef void*(*tThreadPoc)(void*);

class BaseThread
{
public:
	BaseThread();
	~BaseThread();

	inline bool& GetbActive(){return bActive;}
	bool CreateTheard();      //创建一个线程
	bool Start();
	void Stop();   //结束一个线程
	virtual int Run() = 0;
private:
	static void* BaseThreadPoc(void* param);
	pthread_t tid;  //线程id
	bool bActive;
};

#endif