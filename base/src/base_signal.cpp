#include "base_signal.h"

SignalMgr::SignalMgr()
{
}

SignalMgr::~SignalMgr()
{
}

bool SignalMgr::Init(Sigfunc custom, Sigfunc exit, Sigfunc error)
{
	int sig_ignore[] = 
    {
        SIGIO/*异步IO*/,
        SIGPIPE/*管道出错*/,
        SIGPOLL/*异步IO*/,
        SIGPROF/*setitimer到期*/,
        SIGURG/*紧急事件,如网络带外数据*/,
        SIGVTALRM/*setitimer产生*/,
        SIGCHLD/*子进程终止*/,
        SIGCONT/*停止的进程继续执行*/,
        SIGHUP/*终端关闭*/,
    };

    int sig_custom[] = 
    {
        SIGUSR1/*自定义信号1*/,
    };

    //正常关闭信号
    int signal_exit[] =
    {
        SIGINT/*ctrl+c,外部调用*/,
        SIGTERM/*kill(),内部调用*/,
    };

    int sig_error[] = 
    {
    };

	bool bOk = true;
	bOk = SignalRegister(sig_ignore, sizeof(sig_ignore) / sizeof(int), SIG_IGN);
    if (!bOk) return bOk;

    bOk = SignalRegister(sig_custom, sizeof(sig_custom) / sizeof(int), custom);
    if (!bOk) return bOk;

    bOk = SignalRegister(signal_exit, sizeof(signal_exit) / sizeof(int), exit);
    if (!bOk) return bOk;

    bOk = SignalRegister(sig_error, sizeof(sig_error)/sizeof(int), error);
    if(!bOk) return bOk;
}

bool SignalMgr::signal(int signo,Sigfunc func)
{
	struct sigaction act,oact;

	//清空屏蔽的信号集
	sigemptyset(&act.sa_mask);

	//设置捕捉到signo信号时回调函数
	act.sa_handler = func;
	act.sa_flags = 0;

	//时钟消息，希望系统调用中断后不重启
	if(signo == SIGALRM)
	{
		//系统中断后不重启
		#ifdef SA_INTERRUPT
			act.sa_flags |= SA_INTERRUPT;
		#endif
	}else
	{
		//系统调用中断的自动重启
		act.sa_flags |= SA_RESTART;
	}
	//发生signo时的调用act.sa_handler回调函数
	//oact.sa_handler
	//进程收到信号后,将signo加入到该进程的信号屏蔽队列中,重复的信号就暂时在阻塞队列中了,
	//执行完act.sa_handler回调函数,将其地址传递给oact.sa_handler,
	//阻塞的信号集被清空,进程就可以接收到阻塞队列中重复的信号
	if(sigaction(signo, &act, &oact) < 0)
	{
		return false;
	}
	return true;
}

bool SignalMgr::SignalRegister(int* arrSig,int len,Sigfunc func)
{
	for(int i = 0;i<len; ++i)
	{
		if(!signal(arrSig[i],func))
		{
			return false;
		}
	}
	return true;
}