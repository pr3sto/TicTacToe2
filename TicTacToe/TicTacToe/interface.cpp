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
	ShowLogo();

	cout << setw(44) << "1. ������" << endl << endl;
	cout << setw(46) << "2. ���������" << endl << endl;
	cout << setw(46) << "3. ����������" << endl << endl;
	cout << setw(45) << "4. �� ����" << endl << endl;
	cout << setw(44) << "5. �����" << endl << endl;
}

void Interface::ShowSettingsMenu() const 
{
	ShowLogo();

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

void Interface::ShowGameModMenu() const 
{
	ShowLogo();

	cout << setw(49) << "1. ����� vs �����" << endl << endl;
	cout << setw(51) << "2. ����� vs ���������" << endl << endl;
	cout << setw(53) << "3. ��������� vs ���������" << endl << endl;
}

void Interface::ShowComplexityMenu() const 
{
	ShowLogo();

	cout << setw(44) << "1. �����" << endl << endl;
	cout << setw(45) << "2. ������" << endl << endl;
	cout << setw(45) << "3. ������" << endl << endl;
}

void Interface::ShowSymbolMenu() const 
{
	ShowLogo();

	cout << setw(42) << "1. X" << endl << endl;
	cout << setw(42) << "2. O" << endl << endl;
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
	ret.X = GetNumber("������� ���������� x: ", 0, gameParams->SizeOfField());
	ret.Y = GetNumber("������� ���������� Y: ", 0, gameParams->SizeOfField());
	return ret;
}