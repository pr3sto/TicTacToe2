// Player.cpp - abstract class "Player" for Game Players

#include "player.h"

Player::Player(FieldInfo* field_, std::string playerName_)
{
	field = field;
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

	playerName = playerName_;
}