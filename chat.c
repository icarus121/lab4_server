#include <stdlib.h>
#include <stdio.h>
#include <string.h>     //strlen
#include <sys/socket.h>
#include <arpa/inet.h>  //inet_addr
#include <unistd.h>     //write
#include <string.h>
#include <sys/wait.h>


#define MAX 80
#define PORT 8080

// Function designed for chat between client and server.
void func(int socket_desc)
{
    char buff[MAX];
    int n;

    // infinite loop for chat
    for (;;) {
        bzero(buff, MAX);

        // read the message from client and copy it in buffer
        read(socket_desc, buff, sizeof(buff));

        // print buffer which contains the client contents
        printf("From client: %s\t To client : ", buff);
        bzero(buff, MAX);
        n = 0;

        // copy server message in the buffer
        while ((buff[n++] = getchar()) != '\n');

        // and send that buffer to client
        write(socket_desc, buff, sizeof(buff));

        // if msg contains "Exit" then server exit and chat ended
        if (strncmp("exit", buff, 4) == 0) {
            printf("Server Exit...\n");
            break;
        }
    }
}

int main(int argc , char *argv[])
{
	int socket_desc, new_socket, c, len;
        struct sockaddr_in server , client;
        char *message, reply[2000], msg[2000];

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
	bzero(&server, sizeof(server));

        //Prepare the sockaddr_in structure
	server.sin_family = AF_INET;
        //server.sin_addr.s_addr = htonl(INADDR_ANY);
        server.sin_port = htons(8888);
	server.sin_addr.s_addr = htonl(INADDR_ANY);


        //Bind = bind(sockid, &addrport, size)
        if(( bind(socket_desc,(struct sockaddr *)&server , sizeof(server))) != 0)
        {
                puts("bind failed");
                exit(0);
        }
        else
        {
                puts("bind done");
        }

	 if(listen(socket_desc, 3)==0)
        {
                puts("Listen success\n");
		//len = sizeof(client);
        }
        else
        {
                puts("Listen fail\n");
	}

	len = sizeof(client);

	new_socket = accept(socket_desc, (struct sockaddr *)&client, &len);
	if(new_socket<0)
	{
		printf("Server accept failed..\n");
		exit(0);
	}
	else
		printf("Server accept the client..\n");

	func(new_socket);
        close(socket_desc);


        //Accept and incoming connection
        //accept = accept(sock, &name, &namelen)
        /*puts("Waiting for incoming connections...");
	//int pid = fork();
	c = sizeof(struct sockaddr_in);
	//new_socket = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c);
	while((new_socket = accept(socket_desc, (struct sockaddr *)&client, (socklen_t *)&c)))
	{
		//new_socket = accept(socket_desc, (struct sockaddr *)&client, &c);

	if(new_socket<0)
	{
		puts("New Socket failed");
	}
	else
	{
		puts("New Socket accepted");
	}

	/*if(pid < 0)
	{
		puts("Could not find fork");
		exit(1);
	}
	if (pid == 0)
	{
		//this is the child process
		close(socket_desc);

		recv(new_socket, message, 2000, 0);
		puts(message);
		int i = 0;


		while(1)
		{
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

			if (strcmp(reply, "exit/n") == 0)
			{
				printf("%s logout\n", message);
				break;
			}
			else if((strcmp(reply, "\n") < 0 || strcmp(reply, "\n") >0))
				printf("%s:%s", message, reply);
			else if((strcmp(reply, "\n") == 0) && i == 0)
				printf("%s joined\n", reply);
		}
		close(new_socket);
		exit(0);
	}
	else
	{
		wait(NULL);
		//this is parent
		close(new_socket);
	}*/


	/*while(1){
	if(send(new_socket , message, strlen(message), 0)<0)
		puts("failed");
	else
	{
		printf("Enter message:");
	        scanf("%2000s", message);
		puts(message);
	}*/

	//read(new_socket, reply, 2000);
	//puts(reply);

	//reply to the client
	//message ="Hello Client, I have received your connection. But I have to go now, bye \n";
	//write(new_socket, message, strlen(message));
	//}
	//msg = send(new_socket, msg, 2000,0);
	//puts(msg;

	/*if(new_socket<0)
	{
		perror("accept failed");
		return 1;
	}

	close(new_socket);*/
	//close(socket_desc);

	//func(new_socket);
	//close(sockfd);
	//return 0;
}
