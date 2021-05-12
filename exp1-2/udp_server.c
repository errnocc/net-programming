#include "../lib/netlib.h"

int main(int argc, char *argv[])
{
	int sockfd, n;
	struct sockaddr_in servaddr, cliaddr;
	char mesg[MAXLINE];
	socklen_t len;
	if( (sockfd =socket(AF_INET, SOCK_DGRAM, 0)) < 0){
		perror("socket error");
		exit(-1);
	}
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family      = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port        = htons(1234);

	if (bind(sockfd, (SA*) &servaddr, sizeof(servaddr)) == -1 )   {
		perror("bind error");
		exit(-1);
	}
	
	//write some massage to stdout
	len = sizeof(cliaddr);
	while (1) {
		if ( (n = recvfrom(sockfd, mesg, MAXLINE, 0,(SA *) &cliaddr, &len)) == -1 ){
			perror("recvfrom error");
			exit(-1);

		}
		if (sendto(sockfd, mesg, n, 0, (SA*)&cliaddr, len) == -1) {
			perror("sendto error");
			exit(-1);
		}
	}
	return 0;
}
