#include <iostream>
#include<Windows.h>
#include"calcu.h"
#define FOREGROUND_CUS_L  FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_INTENSITY
void ShowGuide();
void BackLine();
void BackLine(const COORD &);
COORD GetCurrPos();

int main(int argc, char** argv)
{
	SetConsoleTitleA("calculator v3.0");
	ShowGuide();
	MyLab::calcu obj;

	std::cout << "Please enter an expression<ends with \'=\'>:" << std::endl;
	std::cout << "<Press N to exit>" << std::endl;
	char choice, cache;
	choice = ' ';
	WORD oldColor = MyLab::Setcolor(FOREGROUND_CUS_L);
	do
	{
		COORD current_pos = GetCurrPos();
		std::cin >> choice;
		if (choice != 'N' && choice != 'n')
		{
			std::cin.putback(choice);
			std::cin >> obj;
			BackLine(current_pos);
			std::cout << obj << std::endl;
			std::cin.clear();
		}
		else
		{
			MyLab::Setcolor(oldColor);
		}
	} while (choice != 'N' && choice != 'n');
	while ((cache = std::cin.get()) != '\n')
	{
		continue;
	}
	std::cout << "Bye!" << std::endl;
	std::cin.get();
	return 0;
}

void ShowGuide()
{
	std::cout << "*************************";
	std::cout << "welcome to calculator v3.0";
	std::cout << "*************************" << std::endl;
	std::cout << "User manual:" << std::endl;
	std::cout << "1.what is the valid expression?" << std::endl;
	std::cout << "   a. The simple arithmatic expression that contains valid operators and operands." << std::endl;
	std::cout << "   b. Valid operators: +, -, *, /, %, &, ^, and paired brackets." << std::endl;
	std::cout << "   c. Valid operands: integer and floating-point numbers." << std::endl;
	std::cout << "   d. Ends with \'=\'." << std::endl;
}

void BackLine()
{
	HANDLE curr = GetStdHandle(STD_OUTPUT_HANDLE);//获取句柄
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(curr, &csbi);//获取当前光标位置
	COORD pos = csbi.dwCursorPosition;
	COORD curr_pos = { 0,pos.Y - 1 };
	SetConsoleCursorPosition(curr, curr_pos);
	short width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	for (short i = 0; i < width; i++)
	{
		std::cout << ' ';
	}
	SetConsoleCursorPosition(curr, curr_pos);
}

void BackLine(const COORD &pos)
{
	HANDLE curr = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(curr, &csbi);//获取当前光标位置
	SetConsoleCursorPosition(curr, pos);
	short lines = csbi.dwCursorPosition.Y - pos.Y + 1;
	short width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	for (short i = 0; i < lines; i++)
	{
		for (short j = 0; j < width; j++)
		{
			std::cout << ' ';
		}
		std::cout << std::endl;
	}
	SetConsoleCursorPosition(curr, pos);
}

COORD GetCurrPos()
{
	HANDLE curr = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(curr, &csbi);//获取当前光标位置
	return csbi.dwCursorPosition;
}
