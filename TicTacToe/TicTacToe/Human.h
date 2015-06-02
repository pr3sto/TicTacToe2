// human.h - game player - Human

#ifndef HUMAN_H_
#define HUMAN_H_

#include "player.h"

class HumanPlayer : public Player
{
public:
	HumanPlayer(FieldInfo* field_, std::string playerName_);
	~HumanPlayer();

	virtual COORD Move() const;
	virtual void Info() const;
};
#endif // HUMAN_H_