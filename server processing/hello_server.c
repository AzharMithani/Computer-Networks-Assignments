//############QJ Technologies###########
//#Author: Qaidjohar Jawadwala		 # 
//#Email: info@qjtechnologies.com 	 #
//#Website: www.qjtechnologies.com     #
//######################################

#include<stdio.h>
#include<sys/socket.h>
#include <arpa/inet.h>
#include<string.h>
#include<stdlib.h>
#include <unistd.h> // for close

#define DATA "Hello from server"

int main(int argc, char* argv[])
{
	/*Variables*/
	int sock;
	struct sockaddr_in server;
	int mysock;
	char buffer[1024];
	int rval;
	
	/*Create Sockets*/
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if(sock<0)
	{
		perror("Failed to create Socket");
		exit(1);
	}
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(5000);
	
	/*Call Bind*/
	if(bind(sock, (struct sockaddr *)&server, sizeof(server)))
	{
			perror("Bind Failed");
			exit(1);
	}
	
	/*Listen*/
	listen(sock, 5);
	
	/*Accept*/
	do
	{
		mysock = accept(sock, (struct sockaddr *) 0, 0);
		if(mysock == -1)
		{
			perror("Accept Failed");
		}
		else
		{
			memset(buffer, 0, sizeof(buffer));
	
			//Receive data from the client
			if(recv(mysock, buffer, sizeof(buffer), 0)<0)
			{
				perror("Receive Failed");
				exit(1);
			}
			printf("Received Message: %s\n",buffer);
			printf("Sending Message: %s\n",DATA);
			
			//Sendinf data to the client
			if(send(mysock,DATA,sizeof(DATA), 0)<0)
			{
				perror("Send Failed");
				close(sock);
				exit(1);
			}
			close(mysock);
		}
	}while(1);
	return 0;
}
