all: client server
.PHONY : clean

client: client.o
	gcc -g -Wall -o client client.o 
server:server.o
	gcc -g -Wall -o server server.o -lpthread

server.o:
	gcc -g -c server.c
client.o: 
	gcc -g -c client.c
clean:
	rm *.o
