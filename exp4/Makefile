all: client server
.PHONY : clean

client: client.o
	g++ -g -Wall -o client client.o
server:server.o
	g++ -g -Wall -o server server.o -lm

server.o:
	g++ -g -c server.cpp
client.o: 
	g++ -g -c client.cpp
clean:
	rm *.o
