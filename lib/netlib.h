#include <arpa/inet.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdio.h>
#include <math.h>
#define MAXLINE 4096
#define SA struct sockaddr
#define LISTENQ 10

//int Socket(int __domain, int __type, int __protocol){
//    int fd;
//    if( (fd = Socket(__domain,__type, __protocol)) )
//}
//
