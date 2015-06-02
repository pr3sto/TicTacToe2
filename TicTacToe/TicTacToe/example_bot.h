// example_bot.h - example bot

#ifndef EXAMPLE_BOT_H_
#define EXAMPLE_BOT_H_

#include "player.h"
#include <random>
#include <vector>

class ExampleBot : public Player
{
public:
	ExampleBot(FieldInfo* field_);
	~ExampleBot();

	virtual COORD Move() const;
	virtual void Info() const;
};
#endif // EXAMPLE_BOT_H_