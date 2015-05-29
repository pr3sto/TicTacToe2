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

public:
	Game();
	~Game();

	void Run();
};

#endif // GAME_H_