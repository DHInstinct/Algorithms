#pragma once

#include <iostream>

enum class Color
{
	black = 0, red = 12, green = 10, yellow = 14, blue = 1, magenta = 13, cyan = 11, white = 15
};

#ifdef _WIN32
	#include <Windows.h>
#elif __APPLE__ 
	#define RESET   "\033[0m"
	#define BLACK   "\033[30m" 
	#define RED     "\033[31m" 
	#define GREEN   "\033[32m" 
	#define YELLOW  "\033[33m" 
	#define BLUE    "\033[34m" 
	#define MAGENTA "\033[35m" 
	#define CYAN    "\033[36m" 
	#define WHITE   "\033[37m"  
#endif

namespace ConsoleColorer
{
	static void SetConsoleColor(Color c)
	{
#ifdef _WIN32
		static HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(handle, (WORD)c);
#elif __APPLE__

		switch (c)
		{
		case Color::black:
			std::cout << BLACK;
			break;

		case Color::red:
			std::cout << RED;
			break;

		case Color::green:
			std::cout << GREEN;
			break;

		case Color::yellow:
			std::cout << YELLOW;
			break;

		case Color::blue:
			std::cout << BLUE;
			break;

		case Color::magenta:
			std::cout << MAGENTA;
			break;

		case Color::cyan:
			std::cout << CYAN;
			break;

		case Color::white:
			std::cout << WHITE;
			break;

		default:
			std::cout << RESET;
		}
#endif
	}
}