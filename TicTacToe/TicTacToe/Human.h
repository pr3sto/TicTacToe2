// human.h - game player - Human

#ifndef HUMAN_H_
#define HUMAN_H_

#include "player.h"

// class for Humans - input data from human
class HumanPlayer : public Player
{
public:
	HumanPlayer(FieldInfo* _field, std::string _player_name);
	~HumanPlayer();

	virtual COORD Move() const;
	virtual void Info() const;
};
#endif // HUMAN_H_