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
	gameInterface.MenuSession();
}