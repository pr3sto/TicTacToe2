// interface.cpp - console interface of game

#include "interface.h"

using std::cout;
using std::cin;
using std::endl;
using std::setw;

Interface::Interface()
{
	gameComponents = nullptr;
}

Interface::Interface(GameComponents* gameComps_)
{
	gameComponents = gameComps_;
}

Interface::~Interface() 
{ }


void Interface::ShowLogo() const 
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

void Interface::ShowGamingField() const
{
	SetConsoleOutputCP(866); // for border's symbols
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE); // for color changing

	u_int sizeOfField = gameComponents->GamingField()->SizeOfField();
	u_int space = (10 - sizeOfField) * 2;

	cout << endl;
	if (sizeOfField < 9)
		cout << endl;
	if (sizeOfField < 7)
		cout << endl;
	if (sizeOfField < 5)
		cout << endl;

	// top of field
	cout << setw(38 + space) << "\xda" << "\xc4\xc4\xc4";
	for (u_int i = 1; i < sizeOfField; ++i) cout << "\xc2" << "\xc4\xc4\xc4";
	cout << "\xbf" << endl;

	// middle of field
	for (u_int i = 0; i < sizeOfField; ++i)
	{
		cout << setw(38 + space) << "\xb3";
		for (u_int j = 0; j < sizeOfField; ++j)
		{
			SetConsoleTextAttribute(hStdOut, (WORD)((Black << 4) | Blue));
			cout << j << "," << i;
			SetConsoleTextAttribute(hStdOut, (WORD)((Black << 4) | LightGray));
			cout << "\xb3";
		}
		cout << endl;

		if (i == sizeOfField - 1) break;

		cout << setw(38 + space) << "\xc3" << "\xc4\xc4\xc4";
		for (u_int j = 1; j < sizeOfField; ++j) cout << "\xc5" << "\xc4\xc4\xc4";
		cout << "\xb4" << endl;
	}

	// bottom of field
	cout << setw(38 + space) << "\xc0" << "\xc4\xc4\xc4";
	for (u_int i = 1; i < sizeOfField; ++i) cout << "\xc1" << "\xc4\xc4\xc4";
	cout << "\xd9" << endl;

	SetConsoleOutputCP(1251);
}

void Interface::ShowPlayingInfo() const
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
	cout << gameComponents->Player1()->GetPlayerName();

	coord.X = 5; coord.Y = 6;
	SetConsoleCursorPosition(hStdOut, coord);
	cout << "������ ����� (O):";
	coord.X = 23; coord.Y = 6;
	SetConsoleCursorPosition(hStdOut, coord);
	cout << gameComponents->Player2()->GetPlayerName();

	coord.X = 5; coord.Y = 8;
	SetConsoleCursorPosition(hStdOut, coord);
	cout << "������ ����� ��� ������: ";
	coord.X = 30; coord.Y = 8;
	SetConsoleCursorPosition(hStdOut, coord);
	cout << gameComponents->GamingField()->SizeOfWinRow();
}

void Interface::ShowPlayingMenu() const
{
	system("cls");

	this->ShowGamingField();
	this->ShowPlayingInfo();
}

void Interface::ShowPlayersMoveMenu(u_int player) const
{
	if (player != 1 && player != 2)
	{
		std::cerr << "Error! Invalid argument in void Interface::ShowPlayingMenu(u_int).";
		exit(1);
	}

	// for working with cursor
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD Written = 0;
	// coordinates of cursor
	COORD coord;

	coord.X = 5; coord.Y = 11;
	SetConsoleCursorPosition(hStdOut, coord);
	FillConsoleOutputCharacter(hStdOut, ' ', 31, coord, &Written);
	cout << "���:";
	coord.X = 10; coord.Y = 11;
	SetConsoleCursorPosition(hStdOut, coord);

	if (player == 1)
		cout << gameComponents->Player1()->GetPlayerName() << endl;
	
	else if (player == 2)
		cout << gameComponents->Player2()->GetPlayerName() << endl;

	coord.X = 5; coord.Y = 13;
	SetConsoleCursorPosition(hStdOut, coord);
}

