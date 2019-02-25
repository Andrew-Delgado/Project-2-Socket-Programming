/**
 * @author Andrew Delgado and Christian Baiza
 * @date 2-24-2019
 * @version 1.0
 * 
 * This program acts as a server to receive and send messages to a client(Client.c).
 * This achieved by setting up a socket with the port 8080,
 * 	the program then waits and listens for a client trying to connect.
 * Once the client connects to the server it waits for the client to send the first message,
 * 	the message is then displayed in the terminal and then each program must take turns
 * 	sending messages.
 * 
 */
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#define PORT 8080


int main(int argc, char const *argv[])
{
	int server_fd, new_socket, valread;
	struct sockaddr_in address;
	int opt = 1;
	int addrlen = sizeof(address);
	char buffer[1024] = {0};
	char serverMessage[200] = {0};

	// Creating socket file descriptor
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
	{
		perror("socket failed");
		exit(EXIT_FAILURE);
	}

	// // Forcefully attaching socket to the port 8080
	// if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
	// 											&opt, sizeof(opt)))
	// {
	// 	perror("setsockopt");
	// 	exit(EXIT_FAILURE);
	// }
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons( PORT );

	// Forcefully attaching socket to the port 8080
	if (bind(server_fd, (struct sockaddr *)&address,
								sizeof(address))<0)
	{
		perror("bind failed");
		exit(EXIT_FAILURE);
	}
	if (listen(server_fd, 3) < 0)
	{
		perror("listen");
		exit(EXIT_FAILURE);
	}
	if ((new_socket = accept(server_fd, (struct sockaddr *)&address,
					(socklen_t*)&addrlen))<0)
	{
		perror("accept");
		exit(EXIT_FAILURE);
	}

	while(1)//This is an infinite loop that keeps the chat indefinitely open
	{

		//clears the buffer
		if(strlen(serverMessage)> 0)
		{
			memset(serverMessage, 0, sizeof(serverMessage));
			memset(buffer, 0, sizeof(buffer));
		}

		valread = read( new_socket , buffer, 1024);
		printf("client: %s\n",buffer );

		printf("Enter Message: ");
		fgets(serverMessage, 200,stdin);
		send(new_socket , serverMessage , strlen(serverMessage) , 0 );
	}
	return 0;
}
