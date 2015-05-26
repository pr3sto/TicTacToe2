// game_parametrs.h - game components 

#ifndef GAME_PARAMETRS_H_
#define GAME_PARAMETRS_H_

#include <memory> // std::shared_ptr
#include <vector>
#include "windows.h"
#include "Player.h"
#include "Human.h"

using std::vector;

class GameComponents;

typedef std::shared_ptr<GameComponents> GameComponentsPtr;
typedef std::shared_ptr<Player> PlayerPtr;
typedef vector<PlayerPtr>::iterator vecOfPlayersIter;

// all players (human + bots)
class Players
{
private:
	vector<PlayerPtr> players;

	void CreateVectorOfBots()
	{
		//TODO: add bots - just push it :/
		players.push_back(PlayerPtr(new HumanPlayer));
	}

public:
	Players() { CreateVectorOfBots(); }
	
	//getter
	vector<PlayerPtr> GetPlayers() const { return players; }
};

class GameComponents 
{
private:
	u_int** gamingField; 
	u_int sizeOfField;
	u_int oldSizeOfField; 
	u_int sizeOfWinRow;

	PlayerPtr player1;
	PlayerPtr player2;

public:
	GameComponents();
	~GameComponents() { oldSizeOfField = sizeOfField;  this->DeleteField(); }
	
	// vector of all players (human + bots)
	Players vectorOfPlayers;

	const u_int MAX_SIZE_OF_FIEFD = 10;
	const u_int MIN_SIZE_OF_FIEFD = 3;
	const u_int MAX_SIZE_OF_WIN_ROW = 10;
	const u_int MIN_SIZE_OF_WIN_ROW = 3;

	// getters
	u_int** Field() const { return gamingField; }
	u_int SizeOfField() const { return sizeOfField; }
	u_int SizeOfWinRow() const { return sizeOfWinRow; }
	PlayerPtr Player1() const { return player1; }
	PlayerPtr Player2() const { return player2; }

	// setters
	void SetSizeOfField(u_int);
	void SetSizeOfWinRow(u_int);
	void SetPlayer1(PlayerPtr player1_) { player1 = player1_; }
	void SetPlayer2(PlayerPtr player2_) { player1 = player2_; }

	void NewField();
	void DeleteField();
	void RefreshOldSizeOfField() { oldSizeOfField = sizeOfField; }
};

#endif // GAME_PARAMETRS_H_