void Interface::ShowPlayerMove(u_int player, COORD move) const
{
	// for working with cursor
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	
	// coordinates of cursor
	COORD coord;
	coord.X = 5; coord.Y = 13;
	SetConsoleCursorPosition(hStdOut, coord);

	cout << "��� � ������ (" << move.X << ", " << move.Y << ") ";

	// symbol on the field
	u_int sizeOfField = gameComponents->GamingField()->SizeOfField();
	u_int space = (10 - sizeOfField) * 2 + 38;
	COORD position;

	if (sizeOfField < 5)
		position.Y = 5 + move.Y * 2;
	else if (sizeOfField < 7)
		position.Y = 4 + move.Y * 2;
	else if (sizeOfField < 9)
		position.Y = 3 + move.Y * 2;
	else
		position.Y = 2 + move.Y * 2;
	

	position.X = space + 4 * move.X;

	SetConsoleCursorPosition(hStdOut, position);
	SetConsoleTextAttribute(hStdOut, (WORD)((Black << 4) | LightRed));
	if (player == 1) cout << " X ";
	else if (player == 2) cout << " O ";
	SetConsoleTextAttribute(hStdOut, (WORD)((Black << 4) | LightGray));

	coord.X = 24; coord.Y = 13;
	SetConsoleCursorPosition(hStdOut, coord);
	std::cin.get();
}

void Interface::PlayerWin(u_int player) const
{
	// for working with cursor
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD Written = 0;

	// coordinates of cursor
	COORD coord;
	coord.X = 5; coord.Y = 11;

	// set cursor + clean line
	SetConsoleCursorPosition(hStdOut, coord);
	FillConsoleOutputCharacter(hStdOut, ' ', 31, coord, &Written);
	coord.Y += 2;
	SetConsoleCursorPosition(hStdOut, coord);
	FillConsoleOutputCharacter(hStdOut, ' ', 31, coord, &Written);
	
	coord.X = 10; coord.Y = 12;
	SetConsoleCursorPosition(hStdOut, coord);

	cout << "���� ��������!";

	coord.X = 0; coord.Y = 14;
	SetConsoleCursorPosition(hStdOut, coord);

	std::string winner = "�������(�) ";
	if (player == 1)
		winner += gameComponents->Player1()->GetPlayerName();
	else if (player == 2)
		winner += gameComponents->Player2()->GetPlayerName();
	winner += "!";

	u_int width = 17 + winner.size() / 2;
	cout << setw(width) << winner;

	cin.get();
}

void Interface::ShowMainMenu() const 
{
	this->ShowLogo();
	
	cout << endl;
	cout << setw(46) << "1.   ������  " << endl << endl;
	cout << setw(46) << "2. ��������� " << endl << endl;
	cout << setw(46) << "3. ����������" << endl << endl;
	cout << setw(46) << "4.  �� ����  " << endl << endl;
	cout << setw(46) << "5.   �����   " << endl << endl;
	cout << endl;
}

void Interface::ShowSettingsMenu() const 
{
	this->ShowLogo();

	cout << setw(63) << "���������:                " << endl << endl;
	cout << setw(50) << "1. ������ ����            ";
	cout << setw(5) << "(" << gameComponents->GamingField()->SizeOfField() << "x"
		<< gameComponents->GamingField()->SizeOfField() << ")" << endl << endl;
	cout << setw(50) << "2. ������ ����� ��� ������";
	cout << setw(5) << "(" << gameComponents->GamingField()->SizeOfWinRow() << ")" << endl << endl;
	cout << setw(50) << "3. ������ �����           ";
	cout << setw(5) << "(" << gameComponents->Player1()->GetPlayerName() << ")" << endl << endl;
	cout << setw(50) << "4. ������ �����           ";
	cout << setw(5) << "(" << gameComponents->Player2()->GetPlayerName() << ")" << endl << endl;

	cout << endl << setw(63) << "5. �����                  " << endl << endl;
}

