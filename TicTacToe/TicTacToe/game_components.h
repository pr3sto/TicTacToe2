// game_parametrs.h - game components 

#ifndef GAME_PARAMETRS_H_
#define GAME_PARAMETRS_H_

#include <vector>
#include "field.h"      // gaming field
#include "player.h"     // Player bot
#include "human.h"      // Human bot
#include "statistics.h" // statistics about players

// add your bot here
#include "example_bot.h" // is's an example
#include "my_bot.h"


// all players (human + bots)
class Players
{
private:
	std::vector<Player*> humans_;
	std::vector<Player*> bots_;

public:
	Players();
	Players(FieldInfo*);
	~Players();
	
	//getter
	std::vector<Player*> bots() const;
	std::vector<Player*> humans() const;
};



// components of the game in one class
class GameComponents 
{
private:
	Field* field_;     // gaming field
	Players* players;  // bots
	Player* player1_;  // pointer to player 1
	Player* player2_;  // pointer to player 2

	Statistics stats;  // statistics about players

public:
	GameComponents();
	~GameComponents();

	// getters
	Player* player1() const;
	Player* player2() const;
	Field* field() const;
	std::vector<Player*> vector_of_bots() const;
	std::vector<Player*> vector_of_humans() const;

	// setters
	void set_player1(Player* _player1);
	void set_player2(Player* _player2);
	
	// stats
	void ShowStatistics() const;
	void SaveStatistics() const;
	void AddStatistics(std::string player1_name,            
					   std::string player2_name, 
					   Statistics::results player1_result);
};

#endif // GAME_PARAMETRS_H_