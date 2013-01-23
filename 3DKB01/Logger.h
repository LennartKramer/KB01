#ifndef __Logger_h__
#define __Logger_h__

#include <fstream>
#include <iostream>
#include <string>
#include <stdio.h>
#include <time.h>
#include <d3dx9.h>

static class Logger
{
public:
	Logger(void);
	~Logger(void);
	void static message(HRESULT, const std::string);
	void static message(const std::string text);
	void static warning(const std::string &text);
	void static critical(const std::string &text);
	void static clearLog() { std::ofstream logfile("logfile.txt", std::ios::out); }
	std::string static currenttime();
};

#endif