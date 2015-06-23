// game.cpp - game itself :/

#include "game.h"

Game::Game()
{
	game_components = new GameComponents();
	game_interface = new Interface(game_components);
}

Game::~Game()
{
	delete game_components;
	delete game_interface;
}

bool Game::Player1Move() const
{
	game_interface->PlayersMoveMenu(1);
	COORD player1_move = game_components->player1()->Move();

	if (!game_components->field()->CheckMove(1, player1_move))
	{
		std::string err = "Wrong move from player";
		std::string func = "bool Game::Player1Move() const, ";
		func +=	"COORD player1_move = game_components->player1()->Move()";
		std::string info = "player1_move = ";
		info += std::to_string(player1_move.X); info += ", "; 
		info += std::to_string(player1_move.Y);
		std::string act = "exit(1)";
		Log::write_log(err, func, info, act);
		exit(1);
	}

	game_interface->ShowPlayerMove(1, player1_move);

	return game_components->field()->CheckForWin(player1_move);
}

bool Game::Player2Move() const
{
	game_interface->PlayersMoveMenu(2);
	COORD player2_move = game_components->player2()->Move();

	if (!game_components->field()->CheckMove(2, player2_move))
	{
		std::string err = "Wrong move from player";
		std::string func = "bool Game::Player2Move() const, ";
		func += "COORD player2_move = game_components->player2()->Move()";
		std::string info = "player2_move = ";
		info += std::to_string(player2_move.X); info += ", ";
		info += std::to_string(player2_move.Y);
		std::string act = "exit(1)";
		Log::write_log(err, func, info, act);
		exit(1);
	}

	game_interface->ShowPlayerMove(2, player2_move);

	return game_components->field()->CheckForWin(player2_move);
}

void Game::Play() const
{
	game_interface->PlayingMenu();

	int max_moves = game_components->field()->size_of_field() *
		game_components->field()->size_of_field();
	int counter_of_moves = 0;

	while (true)
	{
		if (this->Player1Move())
		{
			game_interface->GameOver(1); // player 1 win
			return;
		}
		counter_of_moves++;

		// when there are no free cells 
		if (counter_of_moves == max_moves)
			break;

		if (this->Player2Move())
		{
			game_interface->GameOver(2); // player 2 win
			return;
		}
		counter_of_moves++;
	} 

	game_interface->GameOver(0); // draw
}

void Game::Run() const
{
	// game_interface.MenuSession() - shows menu
	// and return 0 if player wants to exit
	while (game_interface->MenuSession())
	{
		game_components->field()->RefreshField();
		this->Play();
	}
}