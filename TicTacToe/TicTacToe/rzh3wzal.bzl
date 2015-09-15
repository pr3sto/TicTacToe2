// my_bot.cpp - bot 
// minimax algorithm

#include "my_bot.h"

#include <chrono>
#include <sstream>
/*
auto t_start = std::chrono::high_resolution_clock::now();
//
auto t_now = std::chrono::high_resolution_clock::now();
long double ftime = std::chrono::duration_cast<std::chrono::duration<long double>>(t_now - t_start).count();
std::ostringstream ss; ss << ftime;
std::string s(ss.str()); Log::write_log(s, " ", " ", " ");
*/


MyBot::MyBot(FieldInfo* _field) :
	Player(_field, "pr3sto's bot")
{
	work_field = new Field();
	counter_of_figures = 0;
}

MyBot::~MyBot()
{
	delete work_field;
}

void MyBot::init_work_field()
{
	counter_of_figures = 0;

	work_field->set_size_of_field(field->size_of_field());
	work_field->set_size_of_winning_row(field->size_of_winning_row());

	for (int i = 0; i < work_field->size_of_field(); ++i)
	{
		for (int j = 0; j < work_field->size_of_field(); ++j)
		{
			(*work_field)[i][j] = (*field)[i][j];
			if ((*field)[i][j] != 0) 
				counter_of_figures++;
		}
	}
}

bool MyBot::isTerminal(COORD position, int deph)
{
	// max deph
	if (deph == 5) return true;

	// field is full
	if (counter_of_figures >= work_field->size_of_field()*work_field->size_of_field())
		return true;

	// someone win
	if ((*work_field)[position.X][position.Y] != 0)
		if (work_field->CheckForWin(position))
			return true;

	// not terminal state
	return false;
}

int MyBot::heuristic(COORD position, int player, int deph)
{
	if ((*work_field)[position.X][position.Y] != 0)
	{
		if (work_field->CheckForWin(position))
		{
			if ((*work_field)[position.X][position.Y] == player)
				return 50 - deph;
			else
				return -50 + deph;
		}
	}

	return 0;
}

int MyBot::minimax_score(COORD position, int alpha, int beta, int player, int deph, bool my_move, COORD &move)
{
	if (isTerminal(position, deph))
	{
		if (my_move) return heuristic(position, player, deph);
		else         return -heuristic(position, player, deph);
	}

	// score of this move
	int score;
	if (my_move) score = alpha;
	else         score = beta;

	// possible positions
	for (int i = 0; i < work_field->size_of_field(); ++i)
	{
		for (int j = 0; j < work_field->size_of_field(); ++j)
		{
			if ((*work_field)[i][j] == 0)
			{
				//=============================
				(*work_field)[i][j] = player;
				counter_of_figures++;

				position.X = i; position.Y = j;
				int score_of_move; 
				if (my_move) score_of_move = minimax_score(position, score, beta, player % 2 + 1, deph + 1, !my_move, move);
				else         score_of_move = minimax_score(position, alpha, score, player % 2 + 1, deph + 1, !my_move, move);

				(*work_field)[i][j] = 0;
				counter_of_figures--;

				if (my_move)
				{
					if (score_of_move > score)
					{
						score = score_of_move;
						if (deph == 0) { move.X = i; move.Y = j; }
						if (score >= beta) return score;
					}
				}
				else
				{
					if (score_of_move < score)
					{
						score = score_of_move;
						if (score <= alpha) return score;
					}
				}
				//=============================
			}
		}
	}	

	return score;
}

COORD MyBot::Move()
{
	init_work_field();

	// field is empty -> random move
	if (counter_of_figures == 0)
	{
		COORD ret;
		srand(static_cast<unsigned int>(time(0)));
		ret.X = (std::rand() % 10) % 3;
		ret.Y = (std::rand() % 10) % 3;
		return ret;
	}

	// minimax algorithm
	COORD ret_move;
	minimax_score(COORD(), INT_MIN, INT_MAX, index, 0, true, ret_move);
	return ret_move;
}

void MyBot::Info() const
{
	std::cout
		<< std::setw(51) << "          Бот          " << std::endl
		<< std::setw(51) << "     Автор: pr3sto     " << std::endl
		<< std::setw(51) << "          2015         " << std::endl;
}