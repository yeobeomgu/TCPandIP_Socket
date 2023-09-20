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

	SOCKET ServerSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	SOCKADDR_IN ServerSockAddr;
	memset(&ServerSockAddr, 0, sizeof(ServerSocket));
	ServerSockAddr.sin_family = PF_INET;
	ServerSockAddr.sin_port = htons(7777);
	inet_pton(AF_INET, "127.0.0.1", &ServerSockAddr.sin_addr.s_addr);

	connect(ServerSocket, (SOCKADDR*)&ServerSockAddr, sizeof(ServerSockAddr));

	FILE* ReadFile = nullptr;
	ReadFile = fopen("육전.jpg", "rb");

	char Buffer[1024] = { 0, };
	size_t ReadSize = 0;

	do
	{
		ReadSize = fread(Buffer, sizeof(char), sizeof(Buffer), ReadFile);
		size_t WriteSize = send(ServerSocket, Buffer, (int)ReadSize, 0);
	} while (ReadSize > 0);

	//fseek(ReadFile, 0, SEEK_SET);

	//do
	//{
	//	ReadSize = fread(Buffer, sizeof(char), sizeof(Buffer), ReadFile);
	//	size_t WriteSize = send(ServerSocket, Buffer, (int)ReadSize, 0);
	//} while (ReadSize > 0);

	fclose(ReadFile);

	closesocket(ServerSocket);

	WSACleanup();
	return 0;
}