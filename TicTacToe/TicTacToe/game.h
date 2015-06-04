// game.h - game itself :/

#ifndef GAME_H_
#define GAME_H_

#include "game_components.h"
#include "interface.h"
#include "log.h"

// object that represent the game
class Game
{
private:
	GameComponents* game_components;
	Interface game_interface;

	// when player set all parametrs
	// it's run game
	void Play() const;

	bool Player1Move() const;
	bool Player2Move() const;

public:
	Game();
	~Game();

	// run programm
	void Run() const;
};

#endif // GAME_H_