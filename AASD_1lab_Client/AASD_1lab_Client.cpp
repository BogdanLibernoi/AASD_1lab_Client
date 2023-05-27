#include <iostream>
#include <WinSock2.h>
#include <string>
#include <Windows.h>
#include <conio.h>


#include "ActionHandler.h"
#include "Patient.h"

#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable: 4996)
#define _WINSOCK_DEPRECATED_NO_WARNINGS





SOCKET clientSocket;


#pragma region Console Handler

HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);



#pragma endregion


void StartWork(ActionHandler action)
{
	while (true)
	{
		action.ConsoleCursorVisible(false, 15, hStdOut);
		action.MenuHandler(action, hStdOut, clientSocket);
	}
	
}

int main()
{
	ActionHandler action;

#pragma region SocketsConnection



    WSADATA wsaData;

    int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (result !=0)
	{	
		std::cout << "WSAStartup failed. Error: " << WSAGetLastError() << std::endl;
		return 1;
	}
	else
		std::cout << "WsaStartup successful" << std::endl;

	//Socket Creation and Initialization
	clientSocket = socket(AF_INET, SOCK_STREAM, NULL);

	if (clientSocket == INVALID_SOCKET)
	{
		std::cout << "Socket initialization error: " << WSAGetLastError() << std::endl;
		closesocket(clientSocket);
		WSACleanup();
		return 1;
	}

	sockaddr_in servInfo;
	ZeroMemory(&servInfo, sizeof(servInfo));

	servInfo.sin_family = AF_INET;
	servInfo.sin_addr.s_addr = inet_addr("127.0.0.1");
	servInfo.sin_port = htons('1119');

	result = connect(clientSocket, (sockaddr*)&servInfo, sizeof(servInfo));

	if (result != 0)
	{
		std::cout << "Connection to server is Failed. Error: " << WSAGetLastError() << std::endl;
		closesocket(clientSocket);
		WSACleanup();
		return 1;
	}
	else
	{
		std::cout << "Connection established succesfuly. Ready to send a message to Server" << std::endl;
		StartWork(action);
	}
#pragma endregion

	

	
}

