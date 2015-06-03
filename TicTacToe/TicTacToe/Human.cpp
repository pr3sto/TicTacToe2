// human.cpp - game player - Human

#include "human.h"

HumanPlayer::HumanPlayer(FieldInfo* _field, std::string _player_name) :
	Player(_field, _player_name) 
{}

HumanPlayer::~HumanPlayer() 
{}

COORD HumanPlayer::Move() const
{ 
	// for working with cursor
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
	DWORD Written = 0;

	COORD coord;     // coordinates of cursor
	COORD ret;       // retrun coordinates
	COORD position;  // position of cursor

	int size_of_field = field->size_of_field();

	// get current coordinates of cursor
	GetConsoleScreenBufferInfo(hStdOut, &csbiInfo);
	position.X = csbiInfo.dwCursorPosition.X;
	position.Y = csbiInfo.dwCursorPosition.Y;

	while (true)
	{
		// get x coordinate
		while (true)
		{
			std::cout << "Введите координату x: ";

			// get current coordinates of cursor
			GetConsoleScreenBufferInfo(hStdOut, &csbiInfo);
			coord.X = position.X;
			coord.Y = csbiInfo.dwCursorPosition.Y;

			std::cin >> ret.X;
			if (std::cin.good() && ret.X >= 0 && ret.X < size_of_field)
			{
				std::cin.ignore(10, '\n');
				break;
			}

			std::cin.clear();
			std::cin.ignore(10, '\n');

			// set cursor to start position + clean line
			SetConsoleCursorPosition(hStdOut, coord);
			FillConsoleOutputCharacter(hStdOut, ' ', 31, coord, &Written);
		}

		position.Y += 2;
		SetConsoleCursorPosition(hStdOut, position);

		// get y coordinate
		while (true)
		{
			std::cout << "Введите координату y: ";

			// get current coordinates of cursor
			GetConsoleScreenBufferInfo(hStdOut, &csbiInfo);
			coord.X = position.X;
			coord.Y = csbiInfo.dwCursorPosition.Y;

			std::cin >> ret.Y;
			if (std::cin.good() && ret.Y >= 0 && ret.Y < size_of_field)
			{
				std::cin.ignore(10, '\n');
				break;
			}

			std::cin.clear();
			std::cin.ignore(10, '\n');

			// set cursor to start position + clean line
			SetConsoleCursorPosition(hStdOut, coord);
			FillConsoleOutputCharacter(hStdOut, ' ', 31, coord, &Written);
		}

		// clean lines
		SetConsoleCursorPosition(hStdOut, position);
		FillConsoleOutputCharacter(hStdOut, ' ', 31, position, &Written);
		position.Y -= 2;
		SetConsoleCursorPosition(hStdOut, position);
		FillConsoleOutputCharacter(hStdOut, ' ', 31, position, &Written);

		if ((*field)[ret.X][ret.Y] != 0)
		{
			std::cout << "Позиция занята!";
			std::cin.get();

			// set cursor to start position
			SetConsoleCursorPosition(hStdOut, position);
		}
		else
		{
			break;
		}
	}
	
	return ret;
}

void HumanPlayer::Info() const
{
	std::cout
		<< std::setw(58) << "      1. Бот HumanPlayer         " << std::endl << std::endl
		<< std::setw(58) << "бот для ввода координат человеком" << std::endl
		<< std::setw(58) << "         Автор: pr3sto           " << std::endl
		<< std::setw(58) << "             2015                " << std::endl << std::endl << std::endl;
}