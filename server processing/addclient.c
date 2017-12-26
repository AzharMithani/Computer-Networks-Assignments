//############QJ Technologies###########
//#Author: Qaidjohar Jawadwala		 # 
//#Email: info@qjtechnologies.com 	 #
//#Website: www.qjtechnologies.com     #
//######################################


#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<netdb.h>




int main(int argc, char* argv[])
{
/*Variables*/
	int sock,num1,num2,result;
	char buffer[1024],buffer1[1024];
	struct hostent *host;
	struct sockaddr_in server;

	host = gethostbyname(argv[1]);
/*Socket*/
	sock = socket(AF_INET,SOCK_STREAM,0);
	if(sock == -1)
	{
		perror("Socket Failed");
		exit(1);
	}
	
	server.sin_family = AF_INET;
	server.sin_port = htons(5000);
	memcpy(&server.sin_addr,host->h_addr,host->h_length);
	
/*Connect*/
	
	if(connect(sock,(struct sockaddr *)&server,sizeof(server))<0)
	{
			perror("Connect Failed");
			exit(1);
	}

	//Number 1 input
	printf("Enter num1:");
	scanf("%d",&num1);
	//Number 2 input
	printf("Enter num2:");
	scanf("%d",&num2);
	
/*Send*/
	//Sending Number 1
	if(send(sock,&num1,sizeof(int),0)<0)
	{
		perror("send failed");
		exit(1);
	}
	//Sending Number 2
	if(send(sock,&num2,sizeof(int),0)<0)
	{
			perror("Send2 Failed");
			exit(1);
	}
	//Receiving the addition resule
	recv(sock,&result,sizeof(int),0);
	
	printf("Answer is : %d\n",result);
	return 0;
}
