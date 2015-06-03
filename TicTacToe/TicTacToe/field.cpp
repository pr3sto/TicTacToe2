// field.cpp - gaming field

#include "field.h"

FieldInfo::FieldInfo()
{
	size_of_field_ = 3;
	size_of_win_row_ = 3;
	old_size_of_field_ = 3;
	gaming_field_ = nullptr;

	this->NewField();
}

FieldInfo::~FieldInfo()
{
	size_of_field_ = old_size_of_field_;
	this->DeleteField();
}

void FieldInfo::NewField()
{
	if (gaming_field_ != nullptr)
		this->DeleteField();

	gaming_field_ = new int*[size_of_field_];
	for (int i = 0; i < size_of_field_; ++i)
		gaming_field_[i] = new int[size_of_field_];

	for (int i = 0; i < size_of_field_; ++i)
		for (int j = 0; j < size_of_field_; ++j)
			gaming_field_[i][j] = 0;
}

void FieldInfo::DeleteField()
{
	for (int i = 0; i < old_size_of_field_; ++i)
		delete[] gaming_field_[i];
	delete[] gaming_field_;
}

int FieldInfo::size_of_field() const
{ 
	return size_of_field_;
}

int FieldInfo::size_of_win_row() const
{ 
	return size_of_win_row_;
}

const int* FieldInfo::operator[](int x) const
{
	return gaming_field_[x];
}



void Field::RefreshField()
{
	for (int i = 0; i < size_of_field_; ++i)
		for (int j = 0; j < size_of_field_; ++j)
			gaming_field_[i][j] = 0;
}

void Field::set_size_of_field(int new_size)
{
	if (new_size < MIN_SIZE_OF_FIEFD || new_size > MAX_SIZE_OF_FIEFD)
		return;

	old_size_of_field_ = size_of_field_;
	size_of_field_ = new_size;

	if (size_of_field_ < size_of_win_row_)
		size_of_win_row_ = MIN_SIZE_OF_WIN_ROW;

	this->NewField();
}

void Field::set_size_of_win_row(int new_size)
{
	if (new_size < MIN_SIZE_OF_WIN_ROW || new_size > MAX_SIZE_OF_WIN_ROW)
		return;

	size_of_win_row_ = new_size;

	if (size_of_win_row_ > size_of_field_)
		size_of_win_row_ = MIN_SIZE_OF_WIN_ROW;
}

int* Field::operator[](int x) const
{
	return gaming_field_[x];
}

bool Field::CheckMove(int player, COORD move) const
{
	if (move.X < 0 || move.X >= size_of_field_ || move.Y < 0 || move.Y >= size_of_field_)
		return false;

	if (gaming_field_[move.X][move.Y] == 0)
	{
		gaming_field_[move.X][move.Y] = player;
		return true;
	}
	else
		return false;
}

bool Field::CheckLine(COORD move) const
{
	// counter of figures in a row
	int counter = 0;
	// player, that make this move (1 - player1, 2 - player2)
	int player = gaming_field_[move.X][move.Y];

	for (int i = 0; i < size_of_field_; ++i)
	{
		if (gaming_field_[i][move.Y] == player)
		{
			counter++;
		}
		else
		{
			if (counter < size_of_win_row_) counter = 0;
			else return true;
		}
	}

	return (counter >= size_of_win_row_ ? true : false);
}

bool Field::CheckColumn(COORD move) const
{
	// counter of figures in a row
	int counter = 0;
	// player, that make this move (1 - player1, 2 - player2)
	int player = gaming_field_[move.X][move.Y];

	for (int i = 0; i < size_of_field_; ++i)
	{
		if (gaming_field_[move.X][i] == player)
		{
			counter++;
		}
		else
		{
			if (counter < size_of_win_row_) counter = 0;
			else return true;
		}
	}

	return (counter >= size_of_win_row_ ? true : false);
}

bool Field::CheckLeftToRightDiagonal(COORD move) const
{
	// counter of figures in a row
	int counter = 0;
	// player, that make this move (1 - player1, 2 - player2)
	int player = gaming_field_[move.X][move.Y];

	COORD position; // start position - upper left corner of diagonal
	position.X = move.X - min(move.X, move.Y);
	position.Y = move.Y - min(move.X, move.Y);

	for (; (position.X < size_of_field_ && position.Y < size_of_field_); position.X++, position.Y++)
	{
		if (gaming_field_[position.X][position.Y] == player)
		{
			counter++;
		}
		else
		{
			if (counter < size_of_win_row_) counter = 0;
			else return true;
		}
	}

	return (counter >= size_of_win_row_ ? true : false);
}

bool Field::CheckRightToLeftDiagonal(COORD move) const
{
	// counter of figures in a row
	int counter = 0;
	// player, that make this move (1 - player1, 2 - player2)
	int player = gaming_field_[move.X][move.Y];

	COORD position; // start position - upper right corner of diagonal
	if (move.X + move.Y <= size_of_field_ - 1)
	{
		position.X = move.X + move.Y;
		position.Y = 0;
	}
	else
	{
		// - 1 because coordinates in programm begin from 0 (not from 1)
		position.X = size_of_field_ - 1;
		position.Y = move.Y - (size_of_field_ - move.X - 1);
	}

	for (; (position.X >= 0 && position.Y < size_of_field_); position.X--, position.Y++)
	{
		if (gaming_field_[position.X][position.Y] == player)
		{
			counter++;
		}
		else
		{
			if (counter < size_of_win_row_) counter = 0;
			else return true;
		}
	}

	return (counter >= size_of_win_row_ ? true : false);
}

bool Field::CheckForWin(COORD move) const
{
	return (
		CheckLine(move) ||
		CheckColumn(move) ||
		CheckLeftToRightDiagonal(move) ||
		CheckRightToLeftDiagonal(move)
		);
}

