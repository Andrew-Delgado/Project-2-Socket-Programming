// Server side C/C++ program to demonstrate Socket programming
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

	while(1)
	{
	//printf("\nserverMessage length - %ld\n", strlen(serverMessage));
	if(strlen(serverMessage)> 0)
	{
		memset(serverMessage, 0, sizeof(serverMessage));
		memset(buffer, 0, sizeof(buffer));
	}
	//printf("serverMessage length - %ld\n", strlen(serverMessage));

	valread = read( new_socket , buffer, 1024);
	printf("client: %s\n",buffer );

	// printf("serverMessage length - %ld\n", strlen(serverMessage));
	// printf("buffer length - %ld\n", strlen(buffer));
  printf("Enter Message: ");
	fgets(serverMessage, 200,stdin);
	send(new_socket , serverMessage , strlen(serverMessage) , 0 );

	//memset(serverMessage, 0, sizeof(serverMessage));


	}
	return 0;
}