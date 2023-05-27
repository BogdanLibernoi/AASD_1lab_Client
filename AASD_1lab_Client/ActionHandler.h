#pragma once
#include <sstream>
#include "ConsoleHandler.h"
#include <Windows.h>
#include <conio.h>

#include "Patient.h"

#define UP 72
#define DOWN 80
#define ESC 27
#define ENTER 13

class ActionHandler
{

public:
	Patient GetPatient(std::string str)
	{
		if (str.length() == 0) return Patient();
		return Patient(str);
	}


	void ConsoleCursorVisible(bool show, short size, HANDLE hStdOut)
	{
		CONSOLE_CURSOR_INFO structCursorInfo;
		GetConsoleCursorInfo(hStdOut, &structCursorInfo);

		structCursorInfo.bVisible = show;
		structCursorInfo.dwSize = size;
		SetConsoleCursorInfo(hStdOut, &structCursorInfo);
	}
	void GoToXY(short x, short y, HANDLE hStdOut)
	{
		SetConsoleCursorPosition(hStdOut, { x,y });
	}
	void PrintStrPatient(std::string str, HANDLE hStdOut)
	{
		/*if (str == "queue is empty"){
			SetConsoleCursorPosition(hStdOut, { 45, 13 });
			std::cout << str;
		}
		else {*/		
			std::string strTemp[6];
			std::stringstream readerStr(str);

			int i = 0;
			while (std::getline(readerStr, str, ' '))
			{
				strTemp[i] = str;
				i++;
			}
			SetConsoleCursorPosition(hStdOut, { 45, 13 });
			std::cout << strTemp[2] + " " + strTemp[3] + " " + strTemp[4];
			SetConsoleCursorPosition(hStdOut, { 45, 14 });
			std::cout << "Gender: " << strTemp[0] << std::endl;
			SetConsoleCursorPosition(hStdOut, { 45, 15 });
			std::cout << "Condition: " << strTemp[1] << std::endl;
			SetConsoleCursorPosition(hStdOut, { 45, 16 });
			std::cout << "Age: " << strTemp[5] << std::endl;
		//}
		
	}
	void MenuHandler(ActionHandler action, HANDLE hStdOut, SOCKET clientSocket)
	{
		char msg[512] = "check";
		int check = -1;

		std::string menu[] = { "Next Patient", "Exit" };
		int activeMenu = 0;

		char ch;
		while (true)
		{
			int x = 45, y = 13;
			GoToXY(x, y, hStdOut);

			for (int i = 0; i < size(menu); i++)
			{
				if (i == activeMenu) SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
				else SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN);

				GoToXY(x, y++, hStdOut);
				std::cout << menu[i] << std::endl;
			}

			ch = _getch();
			if (ch == -32) ch = _getch();
			switch (ch)
			{
			case UP:
				if (activeMenu > 0)
					--activeMenu;
				break;

			case DOWN:
				if (activeMenu < size(menu) - 1)
					++activeMenu;
				break;

			case ENTER:
				switch (activeMenu)
				{
				case 0:
					system("CLS");
					GoToXY(50, 13, hStdOut);
					SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);


					check = send(clientSocket, msg, sizeof(msg), NULL);
					if (check == SOCKET_ERROR)
					{
						std::cout << "can't send message. Error #" << WSAGetLastError();
					}

					check = recv(clientSocket, msg, sizeof(msg), NULL);
					if (check != -1) {
						action.PrintStrPatient(msg, hStdOut);
						_getch();
						system("CLS");
					}
					else{
						SetConsoleCursorPosition(hStdOut, { 45, 13 });
						std::cout << "No patients in queue.";
					}
					
					break;

				case 1:
					exit(0);
					break;
				}
				break;

			case ESC:
				exit(0);
			}
		}
	}

	
	
};

