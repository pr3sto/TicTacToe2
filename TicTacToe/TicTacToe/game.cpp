// game.cpp - game itself :/

#include "game.h"

Game::Game()
{
	gameComponents = new GameComponents;
	gameInterface = Interface(gameComponents);
}

Game::~Game()
{
	delete gameComponents;
}

void Game::Run()
{
	u_int play = gameInterface.MenuSession();
	
	if (play)
	{
		system("cls");
		(*gameComponents->GamingField())[0][2] = 2;
		gameInterface.ShowGamingField();
		std::cin.get();
	}
}