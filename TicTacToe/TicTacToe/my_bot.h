// my_bot.h - bot
// bot realizes minimax algorithm
// with alpha–beta pruning

#ifndef MY_BOT_H_
#define MY_BOT_H_

#include <random>
#include <vector>
#include <utility>    // std::pair
#include <algorithm>  // std::sort
#include <climits>
#include "player.h"

// bot
class MyBot : public Player
{
private:
	// field used for watching possible moves
	Field* work_field;
	// counter of figures on field
	int counter_of_figures;

	// initialization
	void init_work_field();


	// determine final state for searching
	bool is_terminal(COORD position, int depth);

	// calculate score of field's state
	int score_of_terminal_position(COORD position, int player, int depth);

	// utility of move (usefulness + safeness)
	int utility_of_move(COORD move, int player);


	// COORD &move = best move
	int minimax_algorithm(
			COORD position,  // current move position 
			int alpha,       // for alpha–beta pruning
			int beta,        // for alpha–beta pruning
			int player,      // player
			int depth,       // depth of searching
			bool my_move,    // who's move
			COORD &move      // after function best move here 
		);

public:
	MyBot(FieldInfo* _field);
	~MyBot();

	virtual COORD Move();
	virtual void Info() const;
};

#endif // MY_BOT_H_