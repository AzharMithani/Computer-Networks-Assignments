#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<netdb.h>
#include<unistd.h>

int main()
{
	FILE *fp;
	int sock,pt,cnt=0;
	char filename[1024],buf_recv[1024],buf_send[1024];
	struct sockaddr_in server,client;
	int slen = sizeof(client);
	
	sock = socket(AF_INET,SOCK_DGRAM,0);
	if(sock == -1)
	{
		perror("Socket Error");
		exit(1);
	}
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(8888);
	
	if(bind(sock, (struct sockaddr *)&server, sizeof(server)) == -1)
	{
		perror("Bind Error");
		exit(1);
	}
	
	while(1)
	{
		cnt=0;
		fflush(stdout);
		pt = recvfrom(sock, filename, sizeof(filename), 0, (struct sockaddr *)&client, &slen);
		printf("%s",filename);
		
		strcat(filename,"1");
		fp=fopen(filename, "wb");
		strcpy(buf_recv,"random");
		while(strcmp(buf_recv,"end") != 0)
		{
			pt = recvfrom(sock, buf_recv, sizeof(buf_recv), 0, (struct sockaddr *)&client, &slen);
			
			fwrite(buf_recv, sizeof(buf_recv), 1, fp);
			printf("Received:%d\n",cnt);
			cnt++;
		}
		fclose(fp);
		printf("File Received Successfully\n");	
	}
}
