// GameServer.cpp: 콘솔 응용 프로그램의 진입점을 정의합니다.
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <WinSock2.h>
void ErrorHandling(const char * message);


int main(int argc, char* argv[])
{
	WSADATA wsaData;
	SOCKET hServSock, hClientSock;
	SOCKADDR_IN servAddr, clientAddr;

	int szClientAddr;
	char message[] = "hello world!";
	if (argc != 2)
	{
		printf("Usage: %s <port>\n", argv[0]);
		exit(1);
	}

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		ErrorHandling("WSAStartup() error1");

	hServSock = socket(PF_INET, SOCK_STREAM, 0);
	if (hServSock == INVALID_SOCKET)
		ErrorHandling("socket() error1");

	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servAddr.sin_port = htons(atoi(argv[1]));

	if (bind(hServSock, (SOCKADDR*)&servAddr, sizeof(servAddr)) == SOCKET_ERROR)
		ErrorHandling("bind() error1");

	if (listen(hServSock, 5) == SOCKET_ERROR)
		ErrorHandling("listen() error1");
	printf("서버 시작");

	szClientAddr = sizeof(clientAddr);
	hClientSock = accept(hServSock, (SOCKADDR*)&clientAddr, &szClientAddr);
	if (hClientSock == INVALID_SOCKET)
		ErrorHandling("accept() error1");

	send(hClientSock, message, sizeof(message), 0);
	closesocket(hClientSock);
	closesocket(hServSock);
	WSACleanup();
	return 0;
}

void ErrorHandling(const char * message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}