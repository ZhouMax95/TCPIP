#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>


void ErrorHandling(char* message);

int main(int argc, char* argv[]) {
	
	/*unsigned short host_port = 0x1234;
	unsigned short net_port;
	unsigned long host_addr = 0x12345678;
	unsigned long net_addr;
	net_port = htons(host_port);
	net_addr = htonl(host_addr);

	printf("Host ordered port : %#x\n", host_port);
	printf("Network ordered port:%#x\n", net_port);
	printf("Host ordered address:%#lx \n", host_addr);
	printf("Network ordered address:%#lx \n", net_addr);
	return 0;*/
	
	/*char* addr1 = "1.2.3.4";
	char* addr2 = "1.2.3.256";

	unsigned long conv_addr = inet_addr(addr1);
	if (conv_addr==INADDR_NONE)
	{
		printf("Error occured! \n");
	}
	else
	{
		printf("Network ordered integer addr : %#1x \n", conv_addr);
	}

	conv_addr = inet_addr(addr2);
	if (conv_addr==INADDR_NONE)
	{
		printf("Error occureded \n");
	}
	else
	{
		printf("Network ordered integer addr:%#lx \n\n", conv_addr);
	}
			*/

	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2,2),&wsaData)!=0)
	{
		ErrorHandling("WSAStartup() error!");
	}

	{
		char* addr = "127.212.124.78";
		unsigned long conv_addr = inet_addr(addr);

		if (conv_addr == INADDR_NONE)
		{
			printf("Error occured! \n");
		}
		else
		{
			printf("Network ordered integer addr: %#lx \n", conv_addr);
		}
	}

	{
		struct sockaddr_in addr;
		char* strPtr;
		char strArr[20];

		addr.sin_addr.S_un.S_addr = htonl(0x1020304);
		strPtr = inet_ntoa(addr.sin_addr);
		strcpy(strArr, strPtr);
		printf("Dotted-Decimal notation3 %s \n", strArr);
		printf("Dotted-Decimal notation3 %s \n", strPtr);

		addr.sin_addr.S_un.S_addr = htonl(0x7fd47c4e);
		inet_ntoa(addr.sin_addr);
		printf("Dotted-Decimal notation3 %s \n", strPtr);
		WSACleanup();
		return 0;
	}

}

//int main(int argc, char* argv[]) {
//	WSADATA wsaData;
//	SOCKET hServSock, hClntSock;
//	SOCKADDR_IN servAddr, clntAddr;
//	int sentidex = 0, strLen = 0;
//	int idex = 0, readlen = 0;
//
//	int szClntAddr;
//	char message[] = "I am here";
//	if (argc!=2)
//	{
//		printf("Usage:%s<port>\n", argv[0]);
//		exit(1);
//	}
//
//	if (WSAStartup(MAKEWORD(2,2),&wsaData)!=0)
//	{
//		ErrorHandling("WSAStartup() error!");
//	}
//
//	hServSock = socket(PF_INET, SOCK_STREAM, 0);
//	if (hServSock==INVALID_SOCKET)
//	{
//		ErrorHandling("socket() error");
//	}
//
//	memset(&servAddr, 0, sizeof(servAddr));		
//	servAddr.sin_family = AF_INET;
//	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
//	servAddr.sin_port = htons(atoi(argv[1]));	
//
//	if (bind(hServSock,(SOCKADDR*)&servAddr,sizeof(servAddr))==SOCKET_ERROR)
//	{
//		ErrorHandling("bind() error");
//	}
//
//	if (listen(hServSock,5)==SOCKET_ERROR)
//	{
//		ErrorHandling("listen() error");
//	}
//
//	szClntAddr = sizeof(clntAddr);
//	hClntSock = accept(hServSock, (SOCKADDR*)& clntAddr, &szClntAddr);
//	if (hClntSock==INVALID_SOCKET)
//	{
//		ErrorHandling("accept() error");
//	}
//
//
//	send(hClntSock, message, sizeof(message), 0);
//	/*for (size_t i = 0; i < strlen(message); i++)
//	{
//		send(hClntSock, &message[i], sizeof(message[i]), 0);
//		strLen += i;
//		printf("sending %c\n", message[i]);
//	}*/
//
//	printf("function read call count: %d \n", strLen);
//
//	closesocket(hClntSock);
//	closesocket(hServSock);
//	WSACleanup();
//	return 0;
//}

void ErrorHandling(char* message) {
	fputs(message, stderr);
	fputc("\n", stderr);
	exit(1);
}