#include "Windowmanager.h"
#include "LotsoWindow.h"

Windowmanager::Windowmanager()
{
}

Windowmanager::~Windowmanager()
{
}

// Creates a window object
void Windowmanager::createWindow(WNDPROC argMessageHandler, LPCTSTR argTitle, int argX, int argY, int argWidth, int argHeight, std::string argName)
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

void Windowmanager::showWindows()
{
		std::list<LotsoWindow*>::iterator Iterator;
		for(Iterator = windows.begin(); Iterator != windows.end(); ++Iterator)
		{
			(*Iterator)->show();
		}
}

int Windowmanager::getWindowAmount()
{
	return windows.size();
}

bool Windowmanager::update()
{
	// So, let's process those messages.
	MSG msg;
	ZeroMemory(&msg, sizeof(msg)); // Just incase there's something there.

	// Basically, we loop as long as we don't get the QUIT message.
	while (msg.message != WM_QUIT) {
		// Move the camera position when one of the following cases exists.
		// Using a CASE statement.

		// Are there any messages waiting to be processed?
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			// Translate it and send it off for processing.
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		} 
		else
		{
			return true;
		}

	}

}