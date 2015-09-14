// Player.h - abstract class "Player" for Game Players

#ifndef PLAYER_H_
#define PLAYER_H_

#include <iostream>
#include <iomanip>
#include <string>
#include "field.h"

// abstract class for all bots
class Player
{
protected:
	FieldInfo* field;
	std::string player_name_; // maxlength of player name = 12
	int player_index;         // index number of player

public:
	Player(FieldInfo* _field, std::string _player_name);
	virtual ~Player();

	// getter
	std::string player_name() const;

	// setter
	void set_player_name(std::string new_name);
	void set_index(int _index);

	// player's move
	virtual COORD Move() =0;

	// Info about this bot
	virtual void Info() const;
};

#endif // PLAYER_H_