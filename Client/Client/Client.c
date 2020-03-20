//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include <winsock2.h>
//
//#define BUF_SIZE 1024
//void ErrorHandling(char* message);
//
//int main(int argc, char* argv[]) {
//	WSADATA wsaData;
//	SOCKET hSocket;
//	char message[BUF_SIZE];
//	int strLen;
//	SOCKADDR_IN servAdr;
//
//	if (argc!=3)
//	{
//		printf("Usage : %s<IP><Port>\n", argv[0]);
//		exit(1);
//	}
//
//	if (WSAStartup(MAKEWORD(2,2),&wsaData)!=0)
//	{
//		ErrorHandling("WSAStartup() error!");
//	}
//
//	hSocket = socket(PF_INET, SOCK_STREAM, 0);
//	memset(&servAdr, 0, sizeof(servAdr));
//	servAdr.sin_family = AF_INET;
//	servAdr.sin_addr.S_un.S_addr = inet_addr(argv[1]);
//	servAdr.sin_port = htons(atoi(argv[2]));
//
//	if (connect(hSocket, (SOCKADDR*)&servAdr, sizeof(servAdr))==-1)
//	{
//		ErrorHandling("connect() error!");
//	}
//	else
//	{
//		puts("Connected....");
//	}
//
//	while (1) {
//		fputs("Input message(Q to quit):", stdout);
//		fgets(message, BUF_SIZE, stdin);
//
//		if (!strcmp(message,"q\n")||!(strcmp(message,"Q\n")))
//		{
//			break;
//		}
//
//		send(hSocket, message, strlen(message), 0);
//		strLen = recv(hSocket, message, BUF_SIZE - 1, 0);
//		message[strLen] = 0;
//		printf("Message from server: %s", message);
//		
//
//	}
//
//	
//	closesocket(hSocket);
//	WSACleanup();
//	return 0;
//}
//
//void ErrorHandling(char* message) {
//	fputs(message, stderr);
//	fputc('\n', stderr);
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
//#define BUF_SIZE 30
//
//int main(int argc,char* argv[])
//{
//	WSADATA wsaData;
//	SOCKET hRecvSock;
//	SOCKADDR_IN adr;
//	struct ip_mreq joinAdr;
//	char buf[BUF_SIZE];
//	int strLen;
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
//	}
//
//	hRecvSock = socket(PF_INET, SOCK_DGRAM, 0);
//	memset(&adr, 0, sizeof(adr));
//	adr.sin_family = AF_INET;
//	adr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
//	adr.sin_port = htons(atoi(argv[2]));
//	if (bind(hRecvSock,(SOCKADDR*)&adr,sizeof(adr))==SOCKET_ERROR)
//	{
//		printf("Bind() error!");
//	}
//
//	joinAdr.imr_multiaddr.S_un.S_addr = inet_addr(argv[1]);
//	joinAdr.imr_interface.S_un.S_addr = htonl(INADDR_ANY);
//	if (setsockopt(hRecvSock,IPPROTO_IP,IP_ADD_MEMBERSHIP,(void*)&joinAdr,sizeof(joinAdr))==SOCKET_ERROR)
//	{
//		printf("setsock() error!");
//	}
//
//	while (1)
//	{
//		strLen = recvfrom(hRecvSock, buf, BUF_SIZE - 1, 0, NULL, 0);
//		if (strLen<0)
//		{
//			break;
//		}
//
//		buf[strLen] = 0;
//		fputs(buf, stdout);
//
//	}
//	closesocket(hRecvSock);
//	WSACleanup();
//	return 0;
//}

///* 第15章 */
//
//#include <stdlib.h>
//#include <stdio.h>
//#include <string.h>
//#include <winsock2.h>
//#include <WS2tcpip.h>
//
//#define BUF_SIZE 1024
//
//int main(int argc, char* argv[]) {
//	WSADATA wsaData;
//	SOCKET sock;
//	char message[BUF_SIZE];
//	SOCKADDR_IN serv_adr;
//	FILE* readfp;
//	FILE* writefp;
//
//	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
//		printf("WSAStartup() error!");
//
//	if (argc != 3)
//		printf("start input error!");
//
//	sock = socket(PF_INET, SOCK_STREAM, 0);
//	if (sock == -1)
//		printf("sock init error!");
//	memset(&serv_adr, 0, sizeof(serv_adr));
//	serv_adr.sin_family = AF_INET;
//	inet_pton(AF_INET, "127.0.0.1", (void*)&serv_adr.sin_addr.S_un.S_addr);
//	serv_adr.sin_addr.S_un.S_addr = inet_addr(argv[1]);
//	
//	serv_adr.sin_port = htons(atoi(argv[2]));
//
//	if (connect(sock, (SOCKADDR*) &serv_adr, sizeof(serv_adr)) == SOCKET_ERROR)
//		printf("connect() error!");
//	else
//		printf("Connected.......");
//
//	
//	readfp = fopen(sock, "r");
//	writefp = fopen(sock, "w");
//
//	while (1)
//	{
//		fputs("input message(Q to quit):", stdout);
//		fgets(message, BUF_SIZE, stdin);
//		if (!strcmp(message, "q\n") || !strcmp(message, "Q\n"))
//			break;
//
//		fputs(message, writefp);
//		fflush(writefp);
//		fgets(message, BUF_SIZE, readfp);
//		printf("Message from server:%s", message);
//	}
//	if (writefp!=NULL)
//	{
//		fclose(writefp);
//	}
//	if (readfp != NULL)
//	{
//		fclose(readfp);
//	}
//	
//	return 0;
//
//}

