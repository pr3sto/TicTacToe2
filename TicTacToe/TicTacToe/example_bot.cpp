// example_bot.cpp - example bot

#include "example_bot.h"

ExampleBot::ExampleBot(FieldInfo* _field) :
	Player(_field, "Example bot") 
{}

ExampleBot::~ExampleBot() 
{}

COORD ExampleBot::Move()
{
	std::vector<COORD> free_cells;
	for (int i = 0; i < field->size_of_field(); ++i)
	{
		for (int j = 0; j < field->size_of_field(); ++j)
		{
			if ((*field)[i][j] == 0)
			{
				COORD free_cell; 
				free_cell.X = i;
				free_cell.Y = j;
				free_cells.push_back(free_cell);
			}
		}
	}

	int random_number = std::rand() % free_cells.size();

	COORD ret;
	ret.X = free_cells[random_number].X; 
	ret.Y = free_cells[random_number].Y;
	return ret;
}

void ExampleBot::Info() const
{
	std::cout
		<< std::setw(51) << "      Пример бота      " << std::endl
		<< std::setw(51) << "Ходит случайным образом" << std::endl
		<< std::setw(51) << "     Автор: pr3sto     " << std::endl
		<< std::setw(51) << "          2015         " << std::endl;
}