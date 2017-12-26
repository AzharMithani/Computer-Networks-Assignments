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
#include <string.h>

int main(int argc, char* argv[])
{
/*Variables*/
	int sock,cnt=0;
	char buffer[1024],filedata[1024],filename[1024];
	struct hostent *host;
	struct sockaddr_in server;
	FILE *fp;

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
	
	printf("Enter Filename:");
	scanf("%s",filename);
	
	//Send the filename of the file to receive
	if(send(sock,filename,sizeof(filename),0)<0)
	{
			perror("Send Failed");
			exit(1);
	}
	//Receive the file status. True if file exists else False
	if(recv(sock,buffer,sizeof(buffer),0)<0)
	{
			perror("Receive Failed");
			exit(1);
	}
	printf("\nFile status Received: %s\n",buffer);
	
	//Checking if received value is True i.e. File exists
	if (strcmp(buffer,"True") == 0)
	{
			printf("File Exists.\n");
			strcat(filename,"1");
			
			//Creating the file
			fp=fopen(filename, "wb");
			
			//Initialize filedata with some random value
			strcpy(filedata,"random");
			
			//Receiving file data in packets till end of file
			while(strcmp(filedata,"end") != 0)
			{
				//Receiving File Data
				if(recv(sock,filedata,sizeof(filedata),0)<0)
				{
						perror("Receive Failed");
						exit(1);
				}
				//Writing received data into a file
				fwrite(filedata, sizeof(filedata), 1, fp);
				printf("Received:%d\n",cnt);
				cnt++;
			}
			fclose(fp);	 
    }  
	else
      printf("File Doesn't Exist.\n");
	return 0;
}
