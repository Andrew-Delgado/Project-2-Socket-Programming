/**
 * @author Andrew Delgado and Christian Baiza
 * @date 2-24-2019
 * @version 1.0
 * 
 * This program acts as a client to receive and send messages to a Server(Server.c).
 * This achieved by connecting to port 8080 with the IP address of 127.0.0.1.
 * Once the client connects to the server the client must send the first message.
 * 	The message is then displayed in the terminal and then each program must take turns
 * 	sending messages.
 * 
 */
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#define PORT 8080

int main(int argc, char const *argv[])
{
	struct sockaddr_in address;
	int sock = 0, valread;
	struct sockaddr_in serv_addr;
	char clientMessage[200] = {0};
	char buffer[1024] = {0};
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		printf("\n Socket creation error \n");
		return -1;
	}

	memset(&serv_addr, '0', sizeof(serv_addr));

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);

	// Convert IPv4 and IPv6 addresses from text to binary form
	if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)
	{
		printf("\nInvalid address/ Address not supported \n");
		return -1;
	}

	if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
	{
		printf("\nConnection Failed \n");
		return -1;
	}

	while(1)//This is an infinite loop that keeps the chat indefinitely open
	{
		if(strlen(clientMessage)> 0)
		{
			memset(clientMessage, 0, sizeof(clientMessage));
			memset(buffer, 0, sizeof(buffer));
		}
		
		printf("Enter Message: ");
		fgets(clientMessage, 200,stdin);
		send(sock , clientMessage , strlen(clientMessage) , 0 );

		valread = read( sock , buffer, 1024);
		printf("server: %s\n",buffer );
	}

	return 0;
}

