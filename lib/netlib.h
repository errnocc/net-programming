#include <sys/wait.h>
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
#include <errno.h>
#include <signal.h>
#include <pthread.h>

#define MAXLINE 4096
#define SA struct sockaddr
#define LISTENQ 10

char* Fgets(char *buffer, int len, FILE *fp){
	printf("Input string to server:");
	return(fgets(buffer, MAXLINE, fp));
}

int Write(int __fd, const void *__buf, size_t __n){
	int n;
	if( (n = write(__fd, __buf,  __n)) < 0){
		perror("write error");
		exit(-1);
	}
	return n;
}

int Read(int __fd, void *__buf, size_t __nbytes){
	int n;
	if ( (n = read( __fd, __buf, __nbytes) ) < 0){
		perror("read error");
		exit(-1);
	}
	return n;
}

int Socket(int __domain, int __type, int __protocol){
	int n;
	if ((n = socket( __domain, __type, __protocol)) == -1) {
		perror("Socket error");
		exit(-1);
	}
	return n;
}

int Bind(int __fd, const struct sockaddr *__addr, socklen_t __len){
	int n;
	if ( (n = bind(__fd, __addr, __len)) == -1) {
		perror("Bind error");
		exit(-1);
	}
	return n;
}

int Connect(int __fd, const struct sockaddr *__addr, socklen_t __len){
	int n;
	if ( (n = connect(__fd, __addr, __len)) == -1) {
		perror("Connect error");
		exit(-1);
	}
	return n;

}

void sig_chid(int signo){
	pid_t pid;
	int stat;
	while ( (pid = waitpid(-1, &stat, WNOHANG)) > 0) {
		printf("child %d terminated\n", pid);
	}
	return;
}


int Listen(int __fd, int __n){
	int n;
	if ( (n = listen(__fd, __n)) == -1) {
		perror("Listen error");
		exit(-1);
	}
	return n;
}

int Accept(int __fd, struct sockaddr *__addr, socklen_t *_addr_len){
	int n;
	if ((n = accept(__fd, __addr, _addr_len)) == -1) {
		perror("Accept error");
		exit(-1);
	}
	return n;
}

int Select(int __nfds, fd_set *__readfds, fd_set *__writefds, fd_set *__exceptfds, struct timeval *__timeout){
	int n;
	if ( (n = select(__nfds, __readfds, __writefds, __exceptfds, __timeout)) == -1) {
		perror("select error");
		exit(-1);
	}
	return n;
}

void str_echo(int sockfd);
void str_cli(FILE *fp, int sockfd);
