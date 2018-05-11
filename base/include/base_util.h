#ifndef _BASE_UTIL_H_
#define _BASE_UTIL_H_

#include<iostream>
#include<vector>
#include<list>
#include<map>
#include<pthread.h>
#include<semaphore.h>
#include<string.h>
#include<sys/time.h>
#include<sys/socket.h>
#include<sys/epoll.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<fcntl.h>
#include<unistd.h>
#include<pthread.h>

using namespace::std;

#define INFINITE	-1

typedef unsigned char uint8;
typedef unsigned int uint32;
typedef int 		int32;
typedef int 		sint32;
typedef uint16_t    uint16;

#define SAFE_DEL_POINT(p){delete(p);p=NULL;}

#endif