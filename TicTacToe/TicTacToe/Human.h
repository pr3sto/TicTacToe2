// Human.h - game player - Human

#ifndef HUMAN_H_
#define HUMAN_H_

#include "player.h"

class HumanPlayer : public Player
{
public:
	HumanPlayer() : Player("Человек") { }
	~HumanPlayer() { }

	virtual COORD Move() { return COORD(); }
};
#endif // HUMAN_H_