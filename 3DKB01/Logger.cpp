//Hier komt de logger class.
#include "Logger.h"



Logger::Logger(void)
{
}


Logger::~Logger(void)
{
}

 
void Logger::message(HRESULT result, const std::string text)
{
	LPTSTR error;
	if (result == D3D_OK) error = TEXT("D3D OK");
	else if (result == D3DERR_INVALIDCALL) error = TEXT("D3DERR_INVALIDCALL: Invalid Call or Parameter!");
	else if (result == D3DERR_NOTAVAILABLE) error = TEXT("D3DERR_NOTAVAILABLE: Parameter not supported!");
	else if (result == D3DERR_OUTOFVIDEOMEMORY) error = TEXT("D3DERR_OUTOFVIDEOMEMORY: Out of Video Memory!");
	else if (result == D3DERR_DEVICELOST) error = TEXT("D3DERR_DEVICELOST: The device is lost!");
	else if (result == D3DERR_DRIVERINTERNALERROR) error = TEXT("D3DERR_DRIVERINTERNALERROR: Internal Driver Error!");
	else if (result == D3DXERR_INVALIDDATA) error = TEXT("D3DXERR_INVALIDDATA: Invalid data passed to D3DX function!");
	else error = TEXT("Unknown Error: %X"); //+result

	std::ofstream logfile("logfile.txt", std::ios_base::app | std::ios::out);
    logfile << currenttime() << text << " result: " << error << std::endl;
}

void Logger::message(const std::string text)
{
	std::ofstream logfile("logfile.txt", std::ios_base::app | std::ios::out);
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

void Logger::clearLog() 
{ 
	std::ofstream logfile("logfile.txt", std::ios::out); 
}