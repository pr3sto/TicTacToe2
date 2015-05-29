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

	//TODO: add bots - just push it :/
	players.push_back(new HumanPlayer(field_));
}

Players::~Players()
{
	for (vecOfPlayersIter i = players.begin(); i != players.end(); ++i)
		delete (*i);
}

std::vector<Player*> Players::GetPlayers() const
{ 
	return players; 
}



GameComponents::GameComponents()
{
	field = new Field();
	players = new Players(field);
	player1 = players->GetPlayers()[0];
	player2 = players->GetPlayers()[0];
}

GameComponents::~GameComponents()
{
	delete field;
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

std::vector<Player*> GameComponents::VectorOfPlayers() const 
{ 
	return players->GetPlayers(); 
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