// main.cpp - main file of project

#include "game.h"
#include "windows.h" // for language

int main()
{
	// Russian language
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	// initialisation
	Game game;

	// start game
	game.Run();

	return 0;
}