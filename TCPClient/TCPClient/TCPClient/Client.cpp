
// 컴파일러에 경고 메시지를 표시하지 않도록 지시하는 프리프로세서 디렉티브
#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <iostream>

using namespace std;



#include <WinSock2.h>

#pragma comment(lib, "ws2_32")

int main()
{
	//Windows 소켓 라이브러리를 초기화하는 부분.
	WSAData wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	//클라이언트 소켓을 생성
	SOCKET ServerSocket = socket(PF_INET, SOCK_STREAM, 0);

	//서버 소켓의 주소 정보를 저장하는 구조체
	SOCKADDR_IN ServerSock;
	ZeroMemory(&ServerSock, 0);

	ServerSock.sin_family = AF_INET;
	ServerSock.sin_addr.s_addr = inet_addr("172.16.2.186");
	ServerSock.sin_port = htons(7777);

	// 서버에 연결을 시도, 연결 결과를 Reult에 저장
	int Result = connect(ServerSocket, (SOCKADDR*)&ServerSock, sizeof(ServerSock));
	if (Result == SOCKET_ERROR)
	{
		cout << "connect Error" << endl;
		cout << "Socket Error Number : " << GetLastError() << endl;
		exit(-1);
	}

	//서버로 부터 수신한ㄷ ㅔ이터를 저장하기 위한 Buffer
	char Buffer[1024] = { 0, };

	//서버로부터 데이터를 수신
	int RecvByte = recv(ServerSocket, Buffer, sizeof(Buffer), 0);
	if (RecvByte <= 0)
	{
		cout << "recv Error" << endl;
		cout << "Socket Error Number : " << GetLastError() << endl;
		exit(-1);
	}

	cout << "Recv : " << Buffer << endl;

	char Message[1024] = { 0, };
	sprintf(Message, "%s Hellow", Buffer);

	int SendByte = send(ServerSocket, Message, (int)strlen(Message), 0);
	if (SendByte <= 0)
	{
		cout << "send Error" << endl;
		cout << "Socket Error Number : " << GetLastError() << endl;
		exit(-1);
	}

	closesocket(ServerSocket);

	WSACleanup();

	return 0;
}