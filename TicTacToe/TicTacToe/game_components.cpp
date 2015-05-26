// game_parametrs.cpp - game components 

#include "game_components.h"

GameComponents::GameComponents() 
{
	oldSizeOfField = 3;
	sizeOfField = 3;
	sizeOfWinRow = 3;
	gamingField = nullptr;

	// Humans
	player1 = vectorOfPlayers.GetPlayers()[0];
	player2 = vectorOfPlayers.GetPlayers()[0];

	this->NewField();
}

void GameComponents::NewField() 
{
	if (gamingField != nullptr)
		this->DeleteField();

	gamingField = new u_int*[sizeOfField];
	for (u_int i = 0; i < sizeOfField; i++)
		gamingField[i] = new u_int[sizeOfField];

	for (u_int i = 0; i < sizeOfField; i++)
		for (u_int j = 0; j < sizeOfField; j++)
			gamingField[i][j] = 0;
}

void GameComponents::DeleteField() 
{
	for (u_int i = 0; i < oldSizeOfField; i++)
		delete[] gamingField[i];
	delete[] gamingField;
}

void GameComponents::SetSizeOfField(u_int new_sz) 
{
	if (new_sz < MIN_SIZE_OF_FIEFD || new_sz > MAX_SIZE_OF_FIEFD)
		return;

	oldSizeOfField = sizeOfField;
	sizeOfField = new_sz;

	if (sizeOfField < sizeOfWinRow)
		sizeOfWinRow = MIN_SIZE_OF_WIN_ROW;

	this->NewField();
}

void GameComponents::SetSizeOfWinRow(u_int new_sz) 
{
	if (new_sz < MIN_SIZE_OF_WIN_ROW || new_sz > MAX_SIZE_OF_WIN_ROW)
		return;

	sizeOfWinRow = new_sz;

	if (sizeOfWinRow > sizeOfField)
		sizeOfWinRow = MIN_SIZE_OF_WIN_ROW;
}