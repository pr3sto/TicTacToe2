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
	u_int ValueOfCell(u_int, u_int) const;
};

class Field : public FieldInfo
{
public:
	// setters
	void SetSizeOfField(u_int);
	void SetSizeOfWinRow(u_int);
};

#endif // FIELD_H_
