// field.cpp - gaming field

#include "field.h"

FieldInfo::FieldInfo()
{
	size_of_field_ = 3;
	size_of_winning_row_ = 3;
	old_size_of_field_ = 3;
	gaming_field_ = nullptr;

	this->NewField();
}

FieldInfo::~FieldInfo()
{
	old_size_of_field_ = size_of_field_;
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

int FieldInfo::size_of_winning_row() const
{ 
	return size_of_winning_row_;
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
	{
		std::string err = "Incorrect argument";
		std::string func = "void Field::set_size_of_field(int new_size)";
		std::string info = "new_size = "; info += std::to_string(new_size);
		std::string act = "Exit from function, continue programm";
		Log::write_log(err, func, info, act);
		return;
	}

	old_size_of_field_ = size_of_field_;
	size_of_field_ = new_size;

	if (size_of_field_ < size_of_winning_row_)
		size_of_winning_row_ = MIN_SIZE_OF_WINNING_ROW;

	this->NewField();
}

void Field::set_size_of_winning_row(int new_size)
{
	if (new_size < MIN_SIZE_OF_WINNING_ROW || new_size > MAX_SIZE_OF_WINNING_ROW)
	{
		std::string err = "Incorrect argument";
		std::string func = "void Field::set_size_of_winning_row(int new_size)";
		std::string info = "new_size = "; info += std::to_string(new_size);
		std::string act = "Exit from function, continue programm";
		Log::write_log(err, func, info, act);
		return;
	}

	size_of_winning_row_ = new_size;

	if (size_of_winning_row_ > size_of_field_)
		size_of_winning_row_ = MIN_SIZE_OF_WINNING_ROW;
}

int* Field::operator[](int x) const
{
	return gaming_field_[x];
}

bool Field::CheckMove(int player, COORD move) const
{
	if (player != 1 && player != 2)
	{
		std::string err = "Incorrect argument (first)";
		std::string func = "bool Field::CheckMove(int player, COORD move) const";
		std::string info = "player = "; info += std::to_string(player);
		std::string act = "exit(1)";
		Log::write_log(err, func, info, act);
		exit(1);
	}
	if (move.X < 0 || move.X >= size_of_field_ || move.Y < 0 || move.Y >= size_of_field_)
	{
		std::string err = "Incorrect argument (second)";
		std::string func = "bool Field::CheckMove(int player, COORD move) const";
		std::string info = "move = "; 
		info += std::to_string(move.X); info += ", "; info += std::to_string(move.Y);
		std::string act = "exit(1)";
		Log::write_log(err, func, info, act);
		exit(1);
	}

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
	if (move.X < 0 || move.X >= size_of_field_ || move.Y < 0 || move.Y >= size_of_field_)
	{
		std::string err = "Incorrect argument";
		std::string func = "bool Field::CheckLine(COORD move) const";
		std::string info = "move = ";
		info += std::to_string(move.X); info += ", "; info += std::to_string(move.Y);
		std::string act = "exit(1)";
		Log::write_log(err, func, info, act);
		exit(1);
	}

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
			if (counter < size_of_winning_row_) counter = 0;
			else return true;
		}
	}

	return (counter >= size_of_winning_row_ ? true : false);
}

bool Field::CheckColumn(COORD move) const
{
	if (move.X < 0 || move.X >= size_of_field_ || move.Y < 0 || move.Y >= size_of_field_)
	{
		std::string err = "Incorrect argument";
		std::string func = "bool Field::CheckColumn(COORD move) const";
		std::string info = "move = ";
		info += std::to_string(move.X); info += ", "; info += std::to_string(move.Y);
		std::string act = "exit(1)";
		Log::write_log(err, func, info, act);
		exit(1);
	}

	// counter of figures in a row
	int counter = 0;
	// player, that make this move (1 - player1, 2 - player2)
	int player = gaming_field_[move.X][move.Y];

	for (int i = 0; i < size_of_field_; ++i)
	{
		if (gaming_field_[move.X][i] == player)	counter++;
		else if (counter < size_of_winning_row_) counter = 0;
		else return true;
	}

	return (counter >= size_of_winning_row_ ? true : false);
}

