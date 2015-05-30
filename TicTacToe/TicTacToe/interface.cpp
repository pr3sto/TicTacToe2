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
	// borders
	SetConsoleOutputCP(866);

	char symb_left, symb_right, symb_center;
	u_int sizeOfField = gameComponents->GamingField()->SizeOfField();
	u_int space = (10 - sizeOfField) * 2;

	cout << endl;
	if (sizeOfField < 9)
		cout << endl;
	if (sizeOfField < 7)
		cout << endl;
	if (sizeOfField < 5)
		cout << endl;

	/*
	for (u_int i = 0; i < sizeOfField + 1; ++i)
	{
		if (i == 0) { symb_left = '\xda'; symb_right = '\xbf'; symb_center = '\xc2'; }
		else if (i == sizeOfField) { symb_left = '\xc0'; symb_right = '\xd9'; symb_center = '\xc1'; }
		else { symb_left = '\xc3'; symb_right = '\xb4'; symb_center = '\xc5'; }

		for (u_int j = 0; j < sizeOfField; ++j)
		{
			if (j == 0) cout << setw(36 + space) << symb_left << "\xc4\xc4\xc4";
			if (j == sizeOfField - 1) cout << symb_right;
			else cout << symb_center << "\xc4\xc4\xc4";
		}
		cout << endl;
		if (i != sizeOfField)
		{
			if ((*gameComponents->GamingField())[0][i] == 1) cout << setw(39 + space) << "\xb3 X ";
			else if ((*gameComponents->GamingField())[0][i] == 2) cout << setw(39 + space) << "\xb3 O ";
			else cout << setw(39 + space) << "\xb3   ";

			for (u_int j = 1; j < sizeOfField+1; ++j)
			{
				cout << "\xb3 ";
				if ((*gameComponents->GamingField())[j][i] == 1) cout << "X ";
				else if ((*gameComponents->GamingField())[j][i] == 2) cout << "O ";
				else cout << "  ";
			}

			cout << endl;
		}
	}*/

	SetConsoleOutputCP(1251);

	//symbols
}

void Interface::ShowMainMenu() const 
{
	this->ShowLogo();

	cout << endl;
	cout << setw(46) << "1.   Играть  " << endl << endl;
	cout << setw(46) << "2. Настройки " << endl << endl;
	cout << setw(46) << "3. Статистика" << endl << endl;
	cout << setw(46) << "4.  Об игре  " << endl << endl;
	cout << setw(46) << "5.   Выход   " << endl << endl;
	cout << endl;
}

void Interface::ShowSettingsMenu() const 
{
	this->ShowLogo();

	cout << setw(63) << "Настройки:                " << endl << endl;
	cout << setw(50) << "1. Размер поля            ";
	cout << setw(5) << "(" << gameComponents->GamingField()->SizeOfField() << "x"
		<< gameComponents->GamingField()->SizeOfField() << ")" << endl << endl;
	cout << setw(50) << "2. Размер линии для победы";
	cout << setw(5) << "(" << gameComponents->GamingField()->SizeOfWinRow() << ")" << endl << endl;
	cout << setw(50) << "3. Первый игрок           ";
	cout << setw(5) << "(" << gameComponents->Player1()->GetPlayerName() << ")" << endl << endl;
	cout << setw(50) << "4. Второй игрок           ";
	cout << setw(5) << "(" << gameComponents->Player2()->GetPlayerName() << ")" << endl << endl;

	cout << endl << setw(63) << "5. Назад                  " << endl << endl;
}

