#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>	//inet_addr
#include <string.h>

int main(int argc , char *argv[])
{
	int socket_desc;
	struct sockaddr_in server;
	char *message;

	//Create socket
	socket_desc = socket(AF_INET , SOCK_STREAM , 0);
	if (socket_desc == -1)
	{
		printf("Could not create socket");
	}
	else
	{
		printf("Successfully connect.\n");
	}

	server.sin_addr.s_addr = inet_addr("192.168.0.103");
	server.sin_family = AF_INET;
	server.sin_port = htons(22);

	//Connect to remote server
	//connect(sock, &name, namelen)
	if (connect(socket_desc, (struct sockaddr *)&server, sizeof(server)) < 0)
	{
		puts("connect error");
		return 1;
	}
	else
	{
		puts("Connected \n");
	}

	//Send some data
	//for sock_stream: send(sock, &buf, len, flags)
	message = "connect";
	if(send(socket_desc, message, strlen(message), 0) < 0)
	{
		puts("Send failed");
		return 1;
	}
	else
	{
		puts("Data Send\n");
		return 0;
	}
}