bool Field::CheckLeftToRightDiagonal(COORD move) const
{
	if (move.X < 0 || move.X >= size_of_field_ || move.Y < 0 || move.Y >= size_of_field_)
	{
		std::string err = "Incorrect argument";
		std::string func = "bool Field::CheckLeftToRightDiagonal(COORD move) const";
		std::string info = "move = ";
		info += std::to_string(move.X); info += ", "; info += std::to_string(move.Y);
		std::string act = "exit(1)";
		Log::write_log(err, func, info, act);
		exit(1);
	}

	// counter of figures in a row
	int counter = 0;
	// player, that make this move (1 - player1, 2 - player2)
	int player = gaming_field_[move.X][move.Y];

	COORD position; // start position - upper left corner of diagonal
	position.X = move.X - min(move.X, move.Y);
	position.Y = move.Y - min(move.X, move.Y);

	for (; (position.X < size_of_field_ && position.Y < size_of_field_); position.X++, position.Y++)
	{
		if (gaming_field_[position.X][position.Y] == player) counter++;
		else if (counter < size_of_winning_row_) counter = 0;
		else return true;
	}

	return (counter >= size_of_winning_row_ ? true : false);
}

bool Field::CheckRightToLeftDiagonal(COORD move) const
{
	if (move.X < 0 || move.X >= size_of_field_ || move.Y < 0 || move.Y >= size_of_field_)
	{
		std::string err = "Incorrect argument";
		std::string func = "bool Field::CheckRightToLeftDiagonal(COORD move) const";
		std::string info = "move = ";
		info += std::to_string(move.X); info += ", "; info += std::to_string(move.Y);
		std::string act = "exit(1)";
		Log::write_log(err, func, info, act);
		exit(1);
	}

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
		if (gaming_field_[position.X][position.Y] == player) counter++;
		else if (counter < size_of_winning_row_) counter = 0;
		else return true;
	}

	return (counter >= size_of_winning_row_ ? true : false);
}

bool Field::CheckForWin(COORD move) const
{
	if (move.X < 0 || move.X >= size_of_field_ || move.Y < 0 || move.Y >= size_of_field_)
	{
		std::string err = "Incorrect argument";
		std::string func = "bool Field::CheckForWin(COORD move) const";
		std::string info = "move = ";
		info += std::to_string(move.X); info += ", "; info += std::to_string(move.Y);
		std::string act = "exit(1)";
		Log::write_log(err, func, info, act);
		exit(1);
	}

	return (
		CheckLine(move) ||
		CheckColumn(move) ||
		CheckLeftToRightDiagonal(move) ||
		CheckRightToLeftDiagonal(move)
		);
}

