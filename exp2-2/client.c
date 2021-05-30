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

	sockfd = Socket(AF_INET, SOCK_STREAM, 0);
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
	Connect(sockfd, (SA *)&servaddr, sizeof(servaddr));
	str_cli(stdin, sockfd);

	close(sockfd);
	exit(0);
}

void str_cli(FILE *fp, int sockfd){
	char sendline[MAXLINE], recvline[MAXLINE], pid[20];
	int num = 0;
	printf("Connected to server.\n");
	printf("Input client's name:");
	if ( fgets(sendline, MAXLINE, fp) == NULL){
		printf("\nExit.\n");
		return;
	}
	sendline[sizeof(sendline)-1] = '\0';
	send(sockfd, sendline, strlen(sendline),0);
	//get some strings from stdout
	while (Fgets(sendline, MAXLINE, fp) != NULL) {
		//write strings to sockfd
		send(sockfd, sendline, strlen(sendline), 0);
		//get return from sockfd
		/*if ( (num = recv(sockfd, recvline, MAXLINE, 0)) == 0) {*/
			/*perror("str_cli:server terminated prematurely");*/
			/*return;*/
		/*}*/
		/*recvline[num] = '\0';*/
		//show it
		/*fputs(recvline, stdout);*/
	}
	printf("\nExit\n");
	return;
}


