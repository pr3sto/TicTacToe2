// interface.cpp - console interface of game

#include "interface.h"

void Interface::ShowLogo() const 
{
	cout << endl;
	cout << setw(60) << "OOO   O                        XXX   " << endl;
	cout << setw(60) << " OO  OO                      XX   XX " << endl;
	cout << setw(60) << "  OOO     XX    XX   OOOO   X    X  X" << endl;
	cout << setw(60) << "   OOO     XX  XX   OO      X  X    X" << endl;
	cout << setw(60) << " OO  OO     X X       OO     XX   XX " << endl;
	cout << setw(60) << " O   OOO     X     OOOO        XXX   " << endl;
	cout << endl;
}

void Interface::ShowGamingField() const
{

}

void Interface::ShowMainMenu() const 
{
	this->ShowLogo();

	cout << setw(44) << "1. ������" << endl << endl;
	cout << setw(46) << "2. ���������" << endl << endl;
	cout << setw(46) << "3. ����������" << endl << endl;
	cout << setw(45) << "4. �� ����" << endl << endl;
	cout << setw(44) << "5. �����" << endl << endl;
}

void Interface::ShowSettingsMenu() const 
{
	this->ShowLogo();

	cout << setw(63) << "���������:                " << endl << endl;
	cout << setw(50) << "1. ������ ����            ";
	cout << setw(5) << "(" << gameParams->SizeOfField() << "x" << gameParams->SizeOfField() << ")" << endl << endl;
	cout << setw(50) << "2. ������ ����� ��� ������";
	cout << setw(5) << "(" << gameParams->SizeOfWinRow() << ")" << endl << endl;
	cout << setw(50) << "3. ����� ����             ";
	cout << setw(5) << "(";
	if (gameParams->GameMod() == playerVsPlayer) cout << "����� vs �����";
	if (gameParams->GameMod() == playerVsComputer) cout << "����� vs ����.";
	if (gameParams->GameMod() == computerVsComputer) cout << "����. vs ����.";
	cout << ")" << endl << endl;
	cout << setw(50) << "4. ���������              ";
	cout << setw(5) << "(";
	if (gameParams->Complexity() == easy)   cout << "�����";
	if (gameParams->Complexity() == medium) cout << "������";
	if (gameParams->Complexity() == hard)   cout << "������";
	cout << ")" << endl << endl;
	cout << setw(50) << "5. ������                 ";
	cout << setw(5) << "(";
	if (gameParams->PlayerSymbol() == x) cout << "X";
	if (gameParams->PlayerSymbol() == o) cout << "O";
	cout << ")" << endl << endl;

	cout << endl << setw(63) << "6. �����                  " << endl << endl;
}

void Interface::ShowSizeOfFieldMenu()
{
	system("cls");
	this->ShowLogo();

	gameParams->SetSizeOfField(
		this->GetNumber("\t\t\t    ������� ������ ����: ",
		gameParams->MIN_SIZE_OF_FIEFD, gameParams->MAX_SIZE_OF_FIEFD)
	);
}

void Interface::ShowSizeOfWinRowMenu()
{
	system("cls");
	this->ShowLogo();

	gameParams->SetSizeOfWinRow(
		this->GetNumber("\t\t\t������� ������ ����� ��� ������: ",
		gameParams->MIN_SIZE_OF_WIN_ROW, gameParams->SizeOfField())
	);
}

void Interface::ShowGameModMenu()  
{
	system("cls");
	this->ShowLogo();

	cout << setw(49) << "1. ����� vs �����" << endl << endl;
	cout << setw(51) << "2. ����� vs ���������" << endl << endl;
	cout << setw(53) << "3. ��������� vs ���������" << endl << endl;

	u_int mod_choise = this->GetNumber("\t\t\t    ������� ����� ������ ����: ", 1, 3);
	switch (mod_choise)
	{
	case 1:
		gameParams->SetGameMod(playerVsPlayer);
		break;
	case 2:
		gameParams->SetGameMod(playerVsComputer);
		break;
	case 3:
		gameParams->SetGameMod(computerVsComputer);
		break;
	default:
		gameParams->SetGameMod(playerVsComputer);
		break;
	}
}

void Interface::ShowComplexityMenu()  
{
	system("cls");
	this->ShowLogo();

	cout << setw(44) << "1. �����" << endl << endl;
	cout << setw(45) << "2. ������" << endl << endl;
	cout << setw(45) << "3. ������" << endl << endl;

	u_int compl_choise = this->GetNumber("\t\t\t    ������� ����� ������ ����: ", 1, 3);
	switch (compl_choise) 
	{
	case 1:
		gameParams->SetComplexity(easy);
		break;
	case 2:
		gameParams->SetComplexity(medium);
		break;
	case 3: 
		gameParams->SetComplexity(hard);
		break;
	default:
		gameParams->SetComplexity(medium);
		break;
	}
}

void Interface::ShowSymbolMenu() 
{
	system("cls");
	this->ShowLogo();

	cout << setw(42) << "1. X" << endl << endl;
	cout << setw(42) << "2. O" << endl << endl;

	u_int symb_choise = this->GetNumber("\t\t\t    ������� ����� ������ ����: ", 1, 2);
	switch (symb_choise) 
	{
	case 1: 
		gameParams->SetPlayerSymbol(x);
		break;
	case 2: 
		gameParams->SetPlayerSymbol(o);
		break;
	default:
		gameParams->SetPlayerSymbol(x);
		break;
	}
}

void Interface::SettingsMenuSession()
{
	while (true)
	{
		system("cls");
		this->ShowSettingsMenu();

		u_int sett_choise = GetNumber("\t\t\t    ������� ����� ������ ����: ", 1, 6);

		switch (sett_choise)
		{
		case 1: // size of field
			this->ShowSizeOfFieldMenu();
			break;			
		case 2: // size of win row
			this->ShowSizeOfWinRowMenu();
			break;			
		case 3: // game mod
			this->ShowGameModMenu();
			break;
		case 4: // complexity
			this->ShowComplexityMenu();
			break;			
		case 5: // players symbol
			this->ShowSymbolMenu();
			break;
		case 6: // back
			return;
		default:
			break;
		}
	}
}

u_int Interface::GetNumber(string msg, u_int min, u_int max) const 
{
	// ����������, ����������� ��� ������ � �������� � �������
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
	DWORD Written = 0;

	// ���������� �������
	COORD coord;

	// ������������ �����
	u_int ret;

	while (true) 
	{
		cout << msg;

		// �������� ������� ����������
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

		// ���������� ������, � ������� ���������� �������
		SetConsoleCursorPosition(hStdOut, coord);
		FillConsoleOutputCharacter(hStdOut, ' ', 80, coord, &Written);
	}

	return ret;
}

COORD Interface::GetCoord() const 
{
	COORD ret;
	ret.X = GetNumber("������� ���������� x: ", 1, gameParams->SizeOfField());
	ret.Y = GetNumber("������� ���������� Y: ", 1, gameParams->SizeOfField());
	return ret;
}

u_int Interface::MenuSession()
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
			//TODO: write info func
			break;
		case 5: // exit
			return 0;
		default:
			break;
		}
	}
}