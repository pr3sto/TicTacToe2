// game.h - game itself :/

#ifndef GAME_H_
#define GAME_H_

#include "game_components.h"
#include "interface.h"
#include "player.h"

class Game
{
private:
	GameComponents* gameComponents;
	Interface gameInterface;

	void Play() const;
	void Player1Move() const;
	void Player2Move() const;

public:
	Game();
	~Game();

	void Run() const;
};

#endif // GAME_H_