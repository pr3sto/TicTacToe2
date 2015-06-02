// field.cpp - gaming field

#include "field.h"

FieldInfo::FieldInfo()
{
	sizeOfField = 3;
	sizeOfWinRow = 3;
	oldSizeOfField = 3;
	gamingField = nullptr;

	this->NewField();
}

FieldInfo::~FieldInfo()
{
	sizeOfField = oldSizeOfField;
	this->DeleteField();
}

void FieldInfo::NewField()
{
	if (gamingField != nullptr)
		this->DeleteField();

	gamingField = new u_int*[sizeOfField];
	for (u_int i = 0; i < sizeOfField; ++i)
		gamingField[i] = new u_int[sizeOfField];

	for (u_int i = 0; i < sizeOfField; ++i)
	for (u_int j = 0; j < sizeOfField; ++j)
		gamingField[i][j] = 0;
}

void FieldInfo::DeleteField()
{
	for (u_int i = 0; i < oldSizeOfField; ++i)
		delete[] gamingField[i];
	delete[] gamingField;
}

u_int FieldInfo::SizeOfField() const
{ 
	return sizeOfField; 
}

u_int FieldInfo::SizeOfWinRow() const
{ 
	return sizeOfWinRow; 
}

const u_int* FieldInfo::operator[](u_int i) const
{
	return gamingField[i];
}



void Field::SetSizeOfField(u_int new_sz)
{
	if (new_sz < MIN_SIZE_OF_FIEFD || new_sz > MAX_SIZE_OF_FIEFD)
		return;

	oldSizeOfField = sizeOfField;
	sizeOfField = new_sz;

	if (sizeOfField < sizeOfWinRow)
		sizeOfWinRow = MIN_SIZE_OF_WIN_ROW;

	this->NewField();
}

void Field::SetSizeOfWinRow(u_int new_sz)
{
	if (new_sz < MIN_SIZE_OF_WIN_ROW || new_sz > MAX_SIZE_OF_WIN_ROW)
		return;

	sizeOfWinRow = new_sz;

	if (sizeOfWinRow > sizeOfField)
		sizeOfWinRow = MIN_SIZE_OF_WIN_ROW;
}

u_int* Field::operator[](u_int i) const
{
	return gamingField[i];
}

bool Field::VerifyMove(u_int player, COORD move) const
{
	if (move.X < 0 || move.X >= sizeOfField || move.Y < 0 || move.Y >= sizeOfField)
		return false;

	if (gamingField[move.X][move.Y] == 0)
	{
		gamingField[move.X][move.Y] = player;
		return true;
	}
	else
		return false;
}

bool Field::CheckLine(COORD move) const
{
	u_int counter = 0;
	u_int player = gamingField[move.X][move.Y];

	for (u_int i = 0; i < sizeOfField; ++i)
	{
		if (gamingField[i][move.Y] == player) counter++;
		else
		{
			if (counter < sizeOfWinRow) counter = 0;
			else return true;
		}
	}

	return (counter >= sizeOfWinRow ? true : false);
}

bool Field::CheckColumn(COORD move) const
{
	u_int counter = 0;
	u_int player = gamingField[move.X][move.Y];

	for (u_int i = 0; i < sizeOfField; ++i)
	{
		if (gamingField[move.X][i] == player) counter++;
		else
		{
			if (counter < sizeOfWinRow) counter = 0;
			else return true;
		}
	}

	return (counter >= sizeOfWinRow ? true : false);
}

bool Field::CheckLeftToRightDiagonal(COORD move) const
{
	u_int counter = 0;
	u_int player = gamingField[move.X][move.Y];

	COORD position; // start position - upper left corner of diagonal
	position.X = move.X - min(move.X, move.Y);
	position.Y = move.Y - min(move.X, move.Y);

	for (; (position.X < sizeOfField && position.Y < sizeOfField); position.X++, position.Y++)
	{
		if (gamingField[position.X][position.Y] == player) counter++;
		else
		{
			if (counter < sizeOfWinRow) counter = 0;
			else return true;
		}
	}

	return (counter >= sizeOfWinRow ? true : false);
}

bool Field::CheckRightToLeftDiagonal(COORD move) const
{
	u_int counter = 0;
	u_int player = gamingField[move.X][move.Y];

	COORD position; // start position - upper right corner of diagonal
	if (move.X + move.Y <= sizeOfField - 1)
	{
		position.X = move.X + move.Y;
		position.Y = 0;
	}
	else
	{
		position.X = sizeOfField - 1;
		position.Y = move.Y - (sizeOfField - 1 - move.X);
	}

	for (; (position.X >= 0 && position.Y < sizeOfField); position.X--, position.Y++)
	{
		if (gamingField[position.X][position.Y] == player) counter++;
		else
		{
			if (counter < sizeOfWinRow) counter = 0;
			else return true;
		}
	}

	return (counter >= sizeOfWinRow ? true : false);
}

bool Field::VerifyVictory(COORD move) const
{
	return (
		CheckLine(move) ||
		CheckColumn(move) ||
		CheckLeftToRightDiagonal(move) ||
		CheckRightToLeftDiagonal(move)
		);
}

void Field::RefreshField()
{
	this->NewField();
}