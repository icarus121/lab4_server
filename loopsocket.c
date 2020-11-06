#include <stdio.h>
#include <string.h>	//strlen
#include <sys/socket.h>
#include <arpa/inet.h>	//inet_addr
#include <unistd.h>	//write
#include <string.h>

int main(int argc , char *argv[])
{
	int socket_desc , new_socket , c;
	struct sockaddr_in server , client;
	char *message, reply[2000];

	//Create socket
	//socket = socket(domain, type, protocol)
	socket_desc = socket(AF_INET , SOCK_STREAM , 0);
	if (socket_desc == -1)
	{
		printf("Could not create socket");
	}
	else
	{
		printf("Socket created.\n");
	}

	//Prepare the sockaddr_in structure
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(8888);

	//Bind = bind(sockid, &addrport, size)
	if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
	{
		puts("bind failed");
		return 1;
	}
	else
	{
		puts("bind done");
	}

	//Listen = listen(sock, queulen)
	if(listen(socket_desc, 3)==0)
	{
		puts("Listen success\n");
	}
	else
	{
		puts("Listen fail\n");
	}

	//Accept and incoming connection
	//accept = accept(sock, &name, &namelen)
	puts("Waiting for incoming connections...");
	c = sizeof(struct sockaddr_in);
	while( (new_socket = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c)))
	{
		puts("Connection accepted");

		//Reply to the client
		message = "Hello Client , I have received your connection. But I have to go now, bye\n";
		write(new_socket , message , strlen(message));

		recv(new_socket, reply, 2000, 0);
		puts(reply);
	}

	if (new_socket<0)
	{
		perror("accept failed");
		return 1;
	}
	close(socket_desc);
	return 0;
}

