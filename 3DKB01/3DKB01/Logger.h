#ifndef __Logger_h__
#define __Logger_h__

#include <fstream>
#include <iostream>
#include <string>
#include <ctime>

class Logger
{
public:
	Logger(void);
	~Logger(void);
	void message(const std::string &text);
	void warning(const std::string &text);
	void critical(const std::string &text);
	std::string currenttime();
};

//int main()
//{
	//Logger logger;
	//logger.message("er wordt nu iets gelogd...");
	//int stop;
	//std::cin >> stop;
	//return 0;
//}

#endif