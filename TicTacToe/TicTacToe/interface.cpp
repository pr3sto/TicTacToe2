// interface.cpp - console interface of game

#include "interface.h"

using std::cout;
using std::cin;
using std::endl;
using std::setw;

Interface::Interface()
{
	game_components = nullptr;
}

Interface::Interface(GameComponents* game_comps)
{
	game_components = game_comps;
}

Interface::~Interface() 
{}


void Interface::Logo() const 
{
	cout << setw(75) << R"(  _____    ______                                      _________    )" << endl;
	cout << setw(75) << R"(  \  \ \  /   / /                                    /        \ \   )" << endl;
	cout << setw(75) << R"(   \  \ \/   / /     ___     ____    ________       /    ___   \ \  )" << endl;
	cout << setw(75) << R"(    \  \/   / /      \  \   /  / /  /  ____/_/     |    /|  |   | | )" << endl;
	cout << setw(75) << R"(    |   _   | |       \  \_/  / /  /  /____        |   | |  |   | | )" << endl;
	cout << setw(75) << R"(   /   / \   \ \       \     / /   \____  \ \      |   |_|_/    | | )" << endl;
	cout << setw(75) << R"(  /   / / \   \ \       \   / /     ____\  \ \      \          / /  )" << endl;
	cout << setw(75) << R"( /___/_/   \___\_\       \_/_/     /_______/_/       \________/_/   )" << endl;
	cout << endl;
}

void Interface::GamingField() const
{
	SetConsoleOutputCP(866); // for border's symbols
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE); // for color changing

	int size_of_field = game_components->field()->size_of_field();
	
	int space = (10 - size_of_field) * 2; // to locate field in the middle

	// to locate field in the middle
	cout << endl;
	if (size_of_field < 9)
		cout << endl;
	if (size_of_field < 7)
		cout << endl;
	if (size_of_field < 5)
		cout << endl;

	// top of field
	cout << setw(38 + space) << "\xda" << "\xc4\xc4\xc4";
	for (int i = 1; i < size_of_field; ++i) cout << "\xc2" << "\xc4\xc4\xc4";
	cout << "\xbf" << endl;

	// middle of field
	for (int i = 0; i < size_of_field; ++i)
	{
		cout << setw(38 + space) << "\xb3";
		for (int j = 0; j < size_of_field; ++j)
		{
			SetConsoleTextAttribute(hStdOut, (WORD)((BLACK << 4) | BLUE));
			cout << j << "," << i;
			SetConsoleTextAttribute(hStdOut, (WORD)((BLACK << 4) | LIGHT_GRAY));
			cout << "\xb3";
		}
		cout << endl;

		if (i == size_of_field - 1) break;

		cout << setw(38 + space) << "\xc3" << "\xc4\xc4\xc4";
		for (int j = 1; j < size_of_field; ++j) cout << "\xc5" << "\xc4\xc4\xc4";
		cout << "\xb4" << endl;
	}

	// bottom of field
	cout << setw(38 + space) << "\xc0" << "\xc4\xc4\xc4";
	for (int i = 1; i < size_of_field; ++i) cout << "\xc1" << "\xc4\xc4\xc4";
	cout << "\xd9" << endl;

	SetConsoleOutputCP(1251);
}

void Interface::PlayingInfo() const
{
	// for working with cursor
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	// coordinates of cursor
	COORD coord;

	coord.X = 15; coord.Y = 1;
	SetConsoleCursorPosition(hStdOut, coord);
	cout << "����";

	coord.X = 5; coord.Y = 4;
	SetConsoleCursorPosition(hStdOut, coord);
	cout << "������ ����� (X):";
	coord.X = 23; coord.Y = 4;
	SetConsoleCursorPosition(hStdOut, coord);
	cout << game_components->player1()->player_name();

	coord.X = 5; coord.Y = 6;
	SetConsoleCursorPosition(hStdOut, coord);
	cout << "������ ����� (O):";
	coord.X = 23; coord.Y = 6;
	SetConsoleCursorPosition(hStdOut, coord);
	cout << game_components->player2()->player_name();

	coord.X = 5; coord.Y = 8;
	SetConsoleCursorPosition(hStdOut, coord);
	cout << "������ ����� ��� ������: ";
	coord.X = 30; coord.Y = 8;
	SetConsoleCursorPosition(hStdOut, coord);
	cout << game_components->field()->size_of_win_row();
}

void Interface::PlayingMenu() const
{
	system("cls");

	this->GamingField();
	this->PlayingInfo();
}

