//############QJ Technologies###########
//#Author: Qaidjohar Jawadwala		 # 
//#Email: info@qjtechnologies.com 	 #
//#Website: www.qjtechnologies.com     #
//######################################

#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<stdlib.h>
#include <arpa/inet.h>
#include<unistd.h>

int main(int argc, char* argv[])
{
	/*Variables*/
	int sock,csock;
	struct sockaddr_in server;
	struct sockaddr_in client;
	int sin_size,num1,num2,result;
	char buffer[1024],buffer1[1024];
	
	/*Socket*/
	if((sock = socket(AF_INET,SOCK_STREAM,0))<0)
	{
		perror("Failed to Create Socket");
		exit(1);
	}
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(5000);
	
	
	/*bind*/
	if(bind(sock, (struct sockaddr *)&server, sizeof(server)))
	{
		perror("Bind Failed");
		exit(1);
	}
	
	
	/*listen*/
	
	if(listen(sock,5) == -1)
	{
			perror("Listen failed");
			exit(1);
	}
	
	/*Accept*/
	while(1)
	{
		sin_size = sizeof(client);
		csock = accept(sock,(struct sockaddr *)&client, &sin_size); 
		if(csock == -1)
		{
				perror("Accept Failed");
		}
		 //printf("\n I got a connection");
		printf("Connetion Received from: %s:%d\n",inet_ntoa(client.sin_addr),ntohs(client.sin_port));
		
		//Receive Number 1
		if(recv(csock,&num1,sizeof(int),0)<0)
		{
			perror("Receive 1 Fialed");
			exit(1);
		}
		printf("Num1:%d\n",num1);
		//Receive Number 2
		if(recv(csock,&num2,sizeof(int),0)<0)
		{
			perror("Receive 2 Fialed");
			exit(1);
		}
		printf("Num2:%d\n",num2);
		
		//Perform Addition and store in result
		result = num1+num2;
		printf("Result:%d\n",result);
		//Send result to the server
		if(send(csock,&result,sizeof(int),0)<0)
		{
			perror("Send Failed");
			exit(1);
		}
		
	/*Close*/
		close(csock);
	}
	
	

return 0;
}
