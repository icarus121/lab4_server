#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>		//inet_addr

int main(int argc, char *argv[])
{
	int socket_desc;
	struct sockaddr_in server;

	//create socket
	socket_desc = socket(AF_INET,SOCK_STREAM, 0);
	//socket(domain,type,protocol)
	//domain = AF_INET: IPv4 internet protocols
	//type = SOCK_STREAM: TCP, reliable


	if(socket_desc == -1)
	{
		printf("Could not create socket");
	}
	else
	{
		printf("Succes creating socket.\n");
	}

	server.sin_addr.s_addr=inet_addr("192.168.0.103");
	server.sin_family=AF_INET;
	server.sin_port=htons(22); //htons = host to network short

	//connect to remote server
	if (connect(socket_desc, (struct sockaddr *)&server, sizeof(server)) <0 )
	{
		puts("Connect error.\n");
		return 1;
	}
	else
		puts("Connected.\n");

	return 0;
}
