// Player.cpp - abstract class "Player" for Game Players

#include "player.h"

Player::Player(FieldInfo* _field, std::string _player_name)
{
	field = _field;
	player_name_ = _player_name;
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
		return;

	// maxlength of player name = 12
	int size_of_name = min(new_name.size(), 12);
	player_name_ = std::string(new_name.begin(), new_name.begin() + size_of_name);
}

void Player::Info() const
{
	std::cout << "No info." << std::endl;
}