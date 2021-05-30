#include "../lib/netlib.h"

int main(int argc, char *argv[]) {

	int listenfd, connfd, count = 0;
	long file_len;
	FILE* fd;
	pid_t childpid;
	char buffer[MAXLINE + 1];

	struct sockaddr_in servaddr;
	struct sockaddr_in clivaddr;
	socklen_t len;
	listenfd = Socket(AF_INET, SOCK_STREAM, 0);
	bzero(&servaddr, sizeof(servaddr));
	bzero(buffer, sizeof(buffer));
	//ipv4
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(1234);

	int reuse = SO_REUSEADDR;
	setsockopt(listenfd, SOL_SOCKET,SO_REUSEADDR, &reuse, sizeof(reuse));

	Bind(listenfd, (SA *)&servaddr, sizeof(servaddr));
	Listen(listenfd, LISTENQ);
	
	signal(SIGCHLD, sig_chid);
	while(1){
		/* connect different cilent */
		len = sizeof(clivaddr);
		if( (connfd = Accept(listenfd, (SA *)&clivaddr, &len)) < 0){
			if (errno == EINTR) {
				continue;
			}else {
				perror("accept error");
				exit(-1);
			}
		}
		count++;
		/* print cilent's ip and port */
		printf("the %d client\n",count);
		printf("cilent's ip = %s, port = %d\n", inet_ntoa(clivaddr.sin_addr),
				htons(clivaddr.sin_port));

		if ( (childpid = fork()) == 0) { /* child process */
			close(listenfd);
			printf("this process' pid = %d\n", getpid());
			/*echo strings to stdout*/
			str_echo(connfd);
			exit(0);
		}
	}

	close(connfd);
	return 0;
}

void str_echo(int sockfd){
	int n;
	char sendline[MAXLINE],cli_name[MAXLINE],recvline[MAXLINE];
	
	n = recv(sockfd,cli_name, MAXLINE, 0);
	if ( n == 0) {
		close(sockfd);
		printf("Client disconnected.\n");
		return;
	}
	cli_name[n - 1] = '\0';
	printf("Client's name is %s.\n", cli_name);
	while ((n = recv(sockfd, recvline, MAXLINE, 0))) {
		recvline[n] = '\0';
		printf("received client( %s )message: %s", cli_name, recvline);
		
		/*if ( fgets(sendline, MAXLINE, stdin) == NULL){*/
		/*    printf("\nExit.\n");*/
		/*    return;*/
		/*}*/
		/*sendline[sizeof(sendline)-1] = '\0';*/
		/*send(sockfd, sendline, strlen(sendline),0);*/
	}
}
