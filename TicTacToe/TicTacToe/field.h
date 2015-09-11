// field.h - gaming field

#ifndef FIELD_H_
#define FIELD_H_

#include <utility>   // std::pair
#include "windows.h" // COORD - coordinates on the field
#include "log.h" 

// information about gaming field
// without permission to change something
class FieldInfo
{
protected:
	int** gaming_field_;
	int size_of_field_;
	int size_of_winning_row_;   // number of figures in row to win
	int old_size_of_field_;     // for correct deletion

	void NewField();
	void DeleteField();

public:
	static const int MAX_SIZE_OF_FIEFD = 10;
	static const int MIN_SIZE_OF_FIEFD = 3;
	static const int MAX_SIZE_OF_WINNING_ROW = 10;
	static const int MIN_SIZE_OF_WINNING_ROW = 3;

	FieldInfo();
	~FieldInfo();

	// getters
	int size_of_field() const;
	int size_of_winning_row() const;

	// don't check index out of bounds
	// const - to prohibit changing
	//
	// usage: 
	// FieldInfo field; 
	// int value_of_field_cell = field[x][y];	
	const int* operator[](int x) const;
};



// information about gaming field
// with the possibility to change something
class Field : public FieldInfo
{
private:
	// additional functions for CheckForWin

	// x x
	// _ _
	bool CheckLine(COORD move) const;
	// x _
	// x _
	bool CheckColumn(COORD move) const;
	// x _
	// _ x
	bool CheckLeftToRightDiagonal(COORD move) const;
	// _ x
	// x _
	bool CheckRightToLeftDiagonal(COORD move) const;

public:
	// erase all figures from field
	void RefreshField();

	// setters
	void set_size_of_field(int new_size);
	void set_size_of_winning_row(int new_size);

	// dont check index out of bounds
	//
	// usage: 
	// Field field; 
	// int new_value = 42;
	// int value_of_field_cell = field[x][y];
	// field[x][y] = new_value;
	int* operator[](int x) const;

	// check posibility to make move in cell 'move'
	// and make this move (move by player)
	bool CheckMove(int player, COORD move) const;

	// 'move' - coordinates of player's move
	// that can cause victory
	// @return true if player, that make this move, win
	bool CheckForWin(COORD move) const;

	// return coordinates of ends of winning row
	// player = 1 / 2 - player1 / player2 win
	std::pair<COORD, COORD> EndsOfWinningRow(int player) const;
};

#endif // FIELD_H_
