// statistics.h - statistics of the game

#ifndef STATISTICS_H_
#define STATISTICS_H_

#include <iostream>
#include <iomanip>
#include <string>
#include <map>
#include <fstream>
#include "log.h"

class Statistics
{
private:
	struct player_stats
	{
		int number_of_wins;
		int number_of_loss;
		int number_of_draws;
	};

	// table of statistics
	std::map<std::string, player_stats> stats_table;
	
public:
	static enum results { WIN, LOSS, DRAW };

	Statistics();
	~Statistics();

	// add statistics about player
	void AddStatistics(std::string player_name, results result);

	// save to file
	void Save() const;

	// show statistics (stdout)
	void Show() const;
};

#endif //STATISTICS_H_