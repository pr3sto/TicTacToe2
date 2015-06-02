// Player.cpp - abstract class "Player" for Game Players

#include "player.h"

Player::Player(FieldInfo* field_, std::string playerName_)
{
	field = field_;
	playerName = playerName_;
}

Player::~Player() 
{ }

std::string Player::GetPlayerName() const
{ 
	return playerName; 
}

void Player::SetPlayerName(std::string playerName_)
{
	if (playerName_.empty())
		return;

	// maxlength of player name = 12
	u_int tmp = min(playerName_.size(), 12);
	playerName = std::string(playerName_.begin(), playerName_.begin() + tmp);
}

void Player::Info() const
{
	std::cout << "No info." << std::endl;
}