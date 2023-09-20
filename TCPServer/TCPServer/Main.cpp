#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32")

using namespace std;

int main()
{
	WSAData wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	SOCKET ListenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	SOCKADDR_IN ListenSock;
	memset(&ListenSock, 0, sizeof(ListenSocket));
	ListenSock.sin_family = PF_INET;
	ListenSock.sin_port = htons(7777);
	ListenSock.sin_addr.s_addr = INADDR_ANY;
	bind(ListenSocket, (SOCKADDR*)&ListenSock, sizeof(ListenSock));
	listen(ListenSocket, SOMAXCONN);

	SOCKADDR_IN ClientSock;
	ZeroMemory(&ClientSock, sizeof(ClientSock));
	int ClientSockLength = sizeof(ClientSock);

	SOCKET ClientSocket = accept(ListenSocket, (SOCKADDR*)&ClientSock, &ClientSockLength);


	FILE* WriteFile = nullptr;
	WriteFile = fopen("육전.jpg", "wb");

	char Buffer[1] = { 0, };
	size_t RecvSize = 0;

	do
	{
		RecvSize = recv(ClientSocket, Buffer, sizeof(Buffer), 0);
		size_t WriteSize = fwrite(Buffer, sizeof(char), RecvSize, WriteFile);
	} while (RecvSize > 0);

	fclose(WriteFile);

	closesocket(ClientSocket);
	closesocket(ListenSocket);

	WSACleanup();

	return 0;
}