void Interface::PlayersMoveMenu(int player) const
{
	// for working with cursor
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD Written = 0;

	// coordinates of cursor
	COORD coord;
	coord.X = 5; coord.Y = 11;

	// clear line
	SetConsoleCursorPosition(hStdOut, coord);
	FillConsoleOutputCharacter(hStdOut, ' ', 31, coord, &Written);

	cout << "���:";

	coord.X = 10; coord.Y = 11;
	SetConsoleCursorPosition(hStdOut, coord);

	if (player == 1)
		cout << game_components->player1()->player_name() << endl;
	
	else if (player == 2)
		cout << game_components->player2()->player_name() << endl;

	coord.X = 5; coord.Y = 13;
	SetConsoleCursorPosition(hStdOut, coord);
}

void Interface::ShowPlayerMove(int player, COORD move) const
{
	// for working with cursor
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

	// coordinates of cursor
	COORD coord;
	coord.X = 5; coord.Y = 13;

	SetConsoleCursorPosition(hStdOut, coord);
	cout << "��� � ������ (" << move.X << ", " << move.Y << ") ";

	int size_of_field = game_components->field()->size_of_field();
	int space = (10 - size_of_field) * 2 + 38;
	
	COORD position; // position of symbol

	if (size_of_field < 5)
		position.Y = 5 + move.Y * 2;
	else if (size_of_field < 7)
		position.Y = 4 + move.Y * 2;
	else if (size_of_field < 9)
		position.Y = 3 + move.Y * 2;
	else
		position.Y = 2 + move.Y * 2;

	position.X = space + 4 * move.X;

	// set cursor, set color and print symbol
	SetConsoleCursorPosition(hStdOut, position);
	SetConsoleTextAttribute(hStdOut, (WORD)((BLACK << 4) | LIGHT_RED));
	if (player == 1) cout << " X ";
	else if (player == 2) cout << " O ";
	SetConsoleTextAttribute(hStdOut, (WORD)((BLACK << 4) | LIGHT_GRAY));

	coord.X = 24; coord.Y = 13;
	SetConsoleCursorPosition(hStdOut, coord);

	std::cin.get();
}

void Interface::GameOver(int player) const
{
	// for working with cursor
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD Written = 0;

	// coordinates of cursor
	COORD coord;
	coord.X = 5; coord.Y = 11;

	// set cursor + clean lines
	SetConsoleCursorPosition(hStdOut, coord);
	FillConsoleOutputCharacter(hStdOut, ' ', 31, coord, &Written);
	coord.Y += 2;
	SetConsoleCursorPosition(hStdOut, coord);
	FillConsoleOutputCharacter(hStdOut, ' ', 31, coord, &Written);
	
	coord.X = 10; coord.Y = 12;
	SetConsoleCursorPosition(hStdOut, coord);

	cout << "���� ��������";

	coord.X = 0; coord.Y = 14;
	SetConsoleCursorPosition(hStdOut, coord);

	std::string winner = "�������(�) ";
	if (player == 1)
		winner += game_components->player1()->player_name();
	else if (player == 2)
		winner += game_components->player2()->player_name();
	else
		winner = "�����";
	winner += "!";

	cout << setw(17 + winner.size() / 2) << winner;

	cin.get();
}


void Interface::MainMenu() const 
{
	this->Logo();
	
	cout << endl;
	cout << setw(46) << "1.   ������  " << endl << endl;
	cout << setw(46) << "2. ��������� " << endl << endl;
	cout << setw(46) << "3. ����������" << endl << endl;
	cout << setw(46) << "4.  �� ����  " << endl << endl;
	cout << setw(46) << "5.   �����   " << endl << endl;
	cout << endl;
}

void Interface::SettingsMenu() const 
{
	this->Logo();

	cout << setw(63) << "���������:                " << endl << endl;
	cout << setw(50) << "1. ������ ����            ";
	cout << setw(5) << "(" << game_components->field()->size_of_field() << "x"
		<< game_components->field()->size_of_field() << ")" << endl << endl;
	cout << setw(50) << "2. ������ ����� ��� ������";
	cout << setw(5) << "(" << game_components->field()->size_of_win_row() << ")" << endl << endl;
	cout << setw(50) << "3. ������ �����           ";
	cout << setw(5) << "(" << game_components->player1()->player_name() << ")" << endl << endl;
	cout << setw(50) << "4. ������ �����           ";
	cout << setw(5) << "(" << game_components->player2()->player_name() << ")" << endl << endl;

	cout << endl << setw(63) << "5. �����                  " << endl << endl;
}

