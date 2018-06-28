#ifndef BASE_SIGNAL_H_
#define BASE_SIGNAL_H_

#include"base_util.h"

#include"base_lock.h"

typedef void (*Sigfunc)(int signo);

class SignalMgr
{
public:
	SignalMgr();
	~SignalMgr();

	bool Init(Sigfunc custom, Sigfunc exit, Sigfunc error);

	//arrSig:捕捉信号集
	bool SignalRegister(int* arrSig,int len,Sigfunc func);
private:
	//捕捉单个信号
	bool signal(int signo,Sigfunc func);
};

extern SignalMgr g_SignalMgr;

#endif