std::pair<COORD, COORD> Field::EndsOfWinningRow(int player) const
{
	if (player != 1 && player != 2)
	{
		std::string err = "Incorrect argument";
		std::string func = "std::pair<COORD, COORD> Field::EndsOfWinningRow(int player) const";
		std::string info = "player = "; info += std::to_string(player);
		std::string act = "exit(1)";
		Log::write_log(err, func, info, act);
		exit(1);
	}

	COORD start; // start of winning row
	COORD end;   // end of winning row

	int counter;

	// find start and end of winning row

	// column
	for (int x = 0; x < size_of_field_; ++x)
	{
		counter = 0;
		for (int y = 0; y < size_of_field_; ++y)
		{
			if (gaming_field_[x][y] == player) counter++;
			else if (counter < size_of_winning_row_) counter = 0;
			else
			{
				start.X = end.X = x; end.Y = --y;
				while (y >= 0 && gaming_field_[x][y] == player) --y;
				start.Y = ++y;

				return std::make_pair(start, end);
			}
		}
		if (counter >= size_of_winning_row_)
		{
			int y = size_of_field_ - 1;
			start.X = end.X = x; end.Y = y;
			while (y >= 0 && gaming_field_[x][y] == player) --y;
			start.Y = ++y;

			return std::make_pair(start, end);
		}
	}

	// line
	for (int y = 0; y < size_of_field_; ++y)
	{
		counter = 0;
		for (int x = 0; x < size_of_field_; ++x)
		{
			if (gaming_field_[x][y] == player) counter++;
			else if (counter < size_of_winning_row_) counter = 0;
			else
			{
				start.Y = end.Y = y; end.X = --x;
				while (x >= 0 && gaming_field_[x][y] == player) --x;
				start.X = ++x;

				return std::make_pair(start, end);
			}
		}
		if (counter >= size_of_winning_row_)
		{
			int x = size_of_field_ - 1;
			start.Y = end.Y = y; end.X = x;
			while (x >= 0 && gaming_field_[x][y] == player) --x;
			start.X = ++x;

			return std::make_pair(start, end);
		}
	}

	// left to right diagonal
	for (int y1 = 0; y1 < size_of_field_; ++y1)
	{
		counter = 0;
		int y = y1;
		int x;
		for (x = 0; (x < size_of_field_ && y < size_of_field_); ++x, ++y)
		{
			if (gaming_field_[x][y] == player) counter++;
			else if (counter < size_of_winning_row_) counter = 0;
			else
			{
				end.X = --x; end.Y = --y;
				while (x >= 0 && y >= 0 && gaming_field_[x][y] == player) --x, --y; 
				start.X = ++x; start.Y = ++y;

				return std::make_pair(start, end);
			}
		}
		if (counter >= size_of_winning_row_)
		{
			end.X = --x; end.Y = --y;
			while (x >= 0 && y >= 0 && gaming_field_[x][y] == player) --x, --y;
			start.X = ++x; start.Y = ++y;

			return std::make_pair(start, end);
		}
	}
	for (int x1 = 0; x1 < size_of_field_; ++x1)
	{
		counter = 0;
		int x = x1;
		int y;
		for (y = 0; (x < size_of_field_ && y < size_of_field_); ++x, ++y)
		{
			if (gaming_field_[x][y] == player) counter++;
			else if (counter < size_of_winning_row_) counter = 0;
			else
			{
				end.X = --x; end.Y = --y;
				while (x >= 0 && y >= 0 && gaming_field_[x][y] == player) --x, --y;
				start.X = ++x; start.Y = ++y;

				return std::make_pair(start, end);
			}
		}
		if (counter >= size_of_winning_row_)
		{
			end.X = --x; end.Y = --y;
			while (x >= 0 && y >= 0 && gaming_field_[x][y] == player) --x, --y;
			start.X = ++x; start.Y = ++y;

			return std::make_pair(start, end);
		}
	}

	// right to left diagonal
	for (int x1 = 0; x1 < size_of_field_; ++x1)
	{
		counter = 0;
		int x = x1;
		int y;
		for (y = 0; (x >=0 && y < size_of_field_); --x, ++y)
		{
			if (gaming_field_[x][y] == player) counter++;
			else if (counter < size_of_winning_row_) counter = 0;
			else
			{
				end.X = ++x; end.Y = --y;
				while (x < size_of_field_ && y >= 0 && gaming_field_[x][y] == player) ++x, --y;
				start.X = --x; start.Y = ++y;

				return std::make_pair(start, end);
			}
		}
		if (counter >= size_of_winning_row_)
		{
			end.X = ++x; end.Y = --y;
			while (x < size_of_field_ && y >= 0 && gaming_field_[x][y] == player) ++x, --y;
			start.X = --x; start.Y = ++y;

			return std::make_pair(start, end);
		}
	}
	for (int y1 = 0; y1 < size_of_field_; ++y1)
	{
		counter = 0;
		int y = y1;
		int x;
		for (x = size_of_field_-1; (x >=0 && y < size_of_field_); --x, ++y)
		{
			if (gaming_field_[x][y] == player) counter++;
			else if (counter < size_of_winning_row_) counter = 0;
			else
			{
				end.X = ++x; end.Y = --y;
				while (x < size_of_field_ && y >= 0 && gaming_field_[x][y] == player) ++x, --y;
				start.X = --x; start.Y = ++y;

				return std::make_pair(start, end);
			}
		}
		if (counter >= size_of_winning_row_)
		{
			end.X = ++x; end.Y = --y;
			while (x < size_of_field_ && y >= 0 && gaming_field_[x][y] == player) ++x, --y;
			start.X = --x; start.Y = ++y;

			return std::make_pair(start, end);
		}
	}	

	// ERROR: Function can't detect winning row
	std::string err = "Unknown error";
	std::string func = "std::pair<COORD, COORD> Field::EndsOfWinningRow(int player) const";
	std::string info = "Function can't detect winning row";
	std::string act = "exit(1)";
	Log::write_log(err, func, info, act);
	exit(1);
}

