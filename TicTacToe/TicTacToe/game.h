// game.h - game itself :/

#ifndef GAME_H_
#define GAME_H_

#include <memory> // std::shared_ptr
#include "game_parametrs.h"
#include "interface.h"

class Game
{
private:
	GameParamsPtr gameParams;
	Interface gameInterface;

public:
	Game() 
	{
		gameParams = GameParamsPtr(new GameParametrs);
		gameInterface = Interface(gameParams);
	}
	~Game();

	void Run();
};

#endif // GAME_H_