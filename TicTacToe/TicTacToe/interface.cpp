// interface.cpp - console interface of game

#include "interface.h"

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
	SetConsoleOutputCP(866);
	char symb_left, symb_right, symb_center;
	for (u_int i = 0; i < gameComponents->GamingField()->SizeOfField()+1; ++i)
	{
		if (i == 0) { symb_left = '\xda'; symb_right = '\xbf'; symb_center = '\xc2'; }
		else if (i == gameComponents->GamingField()->SizeOfField()) { symb_left = '\xc0'; symb_right = '\xd9'; symb_center = '\xc1'; }
		else { symb_left = '\xc3'; symb_right = '\xb4'; symb_center = '\xc5'; }

		for (u_int j = 0; j < gameComponents->GamingField()->SizeOfField(); ++j)
		{
			if (j == 0) cout << setw(36) << symb_left << "\xc4\xc4\xc4";
			if (j == gameComponents->GamingField()->SizeOfField() - 1) cout << symb_right;
			else cout << symb_center << "\xc4\xc4\xc4";
		}
		cout << endl;
		if (i != gameComponents->GamingField()->SizeOfField())
		{
			cout << setw(39) << "\xb3   ";
			for (u_int j = 0; j < gameComponents->GamingField()->SizeOfField(); ++j)
				cout << "\xb3   ";

			cout << endl;
		}
	}
	SetConsoleOutputCP(1251);
}

void Interface::ShowMainMenu() const 
{
	this->ShowLogo();

	cout << endl;
	cout << setw(44) << "1. Играть" << endl << endl;
	cout << setw(46) << "2. Настройки" << endl << endl;
	cout << setw(46) << "3. Статистика" << endl << endl;
	cout << setw(45) << "4. Об игре" << endl << endl;
	cout << setw(44) << "5. Выход" << endl << endl;
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

void Interface::ShowSizeOfFieldMenu()
{
	system("cls");
	this->ShowLogo();

	gameComponents->GamingField()->SetSizeOfField(
		this->GetNumber("\t\t\t    Введите размер поля: ",
			gameComponents->GamingField()->MIN_SIZE_OF_FIEFD,
			gameComponents->GamingField()->MAX_SIZE_OF_FIEFD
		)
	);
}

void Interface::ShowSizeOfWinRowMenu()
{
	system("cls");
	this->ShowLogo();

	gameComponents->GamingField()->SetSizeOfWinRow(
		this->GetNumber("\t\t\tВведите размер линии для победы: ",
			gameComponents->GamingField()->MIN_SIZE_OF_WIN_ROW,
			gameComponents->GamingField()->SizeOfField()
		)
	);
}

void Interface::ShowChoisePlayer1Menu()
{
	system("cls");
	this->ShowLogo();

	cout << setw(54) << "Выберите первого игрока: " << endl << endl;

	int counter = 1;
	std::vector<Player*> tmp = gameComponents->VectorOfPlayers();

	for (vecOfPlayersIter i = tmp.begin(); i != tmp.end(); ++i, ++counter)
	{
		u_int width = 40 - (*i)->GetPlayerName().size()/2;
		cout << setw(width) << counter << ". " << (*i)->GetPlayerName() << endl;
	}
	cout << endl;
	
	// player_choise - 1, because of vector have numeration from 0
	u_int player_choise = this->GetNumber("\t\t\t    Введите номер пункта меню: ", 1, tmp.size()) - 1;

	gameComponents->SetPlayer1(gameComponents->VectorOfPlayers()[player_choise]);
}

void Interface::ShowChoisePlayer2Menu()
{
	system("cls");
	this->ShowLogo();

	cout << setw(54) << "Выберите первого игрока: " << endl << endl;

	int counter = 1;
	std::vector<Player*> tmp = gameComponents->VectorOfPlayers();

	for (vecOfPlayersIter i = tmp.begin(); i != tmp.end(); ++i, ++counter)
	{
		u_int width = 40 - (*i)->GetPlayerName().size() / 2;
		cout << setw(width) << counter << ". " << (*i)->GetPlayerName() << endl;
	}
	cout << endl;

	// player_choise - 1, because of vector have numeration from 0
	u_int player_choise = this->GetNumber("\t\t\t    Введите номер пункта меню: ", 1, tmp.size()) - 1;

	gameComponents->SetPlayer2(gameComponents->VectorOfPlayers()[player_choise]);
}
	
void Interface::SettingsMenuSession()
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

u_int Interface::GetNumber(const string& msg, u_int min, u_int max) const 
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

		// set cursor + erase next line
		SetConsoleCursorPosition(hStdOut, coord);
		FillConsoleOutputCharacter(hStdOut, ' ', 80, coord, &Written);
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

u_int Interface::MenuSession()
{	
	while (true)
	{
		system("cls");
		this->ShowMainMenu();

		u_int menu_choise = GetNumber("\t\t\t    Введите номер пункта меню: ", 1, 5);

		switch (menu_choise)
		{
		case 1: // play
			system("cls");
			this->ShowGamingField();
			cin.get();
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