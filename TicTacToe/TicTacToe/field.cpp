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