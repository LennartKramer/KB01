#ifndef _WINDOW_H
#define _WINDOW_H
#include <Windows.h>

class LotsoWindow
{
	public:
	//*** Constructor/Destructor ***
	LotsoWindow(WNDPROC messageHandler, LPCTSTR title, int x, int y, int width, int height, LPTSTR name);
	~LotsoWindow(void);

	//*** Accessors/Modifiers ***
	HWND getHandle(void);
	LPTSTR getName(void);

	//*** Methods ***
	void show(void);
	void setSize(int width, int height);

	private:
	//*** Fields ***
	WNDCLASS windowClass;
	HWND lotsoWindow;
	LPTSTR name;
};
#endif

