// game_parametrs.h - game components 

#include "game_components.h"

Players::Players()
{ }

Players::Players(FieldInfo* field_)
{
	if (field_ == nullptr)
	{
		std::string err = "Incorrect argument";
		std::string func = "Players::Players(FieldInfo* field_)";
		std::string info = "field_ = NULL pointer";
		std::string act = "exit(1)";
		Log::write_log(err, func, info, act);
		exit(1);
	}

	humans_.push_back(new HumanPlayer(field_, "Игрок 1")); // human for player1
	humans_.push_back(new HumanPlayer(field_, "Игрок 2")); // human for player2

	//TODO: add bots - just push it :/
	bots_.push_back(new ExampleBot(field_)); // it's an example
	bots_.push_back(new MyBot(field_));
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
	if (_player1 == nullptr)
	{
		std::string err = "Incorrect argument";
		std::string func = "void GameComponents::set_player1(Player* _player1)";
		std::string info = "_player1 = NULL pointer";
		std::string act = "Exit from function, continue programm";
		Log::write_log(err, func, info, act);
		return;
	}
	else
	{
		player1_ = _player1;
	}
}

void GameComponents::set_player2(Player* _player2)
{
	if (_player2 == nullptr)
	{
		std::string err = "Incorrect argument";
		std::string func = "void GameComponents::set_player2(Player* _player2)";
		std::string info = "_player2 = NULL pointer";
		std::string act = "Exit from function, continue programm";
		Log::write_log(err, func, info, act);
		return;
	}
	else
	{
		player2_ = _player2;
	}
}

void GameComponents::ShowStatistics() const
{
	stats.Show();
}

void GameComponents::SaveStatistics() const
{
	stats.Save();
}

void GameComponents::AddStatistics(
	std::string player1_name,
	std::string player2_name,
	Statistics::results player1_result)
{
	switch (player1_result)
	{
	case Statistics::WIN:
		stats.AddStatistics(player1_name, Statistics::WIN);
		stats.AddStatistics(player2_name, Statistics::LOSS);
		break;
	case Statistics::LOSS:
		stats.AddStatistics(player1_name, Statistics::LOSS);
		stats.AddStatistics(player2_name, Statistics::WIN);
		break;
	case Statistics::DRAW:
		stats.AddStatistics(player1_name, Statistics::DRAW);
		stats.AddStatistics(player2_name, Statistics::DRAW);
		break;
	default:
		break;
	}
}