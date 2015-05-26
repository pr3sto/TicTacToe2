// Player.h - abstract class "Player" for Game Players

#ifndef PLAYER_H_
#define PLAYER_H_

#include <string>
#include "windows.h"

using std::string;

class Player
{
private:
	string playerName;

public:
	Player(string playerName_) : playerName(playerName_) { }
	virtual ~Player() { }

	// getter
	string GetPlayerName() { return playerName; }

	// player's move
	virtual COORD Move() =0;
};

#endif // PLAYER_H_