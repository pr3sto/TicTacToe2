// game_parametrs.h - parametrs of game

#ifndef GAME_PARAMETRS_H_
#define GAME_PARAMETRS_H_

#include <memory> // std::shared_ptr
#include "windows.h"

class GameParametrs;

typedef std::shared_ptr<GameParametrs> GameParamsPtr;


enum gameMod_ {
	playerVsPlayer,
	playerVsComputer,
	computerVsComputer
};

enum complexity_ {
	easy,
	medium,
	hard
};

enum playerSymbol_ {
	x,
	o
};


class GameParametrs 
{
private:
	u_int** gamingField; 
	u_int sizeOfField;
	u_int oldSizeOfField; 
	u_int sizeOfWinRow;

	gameMod_ gameMod;
	complexity_ complexity;
	playerSymbol_ playerSymbol;

public:
	GameParametrs();
	~GameParametrs() { DeleteField(); }

	const u_int MAX_SIZE_OF_FIEFD = 30;
	const u_int MIN_SIZE_OF_FIEFD = 3;
	const u_int MAX_SIZE_OF_WIN_ROW = 30;
	const u_int MIN_SIZE_OF_WIN_ROW = 3;

	// getters
	u_int** Field() const { return gamingField; }
	u_int SizeOfField() const { return sizeOfField; }
	u_int SizeOfWinRow() const { return sizeOfWinRow; }
	gameMod_ GameMod() const { return gameMod; }
	complexity_ Complexity() const { return complexity; }
	playerSymbol_ PlayerSymbol() const { return playerSymbol; }

	// setters
	void SetSizeOfField(u_int);
	void SetSizeOfWinRow(u_int);
	void SetGameMod(gameMod_ mod) { gameMod = mod; }
	void SetComplexity(complexity_ compl) { complexity = compl; }
	void SetPlayerSymbol(playerSymbol_ symb) { playerSymbol = symb; }

	void NewField();
	void DeleteField();
	void RefreshOldSizeOfField() { oldSizeOfField = sizeOfField; }
};

#endif // GAME_PARAMETRS_H_