// statistics.cpp - statistics of the game

#include "statistics.h"

Statistics::Statistics()
{
	std::ifstream in_file;

	try {
		in_file.open("stats.txt");

		// if not empty
		if (in_file.peek() != std::ifstream::traits_type::eof())
		{
			int tmp_win, tmp_loss, tmp_draw;
			std::string tmp_name;

			for (;;)
			{
				in_file >> tmp_win >> tmp_loss >> tmp_draw;
				in_file.get(); // skip whitespace
				getline(in_file, tmp_name, '\n');

				stats_table[tmp_name] = { tmp_win, tmp_loss, tmp_draw };

				if (!in_file) break;
			}
		}

		in_file.close();
	} 
	catch (std::exception e)
	{
		std::string err = "Error while reading statistics from file";
		std::string func = "Statistics::Statistics()";
		std::string info = e.what();
		std::string act = "delete statistics from file, continue programm";
		Log::write_log(err, func, info, act);
		
		in_file.close();
	}
}

Statistics::~Statistics()
{
	this->Save();
}

void Statistics::AddStatistics(std::string player_name, results result)
{
	if (player_name.empty())
	{
		std::string err = "Error while adding player's statistics";
		std::string func = "void Statistics::AddStatistics(std::string player_name, results result)";
		std::string info = "std::string player_name is empty";
		std::string act = "don't save this player, continue programm";
		Log::write_log(err, func, info, act);

		return;
	}


	// add player
	if (stats_table.find(player_name) == stats_table.end())
		stats_table[player_name] = {0, 0, 0};

	// result of game
	switch (result)
	{
	case WIN:
		stats_table[player_name].number_of_wins++;
		break;
	case LOSS:
		stats_table[player_name].number_of_loss++;
		break;
	case DRAW:
		stats_table[player_name].number_of_draws++;
		break;
	default:
		break;
	}
}

void Statistics::Save() const
{
	std::ofstream out_file;

	try
	{
		out_file.open("stats.txt", std::ios_base::out | std::ios_base::trunc);

		for (auto i = stats_table.begin(); i != stats_table.end(); ++i)
		{
			if (i != stats_table.begin())
				out_file << std::endl;

			out_file << (*i).second.number_of_wins <<
				" " << (*i).second.number_of_loss << " " <<
				" " << (*i).second.number_of_draws <<
				" " << (*i).first;
		}

		out_file.close();
	}
	catch (std::exception e)
	{
		std::string err = "Error while saving statistics to file";
		std::string func = "void Statistics::Save() const";
		std::string info = e.what();
		std::string act = "don't save statistics, continue programm";
		Log::write_log(err, func, info, act);

		out_file.close();
	}
}

void Statistics::Show() const
{
	std::ios::fmtflags f(std::cout.flags());

	std::cout << "       " << std::setfill(' ') << std::setw(30) << std::left << "Игрок" 
		<< std::setw(15) << std::left << "  Победы " 
		<< std::setw(15) << std::left << "Поражения" 
		<< "  Ничьи  " << std::endl;
	
	std::cout.flags(f);

	std::cout << std::endl;

	for (auto i = stats_table.begin(); i != stats_table.end(); ++i)
	{
		std::ios::fmtflags f(std::cout.flags());

		std::cout << "    " << std::setfill(' ') << std::setw(37) << std::left << (*i).first 
			<< std::setw(15) << std::left << (*i).second.number_of_wins 
			<< std::setw(15) << std::left << (*i).second.number_of_loss 
			<< (*i).second.number_of_draws << std::endl;

		std::cout.flags(f);
	}
}