void Interface::SizeOfFieldMenu() const
{
	system("cls");
	this->Logo();

	cout << endl << endl << endl
	    << setw(48) << "����������� ������:   "
		<< game_components->field()->MIN_SIZE_OF_FIEFD 
		<< " x " 
		<< game_components->field()->MIN_SIZE_OF_FIEFD
		<< endl << endl;
	cout << setw(47) << "������������ ������: "
		<< game_components->field()->MAX_SIZE_OF_FIEFD
		<< " x "
		<< game_components->field()->MAX_SIZE_OF_FIEFD
		<< endl << endl << endl << endl;
		 
	game_components->field()->set_size_of_field(
		this->GetNumber("\t\t\t    ������� ������ ����: ",
			game_components->field()->MIN_SIZE_OF_FIEFD,
			game_components->field()->MAX_SIZE_OF_FIEFD
		)
	);
}

void Interface::SizeOfWinRowMenu() const
{
	system("cls");
	this->Logo();

	cout << endl
		<< setw(65) << "������ ����� ��� ������ - ��� ���������� �����," << endl
		<< setw(65) << "����������� �  ���  ��  �����������, ��������� " << endl
		<< setw(65) << "��� ��������, ����������� ��� ������.          " << endl
		<< endl << endl

		<< setw(50) << "����������� ������:  "
		<< game_components->field()->MIN_SIZE_OF_WIN_ROW << endl << endl
		<< setw(50) << "������������ ������: "
		<< game_components->field()->size_of_field() << endl << endl << endl;

	game_components->field()->set_size_of_win_row(
		this->GetNumber("\t\t\t������� ������ ����� ��� ������: ",
			game_components->field()->MIN_SIZE_OF_WIN_ROW,
			game_components->field()->size_of_field()
		)
	);
}

void Interface::ListOfBots() const
{
	int counter = 1;
	std::vector<Player*> tmp = game_components->vector_of_bots();

	for (auto i = tmp.begin(); i != tmp.end(); ++i, ++counter)
	{
		int width = 40 - (*i)->player_name().size() / 2;
		cout << setw(width) << counter << ". " << (*i)->player_name() << endl;
	}
	cout << endl;
}

void Interface::ChoisePlayer1Menu() const
{
	system("cls");
	this->Logo();

	cout << endl
		<< setw(55) << "������ ����� ����� ������." << endl << endl << endl
		<< setw(53) << "�������� ��� ������: " << endl << endl
		<< setw(48) << " 1. �������  " << endl << endl
		<< setw(48) << "2. ��������� " << endl << endl << endl;
	
	int player_choise = this->GetNumber("\t\t\t    ������� ����� ������ ����: ", 1, 2);
	switch (player_choise)
	{
	case 1: // human
		{
			  system("cls");
			  this->Logo();

			  cout << endl << endl << endl;
			  cout << setw(60) << "������������ ���������� ��������: 12" << endl << endl;
			  cout << setw(44) << "������� ��� ������: ";
			  std::string tmp;  getline(cin, tmp);
			  game_components->set_player1(game_components->vector_of_humans()[0]);
			  game_components->player1()->set_player_name(tmp);
			  break;
		}
	case 2: // bot
		{
			  system("cls");
			  this->Logo();

			  cout << endl 
				<< setw(50) << "�������� ����: " << endl << endl;
			  this->ListOfBots();
			  cout << endl;

			  // player_choise - 1, because of vector have numeration from 0
			  int player_choise = this->GetNumber(
				  "\t\t\t    ������� ����� ������ ����: ",
				  1,
				  game_components->vector_of_bots().size()
				  ) - 1;

			  game_components->set_player1(game_components->vector_of_bots()[player_choise]);
		}
		break;
	default:
		break;
	}
}

void Interface::ChoisePlayer2Menu() const
{
	system("cls");
	this->Logo();

	cout << endl
		<< setw(55) << "������ ����� ����� ������." << endl << endl << endl
		<< setw(53) << "�������� ��� ������: " << endl << endl
		<< setw(48) << " 1. �������  " << endl << endl
		<< setw(48) << "2. ��������� " << endl << endl << endl;

	int player_choise = this->GetNumber("\t\t\t    ������� ����� ������ ����: ", 1, 2);
	switch (player_choise)
	{
	case 1: // human
	{
			  system("cls");
			  this->Logo();

			  cout << endl << endl << endl;
			  cout << setw(60) << "������������ ���������� ��������: 12" << endl << endl;
			  cout << setw(44) << "������� ��� ������: ";
			  std::string tmp;  getline(cin, tmp);
			  game_components->set_player2(game_components->vector_of_humans()[1]);
			  game_components->player2()->set_player_name(tmp);
			  break;
	}
	case 2: // bot
	{
			  system("cls");
			  this->Logo();

			  cout << endl
				  << setw(50) << "�������� ����: " << endl << endl;
			  this->ListOfBots();
			  cout << endl;

			  // player_choise - 1, because of vector have numeration from 0
			  int player_choise = this->GetNumber(
				  "\t\t\t    ������� ����� ������ ����: ",
				  1,
				  game_components->vector_of_bots().size()
				  ) - 1;

			  game_components->set_player2(game_components->vector_of_bots()[player_choise]);
	}
		break;
	default:
		break;
	}
}