void Interface::ShowSizeOfFieldMenu() const
{
	system("cls");
	this->ShowLogo();

	cout << endl << endl << endl
	    << setw(48) << "Минимальный размер:   "
		<< gameComponents->GamingField()->MIN_SIZE_OF_FIEFD 
		<< " x " 
		<< gameComponents->GamingField()->MIN_SIZE_OF_FIEFD
		<< endl << endl;
	cout << setw(47) << "Максимальный размер: "
		<< gameComponents->GamingField()->MAX_SIZE_OF_FIEFD
		<< " x "
		<< gameComponents->GamingField()->MAX_SIZE_OF_FIEFD
		<< endl << endl << endl << endl;
		 
	gameComponents->GamingField()->SetSizeOfField(
		this->GetNumber("\t\t\t    Введите размер поля: ",
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
		<< setw(65) << "Размер линии для победы - это количество фигур," << endl
		<< setw(65) << "выстроенных в  ряд  по  горизонтали, вертикали " << endl
		<< setw(65) << "или диагонли, необходимое для победы.          " << endl
		<< endl << endl

		<< setw(50) << "Минимальный размер:  "
		<< gameComponents->GamingField()->MIN_SIZE_OF_WIN_ROW << endl << endl
		<< setw(50) << "Максимальный размер: "
		<< gameComponents->GamingField()->SizeOfField() << endl << endl << endl;

	gameComponents->GamingField()->SetSizeOfWinRow(
		this->GetNumber("\t\t\tВведите размер линии для победы: ",
			gameComponents->GamingField()->MIN_SIZE_OF_WIN_ROW,
			gameComponents->GamingField()->SizeOfField()
		)
	);
}

void Interface::ShowBots() const
{
	int counter = 1;
	std::vector<Player*> tmp = gameComponents->VectorOfBots();

	for (vecOfPlayersIter i = tmp.begin(); i != tmp.end(); ++i, ++counter)
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
		<< setw(55) << "Первый игрок ходит первым." << endl << endl << endl
		<< setw(53) << "Выберите тип игрока: " << endl << endl
		<< setw(48) << " 1. Человек  " << endl << endl
		<< setw(48) << "2. Компьютер " << endl << endl << endl;
	
	u_int player_choise = this->GetNumber("\t\t\t    Введите номер пункта меню: ", 1, 2);
	switch (player_choise)
	{
	case 1:
		{
			  system("cls");
			  this->ShowLogo();

			  cout << endl << endl << endl << endl << endl;
			  cout << setw(50) << "Введите имя игрока: ";
			  std::string tmp;  cin >> tmp;
			  gameComponents->SetPlayer1(gameComponents->VectorOfHumans()[0]);
			  gameComponents->Player1()->SetPlayerName(tmp);
			  break;
		}
	case 2:
		{
			  system("cls");
			  this->ShowLogo();

			  cout << endl 
				<< setw(50) << "Выберите бота: " << endl << endl;
			  ShowBots();
			  cout << endl;

			  // player_choise - 1, because of vector have numeration from 0
			  u_int player_choise = this->GetNumber(
				  "\t\t\t    Введите номер пункта меню: ",
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
		<< setw(55) << "Второй игрок ходит вторым." << endl << endl << endl
		<< setw(53) << "Выберите тип игрока: " << endl << endl
		<< setw(48) << " 1. Человек  " << endl << endl
		<< setw(48) << "2. Компьютер " << endl << endl << endl;

	u_int player_choise = this->GetNumber("\t\t\t    Введите номер пункта меню: ", 1, 2);
	switch (player_choise)
	{
	case 1:
	{
			  system("cls");
			  this->ShowLogo();

			  cout << endl << endl << endl << endl << endl;
			  cout << setw(50) << "Введите имя игрока: ";
			  std::string tmp;  cin >> tmp;
			  gameComponents->SetPlayer2(gameComponents->VectorOfHumans()[1]);
			  gameComponents->Player2()->SetPlayerName(tmp);
			  break;
	}
	case 2:
	{
			  system("cls");
			  this->ShowLogo();

			  cout << endl
				  << setw(50) << "Выберите бота: " << endl << endl;
			  ShowBots();
			  cout << endl;

			  // player_choise - 1, because of vector have numeration from 0
			  u_int player_choise = this->GetNumber(
				  "\t\t\t    Введите номер пункта меню: ",
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

		u_int sett_choise = GetNumber("\t\t\t    Введите номер пункта меню: ", 1, 5);

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
			cout << "Введите число от " << min << " до " << max << ": ";
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

COORD Interface::GetCoord() const 
{
	COORD ret;
	ret.X = GetNumber("Введите координату x: ", 1, gameComponents->GamingField()->SizeOfField());
	ret.Y = GetNumber("Введите координату Y: ", 1, gameComponents->GamingField()->SizeOfField());
	return ret;
}

u_int Interface::MenuSession() const
{	
	while (true)
	{
		system("cls");
		this->ShowMainMenu();

		u_int menu_choise = GetNumber("\t\t\t    Введите номер пункта меню: ", 1, 5);

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
			//TODO: write info func
			break;
		case 5: // exit
			return 0;
		default:
			break;
		}
	}
}