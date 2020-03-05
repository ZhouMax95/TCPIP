//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include <winsock2.h>
//
//#define BUF_SIZE 30
//void ErrorHandling(char *message);
//
//int main(int argc, char* argv[]) {
//	WSADATA wsaData;
//	SOCKET hServSock, hClntSock;
//	FILE* fp;
//	char buf[BUF_SIZE];
//	int readCnt;
//
//	SOCKADDR_IN servAdr, clntAdr;
//	int clntAdrSz;
//	if (argc!=2)
//	{
//		printf("Usage:%s <port>\n", argv[0]);
//		exit(1);
//	}
//
//	if (WSAStartup(MAKEWORD(2,2),&wsaData)!=0)
//	{
//		ErrorHandling((char*)"WSAStartup() error");
//	}
//
//	fp = fopen("t.txt", "rb");
//	hServSock = socket(PF_INET, SOCK_STREAM, 0);
//
//	memset(&servAdr, 0, sizeof(servAdr));
//	servAdr.sin_family = AF_INET;
//	servAdr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
//	servAdr.sin_port = htons(atoi(argv[1]));
//
//	bind(hServSock, (SOCKADDR*)&servAdr,sizeof(servAdr));
//	listen(hServSock, 5);
//
//	clntAdrSz = sizeof(clntAdr);
//	hClntSock = accept(hServSock, (SOCKADDR*)&clntAdr, &clntAdrSz);
//
//	while (1)
//	{
//		readCnt = fread((void*)buf, 1, BUF_SIZE, fp);
//		if (readCnt<BUF_SIZE)
//		{
//			send(hClntSock, (char*)&buf, readCnt, 0);
//			break;
//		}
//		send(hClntSock, (char*)&buf, BUF_SIZE, 0);
//	}
//
//	shutdown(hClntSock, SD_SEND);
//	recv(hClntSock, (char*)buf, BUF_SIZE, 0);
//	printf("Message from client:%s \n", buf);
//
//	fclose(fp);
//	closesocket(hClntSock);
//	closesocket(hServSock);
//	WSACleanup();
//	return 0;
//}
//
//void ErrorHandling(char* message) {
//	fputs(message, stderr);
//	fputc('\n', stderr);
//	exit(1);
//}

//#include <stdio.h>
//#include <stdlib.h>
//#include <winsock2.h>
//
//void ErrorHandling(char* message);
//void ShowSocketBufSize(SOCKET sock);
//
//int main(int argc, char* argv[]) {
//	WSADATA wsaData;
//	SOCKET hSock;
//	int sndBuf, rcvBuf, state;
//	if (WSAStartup(MAKEWORD(2,2),&wsaData)!=0)
//	{
//		ErrorHandling("WSAStartup() error!");
//	}
//
//	hSock = socket(PF_INET, SOCK_STREAM, 0);
//	ShowSocketBufSize(hSock);
//
//	sndBuf = 1024 * 3, rcvBuf = 1024 * 3;
//	state = setsockopt(hSock, SOL_SOCKET, SO_SNDBUF, (char*)&sndBuf, sizeof(sndBuf));
//	if (state==SOCKET_ERROR)
//	{
//		ErrorHandling("setsocket() error!");
//	}
//
//	state = setsockopt(hSock, SOL_SOCKET, SO_RCVBUF, (char*)&rcvBuf, sizeof(rcvBuf));
//	if (state==SOCKET_ERROR)
//	{
//		ErrorHandling("setsocket() error!");
//	}
//
//	ShowSocketBufSize(hSock);
//	closesocket(hSock);
//	WSACleanup();
//	return 0;
//}
//
//void ShowSocketBufSize(SOCKET sock) {
//	int sndBuf, rcvBuf, state, len;
//
//	len = sizeof(sndBuf);
//	state = getsockopt(sock, SOL_SOCKET, SO_SNDBUF, (char*)&sndBuf, &len);
//	if (state==SOCKET_ERROR)
//	{
//		ErrorHandling("getsockopt() error");
//	}
//
//	len = sizeof(rcvBuf);
//	state = getsockopt(sock, SOL_SOCKET, SO_RCVBUF, (char*)&rcvBuf, &len);
//	if (state==SOCKET_ERROR)
//	{
//		ErrorHandling("getsockopt() error");
//	}
//	printf("Input buffer size:%d \n", rcvBuf);
//	printf("Output buffer size:%d \n", sndBuf);
//
//}
//
//void ErrorHandling(char* message) {
//	fputs(message, stderr);
//	fputc('\n', stderr);
//	exit(1);
//}

/* 第12章 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>

#define BUF_SIZE 1024

void ErrorHandling(char* message);

int main(int argc, char* argv) {
	WSADATA wsaData;
	SOCKET hServSock, hClntSock;
	SOCKADDR_IN servAdr, clntAdr;
	TIMEVAL timeout;
	fd_set reads, cpyReads;

	int adrSz;
	int strLen, fdNum, i;
	char buf[BUF_SIZE];

	printf("开始");

	if (argc!=2)
	{
		printf("Usage: %s <port>\n", argv[0]);
		exit(1);
	}

	if (WSAStartup(MAKEWORD(2,2),&wsaData)!=0)
	{
		ErrorHandling("WSAStartup() error!");
	}
	
	hServSock = socket(PF_INET, SOCK_STREAM, 0);
	
	memset(&servAdr, 0, sizeof(servAdr));
	servAdr.sin_family = AF_INET;
	
	servAdr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	
	servAdr.sin_port = htons(atoi(argv[1]));
	printf("到这");
	
	if (bind(hServSock,(SOCKADDR*)&servAdr,sizeof(servAdr))== SOCKET_ERROR)
	{
		ErrorHandling("bind() error");
	}

	if (listen(hServSock,5)==SOCKET_ERROR)
	{
		ErrorHandling("listen() error");
	}

	FD_ZERO(&reads);
	FD_SET(hServSock, &reads);

	while (1)
	{
		cpyReads = reads;
		timeout.tv_sec = 5;
		timeout.tv_usec = 5000;

		if ((fdNum=select(0,&cpyReads,0,0,&timeout))== SOCKET_ERROR)
		{
			printf("停止循环");
			break;
		}

		if (fdNum==0)
		{
			printf("跳过");
			continue;
		}
		
		for (i = 0; i < reads.fd_count; i++) {
			if (FD_ISSET(reads.fd_array[i],&cpyReads))
			{
				if (reads.fd_array[i]==hServSock)
				{
					adrSz = sizeof(clntAdr);
					hClntSock = accept(hServSock, (SOCKADDR*)&clntAdr, &adrSz);
					FD_SET(hClntSock, &reads);
					printf("connected clinet: %d \n,hClntSock");
				}
				else
				{
					strLen = recv(reads.fd_array[i], buf, BUF_SIZE - 1, 0);
					if (strLen == 0)
					{
						FD_CLR(reads.fd_array[i], &reads);
						closesocket(cpyReads.fd_array[i]);
						printf("closed client: %d \n", cpyReads.fd_array[i]);
					}
					else
					{
						send(reads.fd_array[i], buf, strLen, 0);
					}

				}
				
			}
		}


	}
	closesocket(hServSock);
	WSACleanup();
	printf("结束");
	return 0;

}



void ErrorHandling(char* message) {
	fputs(message, stderr);
	fputc("\n", stderr);
	exit(1);
}