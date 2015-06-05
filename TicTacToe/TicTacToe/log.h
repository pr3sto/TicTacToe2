// log.h - writing logs

#ifndef LOG_H_
#define LOG_H_

#include <string>
#include <iostream>
#include <fstream>
#include <ctime>

class Log
{
public:
	static void write_log(
		const std::string &error,         // error
		const std::string &function_name, // in function 'function_name'
		const std::string &info,          // info about error
		const std::string &action         // programm reaction on that error
		)
	{
		std::ofstream log_file("log_file.txt", std::ios_base::out | std::ios_base::app);

		// date and time
		time_t timer = time(NULL);
		char date_and_time[26];
		ctime_s(date_and_time, 26, &timer);

		log_file << "Date and Time: " << date_and_time;
		log_file << "Error: " << error << std::endl;
		log_file << "In function: " << function_name << std::endl;
		log_file << "Info: " << info << std::endl;
		log_file << "Programm reaction: " << action << std::endl;
		log_file << "---------------------------" << std::endl;

		log_file.close();
	}
};

#endif //LOG_H_