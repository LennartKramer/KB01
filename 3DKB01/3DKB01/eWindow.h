#ifndef __EWINDOW_H__
#define __EWINDOW_H__

//#include "Scenemanager.h"
#include <string>
#include <iostream>

class eWindow
{
private:
std::string name;

public:
	eWindow(void);
	~eWindow(void);
	std::string getName();
	void setName(std::string argName);

};

#endif