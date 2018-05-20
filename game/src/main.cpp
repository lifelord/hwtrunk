#include "base_include.h"

int main()
{
	CSocketServer g_SocketServer;

	UnPackHandler g_UnpackHandler;

	g_SocketServer.Init(&g_UnpackHandler);

	//client server port:8001
	g_SocketServer.RegListenSocket(INADDR_ANY,8001);

	//web server port:8002
	g_SocketServer.RegListenSocket(INADDR_ANY,8002);

	g_UnpackHandler.Start();

	g_SocketServer.Start();

	g_UnpackHandler.Stop();

	g_SocketServer.Stop();

	/*char buff[512] = {"hello"};

	CStream pack;

	pack.write(buff,sizeof(buff));

	char buff2[512];

	memset(buff2,0,sizeof(buff2));

	pack.read(buff2,sizeof(buff2));

	std::cout << buff2 << std::endl;*/

	return 0;	
}