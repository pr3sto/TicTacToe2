// field.h - gaming field

#ifndef FIELD_H_
#define FIELD_H_

#include <memory> // std::shared_ptr
#include <iostream>
#include "windows.h"

class FieldInfo
{
protected:
	u_int** gamingField;
	u_int sizeOfField;
	u_int sizeOfWinRow;
	u_int oldSizeOfField; // for correct deletion

	void NewField();
	void DeleteField();

public:
	FieldInfo();
	~FieldInfo();

	const u_int MAX_SIZE_OF_FIEFD = 10;
	const u_int MIN_SIZE_OF_FIEFD = 3;
	const u_int MAX_SIZE_OF_WIN_ROW = 10;
	const u_int MIN_SIZE_OF_WIN_ROW = 3;

	// getters
	u_int SizeOfField() const;
	u_int SizeOfWinRow() const;

	// const to prohibit changing
	const u_int* operator[](u_int) const;
};

class Field : public FieldInfo
{
private:
	// additional functions for VerifyVictory
	bool CheckLine(COORD) const;
	bool CheckColumn(COORD) const;
	bool CheckLeftToRightDiagonal(COORD) const;
	bool CheckRightToLeftDiagonal(COORD) const;

public:
	// setters
	void SetSizeOfField(u_int);
	void SetSizeOfWinRow(u_int);

	u_int* operator[](u_int) const;

	bool VerifyMove(u_int, COORD) const;

	// COORD - coordinates of player's move
	//         that can cause victory
	bool VerifyVictory(COORD) const;
};

#endif // FIELD_H_
