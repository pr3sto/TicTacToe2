// game_parametrs.h - game components 

#include "game_components.h"

Players::Players()
{ }

Players::Players(FieldInfo* field_)
{
	humans_.push_back(new HumanPlayer(field_, "Игрок 1")); // human for player1
	humans_.push_back(new HumanPlayer(field_, "Игрок 2")); // human for player2

	//TODO: add bots - just push it :/
	bots_.push_back(new ExampleBot(field_)); // it's an example
}

Players::~Players()
{
	for (auto i = humans_.begin(); i != humans_.end(); ++i)
		delete (*i);

	for (auto i = bots_.begin(); i != bots_.end(); ++i)
		delete (*i);
}

std::vector<Player*> Players::bots() const
{ 
	return bots_; 
}

std::vector<Player*> Players::humans() const
{
	return humans_;
}



GameComponents::GameComponents()
{
	field_ = new Field();
	players = new Players(field_);
	player1_ = players->humans()[0];
	player2_ = players->humans()[1];
}

GameComponents::~GameComponents()
{
	delete field_;
	delete players;
}

Player* GameComponents::player1() const
{ 
	return player1_; 
}

Player* GameComponents::player2() const 
{ 
	return player2_; 
}

Field* GameComponents::field() const 
{ 
	return field_; 
}

std::vector<Player*> GameComponents::vector_of_bots() const
{ 
	return players->bots();
}

std::vector<Player*> GameComponents::vector_of_humans() const
{
	return players->humans();
}

void GameComponents::set_player1(Player* _player1)
{
	if (_player1 != nullptr) 
		player1_ = _player1;
}

void GameComponents::set_player2(Player* _player2)
{
	if (_player2 != nullptr)
		player2_ = _player2;
}