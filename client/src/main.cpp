#include "base_include.h"

#define SERVER_PORT 8001 

void usage(char *name)  
{  
    printf("usage: %s IP\n", name);  
}

//单个客户端
int main(int argc, char *argv[])
{	
	int server_fd, client_fd, length = 0;  
    struct sockaddr_in server_addr, client_addr;  
    socklen_t socklen = sizeof(server_addr);  
  
    if(argc < 2)  
    {  
        usage(argv[0]);  
        exit(1);  
    }  
    if((client_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)  
    {  
        printf("create socket error, exit!\n");  
        exit(1);  
    }  
    srand(time(NULL));  
    bzero(&client_addr, sizeof(client_addr));  
    client_addr.sin_family = AF_INET;  
    client_addr.sin_addr.s_addr = htons(INADDR_ANY);  
  
    bzero(&server_addr, sizeof(server_addr));  
    server_addr.sin_family = AF_INET;  
    inet_aton(argv[1], &server_addr.sin_addr);  
    server_addr.sin_port = htons(SERVER_PORT);  
  
    if(connect(client_fd, (struct sockaddr*)&server_addr, socklen) < 0)  
    {  
        printf("can not connect to %s, exit!\n", argv[1]);  
        printf("%s\n", strerror(errno));  
        exit(1);  
    }

    //测试代码，发argv[2]个包，看解析是否正确
    uint32 num = atoi(argv[2]);
    cout << num;

    for(uint32 i = 0;i<num;++i)
    {
        CStream stream;
        MsgHead*& pHead = stream.NewHead<MsgHead>();
        pHead->pack_start = PACKET_START;
        pHead->pack_type = 1;
        pHead->pack_len = sizeof(MsgHead);
        pHead->pack_cmd = i;
        send(client_fd,&stream[0],stream.length(),0);
    }

    for(;;){}

    return 0;
}