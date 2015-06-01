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

void Game::Player1Move() const
{
	gameInterface.ShowPlayingMenu(1);
	COORD player1Move = gameComponents->Player1()->Move();

	if (!gameComponents->GamingField()->VerifyMove(1, player1Move))
	{
		std::cerr << "Error: wrong move from player: ";
		std::cerr << gameComponents->Player1()->GetPlayerName();
		exit(1);
	}

	gameInterface.ShowPlayerMove(1, player1Move);

	if (gameComponents->GamingField()->VerifyVictory(player1Move))
	{
		std::cout << "онаедю";
		std::cin.get();
	}
}

void Game::Player2Move() const
{
	gameInterface.ShowPlayingMenu(2);
	COORD player2Move = gameComponents->Player2()->Move();

	if (!gameComponents->GamingField()->VerifyMove(2, player2Move))
	{
		std::cerr << "Error: wrong move from player: ";
		std::cerr << gameComponents->Player2()->GetPlayerName();
		exit(1);
	}

	gameInterface.ShowPlayerMove(2, player2Move);

	if (gameComponents->GamingField()->VerifyVictory(player2Move))
	{
		std::cout << "онаедю";
		std::cin.get();
	}
}

void Game::Play() const
{
	while (true)
	{
		this->Player1Move();
		this->Player2Move();
	}
}

void Game::Run() const
{
	u_int play = gameInterface.MenuSession();
	
	if (play)
	{
		system("cls");
		this->Play();
	}
}