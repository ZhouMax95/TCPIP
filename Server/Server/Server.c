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

///* 第12章 */
//
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include <winsock2.h>
//
//#define BUF_SIZE 1024
//
//void ErrorHandling(char* message);
//
//int main(int argc, char* argv[]) {
//	WSADATA wsaData;
//	SOCKET hServSock, hClntSock;
//	SOCKADDR_IN servAdr, clntAdr;
//	TIMEVAL timeout;
//	fd_set reads, cpyReads;
//
//	int adrSz;
//	int strLen, fdNum, i;
//	char buf[BUF_SIZE];
//
//	
//	if (argc!=2)
//	{
//		printf("Usage: %s <port>\n", argv[0]);
//		exit(1);
//	}
//
//	if (WSAStartup(MAKEWORD(2,2),&wsaData)!=0)
//	{
//		ErrorHandling("WSAStartup() error!");
//	}
//	
//	hServSock = socket(PF_INET, SOCK_STREAM, 0);
//	memset(&servAdr, 0, sizeof(servAdr));
//	servAdr.sin_family = AF_INET;
//	servAdr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);	
//	servAdr.sin_port = htons(atoi(argv[1]));
//	
//	
//	if (bind(hServSock,(SOCKADDR*)&servAdr,sizeof(servAdr))== SOCKET_ERROR)
//	{
//		ErrorHandling("bind() error");
//	}
//
//	if (listen(hServSock,5)==SOCKET_ERROR)
//	{
//		ErrorHandling("listen() error");
//	}
//
//	FD_ZERO(&reads);
//	FD_SET(hServSock, &reads);
//
//	while (1)
//	{
//		cpyReads = reads;
//
//		timeout.tv_sec = 5;
//		timeout.tv_usec = 5000;
//
//		if ((fdNum=select(0,&cpyReads,0,0,&timeout))== SOCKET_ERROR)
//		{
//			
//			break;
//		}
//
//		if (fdNum==0)
//		{
//			
//			continue;
//		}
//		
//		for (i = 0; i < reads.fd_count; i++) {
//			if (FD_ISSET(reads.fd_array[i],&cpyReads))
//			{
//				if (reads.fd_array[i]==hServSock)
//				{
//					adrSz = sizeof(clntAdr);
//					hClntSock = accept(hServSock, (SOCKADDR*)&clntAdr, &adrSz);
//					FD_SET(hClntSock, &reads);
//					printf("connected clinet: %d \n,hClntSock");
//				}
//				else
//				{
//					strLen = recv(reads.fd_array[i], buf, BUF_SIZE - 1, 0);
//					if (strLen == 0)
//					{
//						FD_CLR(reads.fd_array[i], &reads);
//						closesocket(cpyReads.fd_array[i]);
//						printf("closed client: %d \n", cpyReads.fd_array[i]);
//					}
//					else
//					{
//						send(reads.fd_array[i], buf, strLen, 0);
//					}
//				}
//				
//			}
//		}
//
//
//	}
//	closesocket(hServSock);
//	WSACleanup();	
//	return 0;
//
//}
//
//void ErrorHandling(char* message) {
//	fputs(message, stderr);
//	fputc("\n", stderr);
//	exit(1);
//}

