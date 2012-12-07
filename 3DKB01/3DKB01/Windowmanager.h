#ifndef __WINDOWMANAGER_H__
#define __WINDOWMANAGER_H__

#include "eWindow.h"
#include <string>
#include <hash_map>

class Windowmanager
{
private:
	eWindow* window1;
	eWindow* window2;
	std::hash_map<std:string, eWindow*> windows;
public:
	Windowmanager(void);
	~Windowmanager(void);
	void createWindow();
	void addWindow(eWindow* window);
	eWindow& getWindow(std::string argWindowName);
};

#endif