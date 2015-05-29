// human.h - game player - Human

#ifndef HUMAN_H_
#define HUMAN_H_

#include "player.h"

class HumanPlayer : public Player
{
public:
	HumanPlayer(FieldInfo* field_);
	~HumanPlayer();

	virtual COORD Move();
};
#endif // HUMAN_H_