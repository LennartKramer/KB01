#include "Windowmanager.h"
#include "LotsoWindow.h"

Windowmanager::Windowmanager()
{
}

Windowmanager::~Windowmanager()
{
}

// Creates a window object
void Windowmanager::createWindow(WNDPROC argMessageHandler, LPCTSTR argTitle, int argX, int argY, int argWidth, int argHeight, LPTSTR argName)
{
	LotsoWindow* window = new LotsoWindow(argMessageHandler, argTitle, argX, argY, argWidth, argHeight, argName);
	addWindow(window);
}

// Adds window object to list
void Windowmanager::addWindow(LotsoWindow* argWindow)
{
	windows.push_back(argWindow);
}

// returns a window object from list
LotsoWindow* Windowmanager::getWindow(std::string argWindowName)
{
		std::list<LotsoWindow*>::iterator Iterator;
		for(Iterator = windows.begin(); Iterator != windows.end(); ++Iterator)
		{
			if((*Iterator)->getName() == argWindowName)
			{
				return (*Iterator);
			}
		}
}
void Windowmanager::cleanup()
{
		std::list<LotsoWindow*>::iterator Iterator;
		while (windows.size() != 0)
		{
			Iterator = windows.begin();
			(*Iterator)->~LotsoWindow();
			windows.remove((*Iterator));
		}
}