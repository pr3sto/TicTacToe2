// Player.h - abstract class "Player" for Game Players

#ifndef PLAYER_H_
#define PLAYER_H_

#include <string>
#include "windows.h"
#include "field.h"
#include <iomanip>

class Player
{
protected:
	FieldInfo* field;
	std::string playerName;

public:
	Player(FieldInfo* field_, std::string playerName_);
	virtual ~Player();

	// getter
	std::string GetPlayerName() const;

	// setter
	void SetPlayerName(std::string playerName_);

	// player's move
	virtual COORD Move() const =0;

	virtual void Info() const;
};

#endif // PLAYER_H_