#include <iostream>
 
using namespace std;

#define _WINSOCK_DEPRECATED_NO_WARNINGS

// Window 소켓 프로그래밍을 위한 헤더
#include <WinSock2.h>

// ws2_32 라이브러리를 링크 (Window 소캣 API 함수를 사용하기 위해 필요
#pragma comment(lib, "ws2_32")

int main()
{
	WSAData wsaData;

	//WSAStartup 함수는 Windows 소켓 라이브러리를 초기화 (이 함수를 호출해야만 소켓 프로그래밍을 시작할 수 있음)
	int Result = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (Result != 0)
	{
		cout << "Error" << endl;
		exit(-1);
	}

	// socket 함수는 소켓을 생성, PF_INET는 인터넷 프로토콜(IP) 패밀리, SOCK_STREAM은 TCP 소캣, IPPROTO_TCP는 TCP프로토콜 사용
	SOCKET ServerSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	//INVALID_SOCKET은 소켓 생성 실패를 나타내는 상수.
	if (ServerSocket == INVALID_SOCKET)
	{
		cout << "Socket Error" << endl;
		cout << "Socket Error Number" << GetLastError() << endl;
		exit(-1);
	}

	while (true)
	{
		//SOCKADDR_IN 구조체를 사용, ServerSock라는 구조체 변수를 선언. (서버 소켓 주소 정버를 설정하는데 사용)
		SOCKADDR_IN ServerSock;

		//ServerSock 구조체를 초기화 (모든 멤버를 0으로 설정 초기화)
		memset(&ServerSock, 0, sizeof(SOCKADDR_IN));

		//주소체계를 설정, AF_INET은 IPV4 주소 체계를 의미
		ServerSock.sin_family = AF_INET;

		//서버 소켓이 7777번 포트에 바인딩되도록 설정 (htons는 호스트 바이트 순서-> 네트워크 바이트 순서로 변환)
		ServerSock.sin_port = htons(7777);

		//서버 소켓이 어떤 네트워크 인터베이스에 바인딩되는지 설정. INADDR_ANY는 모든 네트워크 인터페이스에 바인딩됨을 나타냄
		ServerSock.sin_addr.s_addr = INADDR_ANY;

		//서버 소켓을 지정된 주소와 포트에 바인딩한다.
		Result = bind(ServerSocket, (SOCKADDR*)&ServerSock, sizeof(ServerSock));

		//서버 소켓이 클라이언트의 연결 요청을 수락할 수 있도록 설정, 5는 동시 대기 가능한 연결 요청의 최대수
		Result = listen(ServerSocket, 5);

		// 클라이언트 소켓의 주소 정보를 저장하는 ClientSock 구조체를 선언
		SOCKADDR_IN ClientSock;
		memset(&ClientSock, 0, sizeof(SOCKADDR_IN));

		//클라이언트 소켓의 주소 구조체의 크기를 저장.
		int ClientSockLength = sizeof(ClientSock);

		//accept 함수를 사용, 클라이언트의 연결 요청을 수락하고, 연결된 클라이언트 소켓을 반환.
		SOCKET ClientSocket = accept(ServerSocket, (SOCKADDR*)&ClientSock, &ClientSockLength);

		//전송할 메시지를 저장하는 문자열 선언
		//char Message[] = "";

		int num1 = 5;
		recv(ClientSocket, (char*)&num1, sizeof(num1), 0);

		int num2 = 10;
		recv(ClientSocket, (char*)&num2, sizeof(num2), 0);

		send(ClientSocket, (char*)&Result, sizeof(Result), 0);


		//Mesage 값을 전송하도록
		//int SendByte = send(ClientSocket, Message, (int)strlen(Message), 0);

		//수신된 데이터를 저장하기 위한 Buffer 선언
		char Buffer[1024] = { 0, };

		cout << "client send :" << Buffer << endl;

		//클라이언트 소켓을 닫는다. 통신이 끝난 뒤.
		closesocket(ClientSocket);

	}

	//서버 소켓을 닫는다.
	closesocket(ServerSocket);

	// Windows 소켓 라이브러리를 정리하고 하제.
	WSACleanup();

	return 0;
}