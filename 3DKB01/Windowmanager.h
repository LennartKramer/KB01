#ifndef __WINDOWMANAGER_H__
#define __WINDOWMANAGER_H__

#include "LotsoWindow.h"
#include <iostream>
#include <string>
#include <list>
#include <iterator>

class Windowmanager
{
private:
	std::list<LotsoWindow*> windows;
public:
	Windowmanager(void);
	~Windowmanager(void);
	void createWindow(WNDPROC messageHandler, LPCTSTR title, int x, int y, int width, int height, std::string name);
	void addWindow(LotsoWindow* window);
	LotsoWindow* getWindow(std::string argWindowName);
	void cleanup();
	void showWindows();
	int getWindowAmount();
	bool update();
	};

#endif