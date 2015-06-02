// game_parametrs.h - game components 

#ifndef GAME_PARAMETRS_H_
#define GAME_PARAMETRS_H_

#include <memory> // std::shared_ptr
#include <vector>
#include "windows.h"
#include "field.h"
#include "player.h"
#include "human.h"
#include "example_bot.h"


// all players (human + bots)
class Players
{
private:
	std::vector<Player*> humans;
	std::vector<Player*> bots;

public:
	Players();
	Players(FieldInfo*);
	~Players();
	
	//getter
	std::vector<Player*> GetBots() const;
	std::vector<Player*> GetHumans() const;
};

class GameComponents 
{
private:
	Field* field;
	Players* players;  // vector of pointers to all players
	Player* player1; // pointer to player 1
	Player* player2; // pointer to player 2

public:
	GameComponents();
	~GameComponents();

	// getters
	Player* Player1() const;
	Player* Player2() const;
	Field* GamingField() const;
	std::vector<Player*> VectorOfBots() const;
	std::vector<Player*> VectorOfHumans() const;

	// setters
	void SetPlayer1(Player* player1_);
	void SetPlayer2(Player* player2_);
};

#endif // GAME_PARAMETRS_H_