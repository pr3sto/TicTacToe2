// my_bot.cpp - bot

#include "my_bot.h"

MyBot::MyBot(FieldInfo* _field) :
	Player(_field, "pr3sto's bot")
{}

MyBot::~MyBot()
{}

COORD MyBot::Move() const
{
	return COORD();
}

void MyBot::Info() const
{
	std::cout
		<< std::setw(51) << "          Бот          " << std::endl
		<< std::setw(51) << "     Автор: pr3sto     " << std::endl
		<< std::setw(51) << "          2015         " << std::endl;
}