// game_parametrs.cpp - parametrs of game

#include "game_parametrs.h"

GameParametrs::GameParametrs() 
{
	oldSizeOfField = 3;
	sizeOfField = 3;
	sizeOfWinRow = 3;
	gameMod = playerVsComputer;
	complexity = medium;
	playerSymbol = x;
	gamingField = nullptr;

	NewField();
}

void GameParametrs::NewField() 
{
	if (gamingField != nullptr)
		DeleteField();

	gamingField = new u_int*[sizeOfField];
	for (u_int i = 0; i < sizeOfField; i++)
		gamingField[i] = new u_int[sizeOfField];

	for (u_int i = 0; i < sizeOfField; i++)
		for (u_int j = 0; j < sizeOfField; j++)
			gamingField[i][j] = 0;
}

void GameParametrs::DeleteField() 
{
	for (u_int i = 0; i < oldSizeOfField; i++)
		delete[] gamingField[i];
	delete[] gamingField;
}

void GameParametrs::SetSizeOfField(u_int new_sz) 
{
	if (new_sz < MIN_SIZE_OF_FIEFD || new_sz > MAX_SIZE_OF_FIEFD)
		return;

	oldSizeOfField = sizeOfField;
	sizeOfField = new_sz;

	if (sizeOfField < sizeOfWinRow)
		sizeOfWinRow = MIN_SIZE_OF_WIN_ROW;

	NewField();
}

void GameParametrs::SetSizeOfWinRow(u_int new_sz) 
{
	if (new_sz < MIN_SIZE_OF_WIN_ROW || new_sz > MAX_SIZE_OF_WIN_ROW)
		return;

	sizeOfWinRow = new_sz;

	if (sizeOfWinRow > sizeOfField)
		sizeOfWinRow = MIN_SIZE_OF_WIN_ROW;
}