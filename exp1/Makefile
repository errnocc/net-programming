#client: client.o
	#gcc -g -Wall -o client client.o
#
server:server.o
	gcc -g -Wall -o server server.o

server.o:
	gcc -c server.c

client.o: 
	gcc -c client.c

clean:
	rm server.o client.o 
