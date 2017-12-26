#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<netdb.h>
#include<unistd.h>

int exists(const char *fname)
{
    FILE *file;
    if(file = fopen(fname, "r"))
    {
        fclose(file);
        return 1;
    }
    return 0;
}

int main(int argc, char* argv[])
{
	FILE *fp;
	int sock,pt;
	char filename[1024],buf_recv[1024],buf_send[1024];
	struct sockaddr_in server;
	struct hostent *host;
	int slen = sizeof(server);
	
	host = gethostbyname(argv[1]);
	
	sock = socket(AF_INET,SOCK_DGRAM,0);
	if(sock == -1)
	{
		perror("Socket Error");
		exit(1);
	}
	server.sin_family = AF_INET;
	server.sin_port = htons(8888);
	memcpy(&server.sin_addr,host->h_addr,host->h_length);
	
	printf("Enter Filename: ");
	scanf("%s",filename);
	if(exists(filename))
	{
		sendto(sock, filename, sizeof(filename), 0, (struct sockaddr *)&server, slen);
		fp=fopen(filename, "rb");
		usleep(100000);
		while (fread(buf_send, sizeof(buf_send), 1, fp) == 1) 
		{
			sendto(sock, buf_send, sizeof(buf_send), 0, (struct sockaddr *)&server, slen);
			usleep(1000);
		}
		usleep(100000);
		if (feof(fp))
		{
		    sendto(sock, buf_send, sizeof(buf_send), 0, (struct sockaddr *)&server, slen);
			strcpy(buf_send,"end");
			sendto(sock, buf_send, sizeof(buf_send), 0, (struct sockaddr *)&server, slen);
		    printf("File written successfully\n");
		}
		else
		{
			printf("File not read/written successfully\n");
		}
		fclose(fp);
		
	}
	else
	{
		printf("File Doesn't Exist\n");
	}
	
}

