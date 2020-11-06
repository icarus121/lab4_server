#include <stdlib.h>
#include <stdio.h>
#include <string.h>     //strlen
#include <sys/socket.h>
#include <arpa/inet.h>  //inet_addr
#include <unistd.h>     //write
#include <string.h>

int main(int argc , char *argv[])
{
        int socket_desc , new_socket , c;
        struct sockaddr_in server , client;
        char message[2000], reply[2000], msg[2000];

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
	new_socket = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c);
	//while(1){
	//new_socket = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c);

	if(new_socket<0)
	{
		puts("New Socket failed");
	}
	else
	{
		puts("New Socket accepted");
	}


	//Reply to the client
	int n = recv(new_socket, reply, 2000, 0);
        if (n<0)
                puts("received error");
        else
	{
		//read(new_socket, reply, 2000);
		puts("Received successful");
                puts(reply);
	}

	while(1){
	if(send(new_socket , message, strlen(message), 0)<0)
		puts("failed");
	else
	{
		printf("Enter message:");
	        scanf("%2000s", message);
		puts(message);
	}

	read(new_socket, reply, 2000);
	puts(reply);
	}
	//msg = send(new_socket, msg, 2000,0);
	//puts(msg;

	close(new_socket);
        close(socket_desc);
        return 0;
}

