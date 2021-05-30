#include "../lib/netlib.h"

int main(int argc, char *argv[]) {

	int listenfd, connfd, count = 0;
	long file_len;
	FILE* fd;

	char buffer[MAXLINE + 1];

	struct sockaddr_in servaddr;
	struct sockaddr_in clivaddr;
	socklen_t len;

	if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("socket error");
		exit(-1);
	}

	bzero(&servaddr, sizeof(servaddr));
	bzero(buffer, sizeof(buffer));
	//ipv4
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(1234);

	int reuse = SO_REUSEADDR;
	setsockopt(listenfd, SOL_SOCKET,SO_REUSEADDR, &reuse, sizeof(reuse));

	if (bind(listenfd, (SA *)&servaddr, sizeof(servaddr))) {
		perror("bind error");
		exit(-1);
	}

	if (listen(listenfd, LISTENQ) == -1) {
		perror("listen error");
		exit(-1);
	}

	len = sizeof(clivaddr);
	if ((connfd = accept(listenfd, (SA *)&clivaddr, &len)) == -1) {
		perror("accept error");
		exit(-1);
	}
	printf("cilent's ip = %s, port = %d\n", inet_ntoa(clivaddr.sin_addr),
			htons(clivaddr.sin_port));
	if((fd = fopen("text_2.txt", "r")) == NULL){
		perror("fopen errnor");
	}
	fseek(fd, 0, SEEK_END);
	file_len = ftell(fd);
	rewind(fd);
	while(1){
		count = fread(buffer,1, 5, fd);
		if(count > 0){
			send(connfd, buffer, 5, 0);
			printf("send %d bytes\n", count);
		}else {
			break;
		}
	}
	fclose(fd);
	close(connfd);
	close(listenfd);
	return 0;
}
