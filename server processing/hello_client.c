//############QJ Technologies###########
//#Author: Qaidjohar Jawadwala		 # 
//#Email: info@qjtechnologies.com 	 #
//#Website: www.qjtechnologies.com     #
//######################################

#include<stdio.h>
#include<sys/socket.h>
#include<netdb.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>

#define DATA "Hello from client"

int main(int argc, char *argv[])
{
	int sock;
	struct sockaddr_in server;
	struct hostent *hp;
	char buffer[1024];
	
	//Defining a socket
	sock= socket(AF_INET, SOCK_STREAM, 0);
	if(sock<0)
	{
		perror("Socket Failed");
		close(sock);
		exit(1);
	}
	
	server.sin_family = AF_INET;
	
	//Accept command line argument as IP address
	hp = gethostbyname(argv[1]);
	if(hp==0)
	{
			perror("gethostbynme Failed");
			close(sock);
			exit(1);
	}
	
	memcpy(&server.sin_addr, hp->h_addr, hp->h_length);
	server.sin_port = htons(5000);
	
	//Connect to the server
	if(connect(sock, (struct sockaddr *) &server, sizeof(server))<0)
	{
		perror("connect failed");
		close(sock);
		exit(1);
	}
	
	//Send data to the server
	if(send(sock,DATA,sizeof(DATA), 0)<0)
	{
		perror("Send Failed");
		close(sock);
		exit(1);
	}
	printf("Sent %s\n",DATA);
	
	//Receive data from the server
	recv(sock, buffer, sizeof(buffer), 0);
	printf("Message: %s\n",buffer);
	
	close(sock);
	
	return 0;
}
