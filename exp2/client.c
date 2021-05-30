#include "../lib/netlib.h"

int main(int argc, char *argv[]) {
	//套接字描述符, 缓冲区， 套接字结构体声明
	FILE *fd;
	int sockfd, n, count = 0;
	char buffer[MAXLINE + 1];
	struct sockaddr_in servaddr;

	if (argc != 2) {
		perror("usage: client.out <IPaddress>");
		exit(-1);
	}

	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("socket error");
		exit(-1);
	}
	//数据头结构体清0
	bzero(&servaddr, sizeof(servaddr));

	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(1234);

	//将ASCII字符串ip转换成正确的格式
	if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0) {
		fprintf(stderr, "inet_pton error for %s", argv[1]);
		exit(-1);
	}
	//链接
	servaddr.sin_addr.s_addr = inet_addr(argv[1]);
	if (connect(sockfd, (SA *)&servaddr, sizeof(servaddr)) < 0) {
		perror("connect error");
		exit(-1);
	} 

	str_cli(stdin, sockfd);
	close(sockfd);
	exit(0);
}
