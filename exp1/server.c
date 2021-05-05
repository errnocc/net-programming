#include "unp.h"
#include <strings.h>
#include <time.h>

int main(int argc, char *argv[]) {
  int listenfd, connfd;
  struct sockaddr_in servaddr;
  char buff[MAXLINE];
  time_t ticks;

  if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    perror("socket error");
  }

  bzero(&servaddr, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servaddr.sin_port = htons(1234);

  int reuse = 1;
  setsockopt(listenfd, SOL_SOCKET, SO_REUSEPORT, &reuse, sizeof(reuse));

  if (bind(listenfd, (SA *)&servaddr, sizeof(servaddr))) {
    perror("bind error");
  }

  if (listen(listenfd, LISTENQ)) {
    perror("listen error");
  }

  while (1) {
    if ((connfd = accept(listenfd, (SA *)NULL, NULL))) {
      perror("accept error");
    }
    ticks = time(NULL);
    snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));
    if (write(listenfd, buff, sizeof(buff))) {
      perror("write error");
    }
    if (close(connfd) < 0) {
      perror("close error");
    }
  }
  return 0;
}
