// my_bot.h - bot

#ifndef MY_BOT_H_
#define MY_BOT_H_

#include "player.h"

// bot
class MyBot : public Player
{
public:
	MyBot(FieldInfo* _field);
	~MyBot();

	virtual COORD Move() const;
	virtual void Info() const;
};

#endif // MY_BOT_H_