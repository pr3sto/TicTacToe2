// human.cpp - game player - Human

#include "human.h"

HumanPlayer::HumanPlayer(FieldInfo* field_) : Player(field_, "Человек") { }

HumanPlayer::~HumanPlayer() { }

COORD HumanPlayer::Move() 
{ 
	return COORD();
}