///* 第14章 */
//
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include <winsock2.h>
//#include <ws2tcpip.h>
//
//#define TTL 64
//#define BUF_SIZE 30
//void ErrorHandling(char* message);
//
//int main(int argc, char* argv[]) {
//	WSADATA wsaData;
//	SOCKET hSendSock;
//	SOCKADDR_IN mulAdr;
//	int timeLive=TTL;
//	FILE* fp;
//	char buf[BUF_SIZE];
//
//	if (argc!=3)
//	{
//		printf("argc not right!");
//		exit(1);
//	}
//
//	if (WSAStartup(MAKEWORD(2,2),&wsaData)!=0)
//	{
//		printf("WSAStartup error!");
//		exit(1);
//	}
//
//	hSendSock = socket(PF_INET, SOCK_DGRAM, 0);
//	memset(&mulAdr, 0, sizeof(mulAdr));
//	mulAdr.sin_family = AF_INET;
//	mulAdr.sin_addr.S_un.S_addr = inet_addr(argv[1]);
//	mulAdr.sin_port = htons(atoi(argv[2]));
//
//	setsockopt(hSendSock, IPPROTO_IP, IP_MULTICAST_TTL, (void*)&timeLive, sizeof(timeLive));
//	
//	if ((fp=fopen("new.txt","r"))==NULL)
//	{
//		printf("fopen error");
//	}
//
//	while (!feof(fp))
//	{
//		fgets(buf, BUF_SIZE, fp);
//		sendto(hSendSock, buf, strlen(buf), 0, (SOCKADDR*)&mulAdr, sizeof(mulAdr));
//		Sleep(2000);
//	}
//	closesocket(hSendSock);
//	WSACleanup();
//	return 0;
//
//}

/* 第15章 */

/*  */
//#include <stdlib.h>
//#include <stdio.h>
//#include <winsock2.h>
//#include <string.h>
//
//#define BUF_SIZE 1024
//
//int main(int argc, char* argv[]) {
//	WSADATA wsaData;
//	char message[BUF_SIZE];
//	FILE* readfp;
//	FILE* writefp;
//	SOCKET sevr_sock;
//    SOCKET clnt_sock;
//	SOCKADDR_IN serv_adr;
//	SOCKADDR_IN clnt_adr;
//	int clnt_adr_size;
//
//	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
//		printf("WSAStartup() error!");
//
//	if (argc != 2)
//		printf("start para error!");
//
//	sevr_sock = socket(PF_INET, SOCK_STREAM, 0);
//	if (sevr_sock == -1)
//		printf("serv_sock init error!");
//		
//	memset(&serv_adr, 0, sizeof(serv_adr));
//	serv_adr.sin_family = AF_INET;
//	serv_adr.sin_addr.S_un.S_addr = htonl(INADDR_ANY); 
//	serv_adr.sin_port = htons(atoi(argv[1]));
//	                                     
//	if (bind(sevr_sock, (SOCKADDR*) & serv_adr, sizeof(serv_adr)) == -1)
//		printf("bind() error!");
//
//	if (listen(sevr_sock, 5) == -1)
//		printf("listen error!");
//	clnt_adr_size = sizeof(clnt_adr);
//	for (size_t i = 0; i < 5; i++)
//	{
//		clnt_sock = accept(sevr_sock, (SOCKADDR*) &clnt_adr, &clnt_adr_size);
//		if (clnt_sock == -1)
//			printf("accept() error!");
//		else 
//			printf("Connecte client %d \n", i + 1);		
//
//		readfp = fopen(clnt_sock, "r");
//		writefp = fopen(clnt_sock, "w");
//		while (!feof(readfp))
//		{
//			fgets(message, BUF_SIZE, readfp);
//			fputs(message, writefp);
//			fflush(writefp);
//		}
//		fclose(readfp);
//		fclose(writefp);
//	}
//	close(sevr_sock);
//	return 0;
//}

/* 第19章 */

#include <stdio.h>
#include <windows.h>
#include <process.h>
unsigned WINAPI ThreadFunc(void* arg);

int main(int argc, char* argv[]) {
	HANDLE hThread;
	unsigned threadID;
	int param = 5;

	hThread = (HANDLE)_beginthreadex(NULL, 0, ThreadFunc, (void*)&param, 0, &threadID);
	if (hThread==0)
	{
		puts("_beginThreadex() error");
		return -1;
	}

	Sleep(3000);
	puts("end of main");
	return 0;
}

unsigned WINAPI ThreadFunc(void *arg) {
	int i;
	int cnt = *((int*)arg);
	for (size_t i = 0; i < cnt; i++)
	{
		Sleep(1000); 
		puts("running thread");
	}
	return 0;
}



