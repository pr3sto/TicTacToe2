// Player.cpp - abstract class "Player" for Game Players

#include "player.h"

Player::Player(FieldInfo* _field, std::string _player_name)
{
	if (_field == nullptr)
	{
		std::string err = "Incorrect argument (first)";
		std::string func = "Player::Player(FieldInfo* _field, std::string _player_name)";
		std::string info = "_field = NULL pointer";
		std::string act = "exit(1)";
		Log::write_log(err, func, info, act);
		exit(1);
	}
	if (_player_name.empty())
	{
		std::string err = "Incorrect argument (second)";
		std::string func = "Player::Player(FieldInfo* _field, std::string _player_name)";
		std::string info = "_player_name is empty string";
		std::string act = "Set player_name to 'bot', continue programm";
		Log::write_log(err, func, info, act);
		
		player_name_ = "bot";
		return;
	}

	field = _field;
	player_name_ = _player_name;
	player_index = 0;
}

Player::~Player() 
{ }

std::string Player::player_name() const
{ 
	return player_name_;
}

void Player::set_player_name(std::string new_name)
{
	if (new_name.empty())
	{
		std::string err = "Incorrect argument";
		std::string func = "void Player::set_player_name(std::string new_name)";
		std::string info = "new_name is empty string";
		std::string act = "Exit from function, continue programm";
		Log::write_log(err, func, info, act);
		return;
	}

	// maxlength of player name = 12
	int size_of_name = min(new_name.size(), 12);
	player_name_ = std::string(new_name.begin(), new_name.begin() + size_of_name);
}

void Player::set_index(int _index)
{
	player_index = _index;
}

void Player::Info() const
{
	std::cout << "No info." << std::endl;
}