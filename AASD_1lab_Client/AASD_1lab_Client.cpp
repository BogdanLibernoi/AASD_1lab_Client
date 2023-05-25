#include <iostream>
#include <WinSock2.h>
#include <string>

#include "ActionHandler.h"
#include "Patient.h"


SOCKET clientSocket;

int main()
{
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

}

