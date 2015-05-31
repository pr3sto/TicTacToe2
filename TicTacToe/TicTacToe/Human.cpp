// human.cpp - game player - Human

#include "human.h"

HumanPlayer::HumanPlayer(FieldInfo* field_, std::string playerName_) :
	Player(field_, playerName_) { }

HumanPlayer::~HumanPlayer() { }

COORD HumanPlayer::Move() const
{ 
	// for working with cursor
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
	DWORD Written = 0;

	COORD coord;     // coordinates of cursor
	COORD ret;       // retrun coordinates
	COORD start_pos; // start position of cursor

	u_int sizeOfField = field->SizeOfField();

	// get current coordinates of cursor
	GetConsoleScreenBufferInfo(hStdOut, &csbiInfo);
	start_pos.X = csbiInfo.dwCursorPosition.X;
	start_pos.Y = csbiInfo.dwCursorPosition.Y;

	while (true)
	{
		while (true)
		{
			std::cout << "Введите координату x: ";

			// get current coordinates of cursor
			GetConsoleScreenBufferInfo(hStdOut, &csbiInfo);
			coord.X = start_pos.X;
			coord.Y = csbiInfo.dwCursorPosition.Y;

			std::cin >> ret.X;
			if (std::cin.good() && ret.X >= 0 && ret.X < sizeOfField)
			{
				std::cin.ignore(10, '\n');
				break;
			}

			std::cin.clear();
			std::cin.ignore(10, '\n');

			// set cursor + clean line
			SetConsoleCursorPosition(hStdOut, coord);
			FillConsoleOutputCharacter(hStdOut, ' ', 31, coord, &Written);
		}

		start_pos.Y += 2;
		SetConsoleCursorPosition(hStdOut, start_pos);
		while (true)
		{
			std::cout << "Введите координату y: ";

			// get current coordinates of cursor
			GetConsoleScreenBufferInfo(hStdOut, &csbiInfo);
			coord.X = start_pos.X;
			coord.Y = csbiInfo.dwCursorPosition.Y;

			std::cin >> ret.Y;
			if (std::cin.good() && ret.Y >= 0 && ret.Y < sizeOfField)
			{
				std::cin.ignore(10, '\n');
				break;
			}

			std::cin.clear();
			std::cin.ignore(10, '\n');

			// set cursor + clean line
			SetConsoleCursorPosition(hStdOut, coord);
			FillConsoleOutputCharacter(hStdOut, ' ', 31, coord, &Written);
		}

		if ((*field)[ret.X][ret.Y] != 0)
		{
			// set cursor + clean line
			SetConsoleCursorPosition(hStdOut, start_pos);
			FillConsoleOutputCharacter(hStdOut, ' ', 31, start_pos, &Written);
			start_pos.Y -= 2;
			SetConsoleCursorPosition(hStdOut, start_pos);
			FillConsoleOutputCharacter(hStdOut, ' ', 31, start_pos, &Written);

			std::cout << "Позиция занята!";
			std::cin.get();

			SetConsoleCursorPosition(hStdOut, start_pos);
		}
		else
			break;
	}
	
	return ret;
}