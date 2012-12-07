#include <iostream>
#include "Windowmanager.h"

Windowmanager::Windowmanager(void)
{
	window1 = new eWindow();
}
Windowmanager::~Windowmanager(void)
{
}
// Creates a window object
void Windowmanager::createWindow()
{
	eWindow* window2 = new eWindow();
	addWindow(window2);
}
// Adds window object to list
void Windowmanager::addWindow(eWindow* argWindow)
{
	//this->windows.
}
// returns a window object from list
eWindow& Windowmanager::getWindow(std::string argWindowName)
{
	//if(this->windows->)
}