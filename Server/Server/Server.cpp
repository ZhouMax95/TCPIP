#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>

#define BUF_SIZE 30
void ErrorHandling(char* message);

int main(int argc, char* argv[])
{
	WSADATA wsaData;
	int serv_sd, clnt_sd;
	FILE* fp;
	char buf[BUF_SIZE];
	char file_name[BUF_SIZE];
	int read_cnt;

	struct sockaddr_in serv_adr, clnt_adr;
	int clnt_adr_sz;

	if (argc != 2) {
		printf("Usage: %s <port>\n", argv[0]);
		exit(1);
	}

	if (WSAStartup(MAKEWORD(2,2),&wsaData)!=0)
	{
		ErrorHandling((char*)"WSAStartup() error!");
	}

	serv_sd = socket(PF_INET, SOCK_STREAM, 0);

	memset(&serv_adr, 0, sizeof(serv_adr));
	serv_adr.sin_family = AF_INET;
	serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_adr.sin_port = htons(atoi(argv[1]));

	bind(serv_sd, (struct sockaddr*) & serv_adr, sizeof(serv_adr));
	listen(serv_sd, 1);

	clnt_adr_sz = sizeof(clnt_adr);
	clnt_sd = accept(serv_sd, (struct sockaddr*) & clnt_adr, &clnt_adr_sz);

	recv(clnt_sd, file_name, BUF_SIZE,0);
	fopen_s(&fp,file_name, "rb");
	if (fp != NULL) 
	{
		while (1)
		{
			read_cnt = fread((void*)buf, 1, BUF_SIZE, fp);
			if (read_cnt < BUF_SIZE)
			{
				send(clnt_sd, buf, read_cnt,0);
				break;
			}
			send(clnt_sd, buf, BUF_SIZE,0);
		}
	}

	fclose(fp);
	closesocket(clnt_sd); 
	closesocket(serv_sd);
	WSACleanup();
	return 0;
}

void ErrorHandling(char* message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
