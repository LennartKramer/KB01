#ifndef _WINDOW_H
#define _WINDOW_H
#include <Windows.h>

class LotsoWindow
{
	public:
	//*** Constructor/Destructor ***
	LotsoWindow(WNDPROC messageHandler, LPCTSTR title, int x, int y, int width, int height, LPTSTR name);
	~LotsoWindow();

	//*** Accessors/Modifiers ***
	HWND getHandle() { return lotsoWindow; }
	LPTSTR getName() { return name; }

	//*** Methods ***
	void show() { ShowWindow(lotsoWindow, SW_SHOWDEFAULT); }
	void setSize(int width, int height) {
		SetWindowPos(lotsoWindow, HWND_NOTOPMOST, NULL, NULL, width, height, SWP_NOACTIVATE | SWP_NOMOVE);
	}

	private:
	//*** Fields ***
	WNDCLASS windowClass;
	HWND lotsoWindow;
	LPTSTR name;
};
#endif

