//Hier komt de logger class.
#include "Logger.h"
#include <fstream>
#include <iostream>
#include <string>
#include <stdio.h>
#include <time.h>

Logger::Logger(void)
{
}


Logger::~Logger(void)
{
}

 
void Logger::message( const std::string &text )
{
    std::ofstream logfile("logfile.txt", std::ios::out);
    logfile << currenttime() << text << std::endl;
}

void Logger::warning( const std::string &text )
{
    std::ofstream logfile("logfile.txt", std::ios::out);
    logfile << currenttime() << text << std::endl;
}
void Logger::critical( const std::string &text )
{
	std::ofstream logfile("logfile.txt", std::ios::out);
    logfile << currenttime() << text << std::endl;
}

std::string Logger::currenttime()
{
 time_t rawtime;
  struct tm * timeinfo;
  char buffer [80];

  time ( &rawtime );
  timeinfo = localtime ( &rawtime );

  strftime (buffer,80,"%X --  ",timeinfo);
return buffer;
} 
