// example_bot.h - example bot

#ifndef EXAMPLE_BOT_H_
#define EXAMPLE_BOT_H_

#include <random>
#include <vector>
#include "player.h"

// bot, that moves randomly
class ExampleBot : public Player
{
public:
	ExampleBot(FieldInfo* _field);
	~ExampleBot();

	virtual COORD Move() const;
	virtual void Info() const;
};
#endif // EXAMPLE_BOT_H_