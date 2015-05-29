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
	for (u_int i = 0; i < sizeOfField; i++)
		gamingField[i] = new u_int[sizeOfField];

	for (u_int i = 0; i < sizeOfField; i++)
	for (u_int j = 0; j < sizeOfField; j++)
		gamingField[i][j] = 0;
}

void FieldInfo::DeleteField()
{
	for (u_int i = 0; i < oldSizeOfField; i++)
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

u_int FieldInfo::ValueOfCell(u_int x, u_int y) const
{
	if (x < 0 || x >= sizeOfField || y < 0 || y >= sizeOfField)
	{
		std::cerr << "Accessing an array outside it's bounds: " << std::endl
			<< "Field[" << x << "][" << y << "]";
		exit(1);
	}
	else
		return gamingField[x][y];
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