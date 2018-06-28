#include "base_include.h"

static void CatchExit(int signo)
{
	cout << "CatchExit Signo,Signo=" << signo << endl;
}

int main()
{
	CSocketServer g_SocketServer;

	UnPackHandler g_UnpackHandler;

	SignalMgr g_SignalMgr;

	g_SignalMgr.Init(NULL,CatchExit,NULL);

	g_SocketServer.Init(&g_UnpackHandler);

	//client server port:8001
	g_SocketServer.RegListenSocket(INADDR_ANY,8001,QSERVER_TYPE_NORMAL);

	//web server port:8002
	g_SocketServer.RegListenSocket(INADDR_ANY,8002,QSERVER_TYPE_WEB);

	g_UnpackHandler.Init("../game/lua/preload.lua");

	g_UnpackHandler.Start();

	g_SocketServer.Start();

	g_UnpackHandler.Stop();

	g_SocketServer.Stop();

	cout << "Exist Game!" << endl;

	/*char buff[512] = {"hello"};

	CStream pack;

	pack.write(buff,sizeof(buff));

	char buff2[512];

	memset(buff2,0,sizeof(buff2));

	pack.read(buff2,sizeof(buff2));

	std::cout << buff2 << std::endl;*/

	return 0;	
}