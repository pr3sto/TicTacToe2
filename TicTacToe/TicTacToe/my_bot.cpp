// my_bot.cpp - bot 
// minimax algorithm

#include "my_bot.h"

int factorial(int n)
{
	if (n < 0) return 0;
	return !n ? 1 : n * factorial(n - 1);
}

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

bool MyBot::is_terminal(COORD position, int depth)
{
	// max depth
	if (work_field->size_of_field() == 4 && depth == 6)
		return true;
	if (work_field->size_of_field() == 5 && depth == 5)
		return true;
	if (work_field->size_of_field() == 6 && depth == 4)
		return true;
	if ((work_field->size_of_field() == 7 || work_field->size_of_field() == 8) && depth == 3)
		return true;
	if ((work_field->size_of_field() == 9 || work_field->size_of_field() == 10) && depth == 2)
		return true;

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

int MyBot::score_of_terminal_position(COORD position, int player, int depth)
{
	if (work_field->CheckForWin(position))
	{
		if ((*work_field)[position.X][position.Y] == player)
			return 50 - depth; // win
		else
			return -50 + depth; // loss
	}

	return 0; // draw or nothing
}

int MyBot::utility_of_move(COORD position, int player)
{
	int i, j;

	// horizontal line
	int k_h = 0;
	int k_h_1 = 0;

	// k_h
	for (i = position.X + 1; i < work_field->size_of_field(); ++i)
	{
		if ((*work_field)[i][position.Y] == player) 
			k_h++;
		else 
			break;
	}
	for (i = position.X-1; i >= 0; --i)
	{
		if ((*work_field)[i][position.Y] == player)
			k_h++;
		else
			break;
	}
	if (k_h != 0 ||
		(position.X + 1 < work_field->size_of_field() && (*work_field)[position.X + 1][position.Y] == 0) ||
		(position.X - 1 >=0 && (*work_field)[position.X - 1][position.Y] == 0))
	{
		k_h++;
	}
	// k_h_1
	for (i = position.X + 1; i < work_field->size_of_field(); ++i)
	{
		if ((*work_field)[i][position.Y] == player % 2 + 1)
			k_h_1++;
		else
			break;
	}
	for (i = position.X - 1; i >= 0; --i)
	{
		if ((*work_field)[i][position.Y] == player % 2 + 1)
			k_h_1++;
		else
			break;
	}
	if (k_h_1 != 0 ||
		(position.X + 1 < work_field->size_of_field() && (*work_field)[position.X + 1][position.Y] == 0) ||
		(position.X - 1 >= 0 && (*work_field)[position.X - 1][position.Y] == 0))
	{
		k_h_1++;
	}

	// vertical line
	int k_v = 0;
	int k_v_1 = 0;

	// k_v
	for (j = position.Y + 1; j < work_field->size_of_field(); ++j)
	{
		if ((*work_field)[position.X][j] == player)
			k_v++;
		else
			break;
	}
	for (j = position.Y - 1; j >= 0; --j)
	{
		if ((*work_field)[position.X][j] == player)
			k_v++;
		else
			break;
	}
	if (k_v != 0 ||
		(position.Y + 1 < work_field->size_of_field() && (*work_field)[position.X][position.Y + 1] == 0) ||
		(position.Y - 1 >= 0 && (*work_field)[position.X][position.Y - 1] == 0))
	{
		k_v++;
	}
	// k_v_1
	for (j = position.Y + 1; j < work_field->size_of_field(); ++j)
	{
		if ((*work_field)[position.X][j] == player % 2 + 1)
			k_v_1++;
		else
			break;
	}
	for (j = position.Y - 1; j >= 0; --j)
	{
		if ((*work_field)[position.X][j] == player % 2 + 1)
			k_v_1++;
		else
			break;
	}
	if (k_v_1 != 0 ||
		(position.Y + 1 < work_field->size_of_field() && (*work_field)[position.X][position.Y + 1] == 0) ||
		(position.Y - 1 >= 0 && (*work_field)[position.X][position.Y - 1] == 0))
	{
		k_v_1++;
	}

	// left to right diagonal
	int k_d1 = 0;
	int k_d1_1 = 0;

	// k_d1
	for (i = position.X + 1, j = position.Y + 1;
		(i < work_field->size_of_field() && j < work_field->size_of_field()); ++i, ++j)
	{
		if ((*work_field)[i][j] == player)
			k_d1++;
		else
			break;
	}
	for (i = position.X - 1, j = position.Y - 1;
		(i >= 0 && j >= 0); --i, --j)
	{
		if ((*work_field)[i][j] == player)
			k_d1++;
		else
			break;
	}
	if (k_d1 != 0 ||
		(position.X + 1 < work_field->size_of_field() && position.Y + 1 < work_field->size_of_field() && 
		(*work_field)[position.X + 1][position.Y + 1] == 0) ||
		(position.X - 1 >= 0 && position.Y - 1 >= 0 && (*work_field)[position.X - 1][position.Y - 1] == 0))
	{
		k_d1++;
	}
	// k_d1_1
	for (i = position.X + 1, j = position.Y + 1;
		(i < work_field->size_of_field() && j < work_field->size_of_field()); ++i, ++j)
	{
		if ((*work_field)[i][j] == player % 2 + 1)
			k_d1_1++;
		else
			break;
	}
	for (i = position.X - 1, j = position.Y - 1;
		(i >= 0 && j >= 0); --i, --j)
	{
		if ((*work_field)[i][j] == player % 2 + 1)
			k_d1_1++;
		else
			break;
	}
	if (k_d1_1 != 0 ||
		(position.X + 1 < work_field->size_of_field() && position.Y + 1 < work_field->size_of_field() &&
		(*work_field)[position.X + 1][position.Y + 1] == 0) ||
		(position.X - 1 >= 0 && position.Y - 1 >= 0 && (*work_field)[position.X - 1][position.Y - 1] == 0))
	{
		k_d1_1++;
	}

	// right to left diagonal
	int k_d2 = 0;
	int k_d2_1 = 0;

	//k_d2
	for (i = position.X + 1, j = position.Y - 1;
		(i < work_field->size_of_field() && j >= 0); ++i, --j)
	{
		if ((*work_field)[i][j] == player)
			k_d2++;
		else
			break;
	}
	for (i = position.X - 1, j = position.Y + 1;
		(i >= 0 && j < work_field->size_of_field()); --i, ++j)
	{
		if ((*work_field)[i][j] == player)
			k_d2++;
		else
			break;
	}
	if (k_d2 != 0 ||
		(position.X + 1 < work_field->size_of_field() && position.Y - 1 >= 0 &&
		(*work_field)[position.X + 1][position.Y - 1] == 0) ||
		(position.X - 1 >= 0 && position.Y + 1 < work_field->size_of_field() && (*work_field)[position.X - 1][position.Y + 1] == 0))
	{
		k_d2++;
	}
	//k_d2_1
	for (i = position.X + 1, j = position.Y - 1;
		(i < work_field->size_of_field() && j >= 0); ++i, --j)
	{
		if ((*work_field)[i][j] == player % 2 + 1)
			k_d2_1++;
		else
			break;
	}
	for (i = position.X - 1, j = position.Y + 1;
		(i >= 0 && j < work_field->size_of_field()); --i, ++j)
	{
		if ((*work_field)[i][j] == player % 2 + 1)
			k_d2_1++;
		else
			break;
	}
	if (k_d2_1 != 0 ||
		(position.X + 1 < work_field->size_of_field() && position.Y - 1 >= 0 &&
		(*work_field)[position.X + 1][position.Y - 1] == 0) ||
		(position.X - 1 >= 0 && position.Y + 1 < work_field->size_of_field() && (*work_field)[position.X - 1][position.Y + 1] == 0))
	{
		k_d2_1++;
	}

	// win
	if (k_v >= work_field->size_of_winning_row() ||
		k_h >= work_field->size_of_winning_row() ||
		k_d1 >= work_field->size_of_winning_row() ||
		k_d2 >= work_field->size_of_winning_row())
		return INT_MAX - 10;

	// loss
	if (k_v_1 >= work_field->size_of_winning_row() ||
		k_h_1 >= work_field->size_of_winning_row() ||
		k_d1_1 >= work_field->size_of_winning_row() ||
		k_d2_1 >= work_field->size_of_winning_row())
		return INT_MIN + 10;

	return factorial(k_v + 2) + factorial(k_v_1 + 2) +
		   factorial(k_h + 2) + factorial(k_h_1 + 2) +
		   factorial(k_d1 + 2) + factorial(k_d1_1 + 2) +
		   factorial(k_d2 + 2) + factorial(k_d2_1 + 2);
}

int MyBot::minimax_algorithm(COORD position, int alpha, int beta, int player, int depth, bool my_move, COORD &move)
{
	if (is_terminal(position, depth))
	{
		if (my_move) return score_of_terminal_position(position, player, depth);
		else         return -score_of_terminal_position(position, player, depth);
	}

	// score of this move
	int score;
	if (my_move) score = alpha;
	else         score = beta;

	// possible positions
	std::vector<std::pair<COORD, int> > possible_positions;
	for (int i = 0; i < work_field->size_of_field(); ++i)
	{
		for (int j = 0; j < work_field->size_of_field(); ++j)
		{
			if ((*work_field)[i][j] == 0)
			{
				COORD pos; pos.X = i; pos.Y = j;
				possible_positions.push_back(std::make_pair(pos, utility_of_move(pos, player)));
			}
		}
	}
	auto cmp = [](std::pair<COORD, int> const & a, std::pair<COORD, int> const & b)
	{ return a.second > b.second; };
	std::sort(possible_positions.begin(), possible_positions.end(), cmp);

	// minimax algorithm
	for (auto i = possible_positions.begin(); i != possible_positions.end(); ++i)
	{
		(*work_field)[i->first.X][i->first.Y] = player;
		counter_of_figures++;

		position.X = i->first.X; position.Y = i->first.Y;
		int score_of_move; 
		if (my_move) score_of_move = minimax_algorithm(position, score, beta, player % 2 + 1, depth + 1, !my_move, move);
		else         score_of_move = minimax_algorithm(position, alpha, score, player % 2 + 1, depth + 1, !my_move, move);

		(*work_field)[i->first.X][i->first.Y] = 0;
		counter_of_figures--;

		if (my_move)
		{
			if (score_of_move > score)
			{
				score = score_of_move;
				if (depth == 0) { move = i->first; }
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
		ret.X = std::rand() % field->size_of_field();
		ret.Y = std::rand() % field->size_of_field();
		return ret;
	}

	// minimax algorithm
	COORD ret_move;
	minimax_algorithm(COORD(), INT_MIN, INT_MAX, player_index, 0, true, ret_move);
	return ret_move;
}

void MyBot::Info() const
{
	std::cout
		<< std::setw(54) << "            ���             " << std::endl
		<< std::setw(54) << " ��������� �������� minimax " << std::endl
		<< std::setw(54) << "  c alpha-beta ����������   " << std::endl
		<< std::setw(54) << "       �����: pr3sto        " << std::endl
		<< std::setw(54) << "            2015            " << std::endl;
}