void Interface::ShowSizeOfFieldMenu() const
{
	system("cls");
	this->ShowLogo();

	cout << endl << endl << endl
	    << setw(48) << "����������� ������:   "
		<< gameComponents->GamingField()->MIN_SIZE_OF_FIEFD 
		<< " x " 
		<< gameComponents->GamingField()->MIN_SIZE_OF_FIEFD
		<< endl << endl;
	cout << setw(47) << "������������ ������: "
		<< gameComponents->GamingField()->MAX_SIZE_OF_FIEFD
		<< " x "
		<< gameComponents->GamingField()->MAX_SIZE_OF_FIEFD
		<< endl << endl << endl << endl;
		 
	gameComponents->GamingField()->SetSizeOfField(
		this->GetNumber("\t\t\t    ������� ������ ����: ",
			gameComponents->GamingField()->MIN_SIZE_OF_FIEFD,
			gameComponents->GamingField()->MAX_SIZE_OF_FIEFD
		)
	);
}

void Interface::ShowSizeOfWinRowMenu() const
{
	system("cls");
	this->ShowLogo();

	cout << endl
		<< setw(65) << "������ ����� ��� ������ - ��� ���������� �����," << endl
		<< setw(65) << "����������� �  ���  ��  �����������, ��������� " << endl
		<< setw(65) << "��� ��������, ����������� ��� ������.          " << endl
		<< endl << endl

		<< setw(50) << "����������� ������:  "
		<< gameComponents->GamingField()->MIN_SIZE_OF_WIN_ROW << endl << endl
		<< setw(50) << "������������ ������: "
		<< gameComponents->GamingField()->SizeOfField() << endl << endl << endl;

	gameComponents->GamingField()->SetSizeOfWinRow(
		this->GetNumber("\t\t\t������� ������ ����� ��� ������: ",
			gameComponents->GamingField()->MIN_SIZE_OF_WIN_ROW,
			gameComponents->GamingField()->SizeOfField()
		)
	);
}

void Interface::ShowBots() const
{
	int counter = 1;
	std::vector<Player*> tmp = gameComponents->VectorOfBots();

	for (auto i = tmp.begin(); i != tmp.end(); ++i, ++counter)
	{
		u_int width = 40 - (*i)->GetPlayerName().size() / 2;
		cout << setw(width) << counter << ". " << (*i)->GetPlayerName() << endl;
	}
	cout << endl;
}

void Interface::ShowChoisePlayer1Menu() const
{
	system("cls");
	this->ShowLogo();

	cout << endl
		<< setw(55) << "������ ����� ����� ������." << endl << endl << endl
		<< setw(53) << "�������� ��� ������: " << endl << endl
		<< setw(48) << " 1. �������  " << endl << endl
		<< setw(48) << "2. ��������� " << endl << endl << endl;
	
	u_int player_choise = this->GetNumber("\t\t\t    ������� ����� ������ ����: ", 1, 2);
	switch (player_choise)
	{
	case 1:
		{
			  system("cls");
			  this->ShowLogo();

			  cout << endl << endl << endl;
			  cout << setw(60) << "������������ ���������� ��������: 12" << endl << endl;
			  cout << setw(44) << "������� ��� ������: ";
			  std::string tmp;  getline(cin, tmp);
			  gameComponents->SetPlayer1(gameComponents->VectorOfHumans()[0]);
			  gameComponents->Player1()->SetPlayerName(tmp);
			  break;
		}
	case 2:
		{
			  system("cls");
			  this->ShowLogo();

			  cout << endl 
				<< setw(50) << "�������� ����: " << endl << endl;
			  ShowBots();
			  cout << endl;

			  // player_choise - 1, because of vector have numeration from 0
			  u_int player_choise = this->GetNumber(
				  "\t\t\t    ������� ����� ������ ����: ",
				  1,
				  gameComponents->VectorOfBots().size()
				  ) - 1;

			  gameComponents->SetPlayer1(gameComponents->VectorOfBots()[player_choise]);
		}
		break;
	default:
		break;
	}
}

