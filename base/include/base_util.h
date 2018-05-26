#ifndef _BASE_UTIL_H_
#define _BASE_UTIL_H_

#include<iostream>
#include<vector>
#include<list>
#include<map>
#include<pthread.h>
#include<semaphore.h>
#include<string.h>

#include<stdio.h>
#include<netdb.h>//hostent
#include<stdint.h>
#include<fcntl.h>
#include<sys/time.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<sys/epoll.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<pthread.h>

extern "C" {
#include<lua.h>
#include<lauxlib.h>
#include<lualib.h>
}

using namespace::std;

#define INFINITE	-1
#define SOCKET_ERROR -1
#define INVALID_SOCKET -1
#define SleepTime(_millsec_)		usleep( _millsec_ * 1000 )

typedef unsigned char uint8;
typedef unsigned int uint32;
typedef int 		int32;
typedef int 		sint32;
typedef uint16_t    uint16;
typedef int 		SOCKET;

#define SAFE_DEL_POINT(p){delete p;p=NULL;}

#endif