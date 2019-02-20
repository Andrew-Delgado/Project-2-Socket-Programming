CC1=gcc

CFLAGS = -g -c -Wall
#CFLAGS = -ansi -c -Wall -pedantic
all: Client Server

A = Client.o
B = Server.o

Client: $A
	$(CC1) -o Client $A

Client.o: client.c
	$(CC1) -c client.c

Server: $B
	$(CC1) -o Server $B

Server.o: server.c
	$(CC1) -c server.c

clean:
	rm *.o
	rm Server
	rm Client
