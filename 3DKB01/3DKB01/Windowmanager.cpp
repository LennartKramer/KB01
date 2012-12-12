#include "Windowmanager.h"

Windowmanager::Windowmanager(void)
{
	eWindow* window = new eWindow();
}

Windowmanager::~Windowmanager(void)
{
}

// Creates a window object
void Windowmanager::createWindow()
{
	eWindow* window = new eWindow();
	addWindow(window);
}

// Adds window object to list
void Windowmanager::addWindow(eWindow* argWindow)
{
	windows.push_back(argWindow);
}

// returns a window object from list
eWindow* Windowmanager::getWindow(std::string argWindowName)
{
	for(int i =0; i<this->windows.size(); ++i) 
	{
		std::list<eWindow*>::iterator Iterator;
		for(Iterator = windows.begin(); Iterator != windows.end(); ++Iterator)
		{
			if((*Iterator)->getName() == argWindowName)
			{
				return (*Iterator);
			}
		}
		
	}
}