#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>


#define BUF_SIZE 30

void ErrorHandling(char* message);
int main(int argc, char* argv[])
{
	int sd;
	FILE* fp;

	char buf[BUF_SIZE];
	char file_name[BUF_SIZE];
	int read_cnt;
	struct sockaddr_in serv_adr;

	WSADATA wsaData;
	
	if (argc != 3) {
		printf("Usage : %s <IP> <port>\n", argv[0]);
		exit(1);
	}

	if (WSAStartup(MAKEWORD(2,2),&wsaData)!=0)
	{
		ErrorHandling((char*)"WSAStartup() error!");
	}

	printf("Input file name: ");
	scanf("%s", file_name);
	fp = fopen(file_name, "wb", 0);

	sd = socket(PF_INET, SOCK_STREAM, 0);
	if (sd == -1)
		ErrorHandling("socket() error");

	memset(&serv_adr, 0, sizeof(serv_adr));
	serv_adr.sin_family = AF_INET;
	serv_adr.sin_addr.s_addr = inet_addr(argv[1]);
	serv_adr.sin_port = htons(atoi(argv[2]));

	if (connect(sd, (struct sockaddr*) & serv_adr, sizeof(serv_adr)) == -1)
		ErrorHandling("connect() error!");

	send(sd, file_name, strlen(file_name) + 1,0);

	while ((read_cnt = recv(sd, buf, BUF_SIZE,0)) != 0)	
		fwrite((void*)buf, 1, read_cnt, fp);

	fclose(fp);
	closesocket(sd);
	WSACleanup();
	return 0;
}

void ErrorHandling(char* message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}

