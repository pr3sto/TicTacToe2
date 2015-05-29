// Player.h - abstract class "Player" for Game Players

#ifndef PLAYER_H_
#define PLAYER_H_

#include <string>
#include "windows.h"
#include "field.h"

class Player
{
protected:
	FieldInfo* field;
	std::string playerName;

public:
	Player(FieldInfo* field_, std::string playerName_) :
		field(field_),
		playerName(playerName_) { }
	virtual ~Player() { }

	// getter
	std::string GetPlayerName() const { return playerName; }

	// player's move
	virtual COORD Move() =0;
};

#endif // PLAYER_H_