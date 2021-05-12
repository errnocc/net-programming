#include "../lib/netlib.h"

int main(int argc, char *argv[])
{
	int sockfd, n, servlen;
	char sendline[MAXLINE], recvline[MAXLINE];
	struct sockaddr_in servaddr, cliaddr;
	FILE fp;
	if( argc != 2){
		perror("unset client ip address");
		exit(-1);
	}
	servlen = sizeof(servaddr);
	bzero(&servaddr, servlen);
	servaddr.sin_family = AF_INET;
	inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

	if ( ( sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("socket error");
		exit(-1);
	}
	
	//read command  form stdin and show it
	while ((fgets(sendline, MAXLINE, stdin) != NULL)) {
		if ( sendto(sockfd, sendline, strlen(recvline), 0, (SA *)&servaddr, servlen) == -1) {
			perror("sendto error");
			exit(-1);
		}
		if ((n = recvfrom(sockfd, recvline, MAXLINE, 0, NULL, NULL))) {
			perror("recvfrom error");
			exit(-1);
		}
		recvline[n] = '\0';
		fputs(recvline, stdout);
	}

	exit(0);
}
