#ifndef __WINDOWMANAGER_H__
#define __WINDOWMANAGER_H__

#include "eWindow.h"
#include <iostream>
#include <string>
#include <list>
#include <iterator>

class Windowmanager
{
private:
	std::list<eWindow*> windows;
public:
	Windowmanager(void);
	~Windowmanager(void);
	void createWindow();
	void addWindow(eWindow* window);
	eWindow* getWindow(std::string argWindowName);
};

#endif