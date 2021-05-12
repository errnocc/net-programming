all: udp_server udp_client
.PHONY : clean

udp_server:udp_server.o
	cc -g -Wall -o udp_server udp_server.o

udp_client:udp_client.o
	cc -g -Wall -o udp_client udp_client.o

udp_client.o:
	cc -g -c udp_client.c
udp_server.o:
	cc -g -c udp_server.c

clean: 
	rm *.o
