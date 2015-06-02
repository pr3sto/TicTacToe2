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

bool Game::Player1Move() const
{
	gameInterface.ShowPlayersMoveMenu(1);

	COORD player1Move = gameComponents->Player1()->Move();

	if (!gameComponents->GamingField()->VerifyMove(1, player1Move))
	{
		std::cerr << "Error: wrong move from player: ";
		std::cerr << gameComponents->Player1()->GetPlayerName();
		exit(1);
	}

	gameInterface.ShowPlayerMove(1, player1Move);

	return gameComponents->GamingField()->VerifyVictory(player1Move);
}

bool Game::Player2Move() const
{
	gameInterface.ShowPlayersMoveMenu(2);

	COORD player2Move = gameComponents->Player2()->Move();

	if (!gameComponents->GamingField()->VerifyMove(2, player2Move))
	{
		std::cerr << "Error: wrong move from player: ";
		std::cerr << gameComponents->Player2()->GetPlayerName();
		exit(1);
	}

	gameInterface.ShowPlayerMove(2, player2Move);

	return gameComponents->GamingField()->VerifyVictory(player2Move);
}

void Game::Play() const
{
	gameInterface.ShowPlayingMenu();

	while (true)
	{
		if (this->Player1Move())
		{
			gameInterface.PlayerWin(1);
			break;
		}
		if (this->Player2Move())
		{
			gameInterface.PlayerWin(2);
			break;
		}
	}
}

void Game::Run() const
{
	// gameInterface.MenuSession() - shows menu
	// and return 0 if player wants to exit
	while (gameInterface.MenuSession())
	{
		gameComponents->GamingField()->RefreshField();
		this->Play();
	}
}