void Interface::ShowChoisePlayer2Menu() const
{
	system("cls");
	this->ShowLogo();

	cout << endl
		<< setw(55) << "������ ����� ����� ������." << endl << endl << endl
		<< setw(53) << "�������� ��� ������: " << endl << endl
		<< setw(48) << " 1. �������  " << endl << endl
		<< setw(48) << "2. ��������� " << endl << endl << endl;

	u_int player_choise = this->GetNumber("\t\t\t    ������� ����� ������ ����: ", 1, 2);
	switch (player_choise)
	{
	case 1:
	{
			  system("cls");
			  this->ShowLogo();

			  cout << endl << endl << endl;
			  cout << setw(60) << "������������ ���������� ��������: 12" << endl << endl;
			  cout << setw(44) << "������� ��� ������: ";
			  std::string tmp;  getline(cin, tmp);
			  gameComponents->SetPlayer2(gameComponents->VectorOfHumans()[1]);
			  gameComponents->Player2()->SetPlayerName(tmp);
			  break;
	}
	case 2:
	{
			  system("cls");
			  this->ShowLogo();

			  cout << endl
				  << setw(50) << "�������� ����: " << endl << endl;
			  ShowBots();
			  cout << endl;

			  // player_choise - 1, because of vector have numeration from 0
			  u_int player_choise = this->GetNumber(
				  "\t\t\t    ������� ����� ������ ����: ",
				  1,
				  gameComponents->VectorOfBots().size()
				  ) - 1;

			  gameComponents->SetPlayer2(gameComponents->VectorOfBots()[player_choise]);
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
		this->ShowSettingsMenu();

		u_int sett_choise = GetNumber("\t\t\t    ������� ����� ������ ����: ", 1, 5);

		switch (sett_choise)
		{
		case 1: // size of field
			this->ShowSizeOfFieldMenu();
			break;			
		case 2: // size of win row
			this->ShowSizeOfWinRowMenu();
			break;			
		case 3: // player 1
			this->ShowChoisePlayer1Menu();
			break;
		case 4: // player 2
			this->ShowChoisePlayer2Menu();
			break;			
		case 5: // back
			return;
		default:
			break;
		}
	}
}

u_int Interface::GetNumber(const std::string& msg, u_int min, u_int max) const 
{
	// for working with cursor
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
	DWORD Written = 0;

	// coordinates of cursor
	COORD coord;

	// retrun
	u_int ret;

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

u_int Interface::MenuSession() const
{	
	while (true)
	{
		system("cls");
		this->ShowMainMenu();

		u_int menu_choise = GetNumber("\t\t\t    ������� ����� ������ ����: ", 1, 5);

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
			this->ShowInfo();
			break;
		case 5: // exit
			return 0;
		default:
			break;
		}
	}
}

void Interface::ShowBotsInfo() const
{
	gameComponents->VectorOfHumans()[0]->Info();
	cout << endl;
	
	u_int width;
	u_int counter = 2;

	auto bots = gameComponents->VectorOfBots();
	for (auto i = bots.begin(); i != bots.end(); ++i, ++counter)
	{
		width = 37 - (*i)->GetPlayerName().size() / 2;
		cout << setw(width) << counter << ". ��� " << (*i)->GetPlayerName() << endl << endl;
		(*i)->Info();
		cout << endl << endl << endl;
	}
}

void Interface::ShowInfo() const
{
	system("cls");
	this->ShowLogo();
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
       	 
	this->ShowBotsInfo();

	// for working with cursor
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	// coordinates of cursor
	COORD coord;
	coord.X = 0; coord.Y = 0;
	SetConsoleCursorPosition(hStdOut, coord);

	cin.get();
}
