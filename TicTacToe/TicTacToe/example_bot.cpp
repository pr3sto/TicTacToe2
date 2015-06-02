// example_bot.cpp - example bot

#include "example_bot.h"

ExampleBot::ExampleBot(FieldInfo* field_) :
Player(field_, "Example bot") { }

ExampleBot::~ExampleBot() { }

COORD ExampleBot::Move() const
{
	std::vector<COORD> free_cells;
	for (u_int i = 0; i < field->SizeOfField(); ++i)
	{
		for (u_int j = 0; j < field->SizeOfField(); ++j)
		{
			if ((*field)[i][j] == 0)
			{
				COORD tmp; 
				tmp.X = i; 
				tmp.Y = j;
				free_cells.push_back(tmp);
			}
		}
	}

	u_int random_number = std::rand() % (free_cells.size()+1);

	COORD ret;
	ret.X = free_cells[random_number].X; 
	ret.Y = free_cells[random_number].Y;
	return ret;
}

void ExampleBot::Info() const
{
	std::cout
		<< std::setw(48) << " Пример бота  " << std::endl
		<< std::setw(48) << "Автор - pr3sto" << std::endl
		<< std::setw(48) << "    2015      " << std::endl;
}