void Interface::SettingsMenuSession() const
{
	while (true)
	{
		system("cls");
		this->SettingsMenu();

		int sett_choise = GetNumber("\t\t\t    ������� ����� ������ ����: ", 1, 5);

		switch (sett_choise)
		{
		case 1: // size of field
			this->SizeOfFieldMenu();
			break;			
		case 2: // size of win row
			this->SizeOfWinRowMenu();
			break;			
		case 3: // player 1
			this->ChoisePlayer1Menu();
			break;
		case 4: // player 2
			this->ChoisePlayer2Menu();
			break;			
		case 5: // back
			return;
		default:
			break;
		}
	}
}

int Interface::MenuSession() const
{	
	while (true)
	{
		system("cls");
		this->MainMenu();

		int menu_choise = GetNumber("\t\t\t    ������� ����� ������ ����: ", 1, 5);

		switch (menu_choise)
		{
		case 1: // play
			return 1;
		case 2: // settings
			this->SettingsMenuSession();
			break;
		case 3: // statistic
			//TODO: write stats func
			break;
		case 4: // info
			this->Info();
			break;
		case 5: // exit
			return 0;
		default:
			break;
		}
	}
}

void Interface::BotsInfo() const
{
	game_components->vector_of_humans()[0]->Info();
	cout << endl;
	
	int width;
	int counter = 2;

	auto bots = game_components->vector_of_bots();
	for (auto i = bots.begin(); i != bots.end(); ++i, ++counter)
	{
		width = 37 - (*i)->player_name().size() / 2;
		cout << setw(width) << counter << ". ��� " << (*i)->player_name() << endl << endl;
		(*i)->Info();
		cout << endl << endl << endl;
	}
}

void Interface::Info() const
{
	system("cls");
	this->Logo();
	cout << endl;

	cout << setw(44) << "�� ����:" << endl << endl
		<< setw(75) << "�������� - ������  �  ����������  ����  �����  �����  ������������  " << endl << endl
		<< setw(75) << "�� ���������� ���� ������ ������� (������ �� ������������� �����).  " << endl << endl
		<< setw(75) << "���� �� ������� ������  ����������� (X), ������ � ��������� (O).  " << endl << endl
		<< endl << endl
		<< setw(46) << "������� ����:" << endl << endl
		<< setw(75) << "������  ��  ������� ������  ��  ��������� ������  ����  ����� (���� " << endl << endl
		<< setw(75) << "������ ��������,  ������ ������ ������).  ������, ����������� � ��� " << endl << endl
		<< setw(75) << "N ����� ����� ��  ���������, ����������� ��� ���������, ����������. " << endl << endl
		<< setw(75) << "������ ��� ������ �����, �������� ��������.                         " << endl << endl
		<< endl << endl
		<< setw(46) << "�����: pr3sto" << endl << endl
		<< setw(42) << "2015" << endl << endl
		<< endl << endl << endl
		<< setw(43) << "����:" << endl << endl;
       	 
	this->BotsInfo();

	// for working with cursor
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	// coordinates of cursor
	COORD coord;
	coord.X = 0; coord.Y = 0;
	SetConsoleCursorPosition(hStdOut, coord);

	cin.get();
}


int Interface::GetNumber(const std::string& msg, int min, int max) const
{
	// for working with cursor
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
	DWORD Written = 0;

	// coordinates of cursor
	COORD coord;

	// retrun value
	int ret;

	while (true)
	{
		if (msg.empty())
			cout << "������� ����� �� " << min << " �� " << max << ": ";
		else
			cout << msg;

		// get current coordinates of cursor
		GetConsoleScreenBufferInfo(hStdOut, &csbiInfo);
		coord.X = 0;
		coord.Y = csbiInfo.dwCursorPosition.Y;

		cin >> ret;
		if (cin.good() && ret != 0 && ret >= min && ret <= max)
		{
			cin.ignore(10, '\n');
			break;
		}

		cin.clear();
		cin.ignore(10, '\n');

		// set cursor + clean next 2 lines
		SetConsoleCursorPosition(hStdOut, coord);
		FillConsoleOutputCharacter(hStdOut, ' ', 300, coord, &Written);
	}

	return ret;
}