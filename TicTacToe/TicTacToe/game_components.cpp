// game_parametrs.h - game components 

#include "game_components.h"

Players::Players()
{ }

Players::Players(FieldInfo* field_)
{
	if (field_ == nullptr)
	{
		std::cerr << "Can't create Players because FieldInfo pointer is nullptr." << std::endl;
		exit(1);
	}

	humans.push_back(new HumanPlayer(field_, "Игрок 1")); // human for player1
	humans.push_back(new HumanPlayer(field_, "Игрок 2")); // human for player2

	//TODO: add bots - just push it :/
	bots.push_back(new HumanPlayer(field_, "Example"));
}

Players::~Players()
{
	for (vecOfPlayersIter i = humans.begin(); i != humans.end(); ++i)
		delete (*i);

	for (vecOfPlayersIter i = bots.begin(); i != bots.end(); ++i)
		delete (*i);
}

std::vector<Player*> Players::GetBots() const
{ 
	return bots; 
}

std::vector<Player*> Players::GetHumans() const
{
	return humans;
}




GameComponents::GameComponents()
{
	field = new Field();
	players = new Players(field);
	player1 = players->GetHumans()[0];
	player2 = players->GetHumans()[1];
}

GameComponents::~GameComponents()
{
	delete field;
	delete players;
}

Player* GameComponents::Player1() const
{ 
	return player1; 
}

Player* GameComponents::Player2() const 
{ 
	return player2; 
}

Field* GameComponents::GamingField() const 
{ 
	return field; 
}

std::vector<Player*> GameComponents::VectorOfBots() const 
{ 
	return players->GetBots();
}

std::vector<Player*> GameComponents::VectorOfHumans() const
{
	return players->GetHumans();
}

void GameComponents::SetPlayer1(Player* player1_)
{
	if (player1_ != nullptr) 
		player1 = player1_;
}

void GameComponents::SetPlayer2(Player* player2_)
{
	if (player2_ != nullptr) 
		player2 = player2_;
}