// game.h - game itself :/

#ifndef GAME_H_
#define GAME_H_

#include "game_components.h"
#include "interface.h"
#include "player.h"

class Game
{
private:
	GameComponentsPtr gameComponents;
	Interface gameInterface;

public:
	Game() 
	{
		gameComponents = GameComponentsPtr(new GameComponents);
		gameInterface = Interface(gameComponents);
	}
	~Game() {}

	void Run();
	void Refresh();
};

#endif // GAME_H_