#ifndef _WINDOW_H
#define _WINDOW_H
#include <Windows.h>

class LotsoWindow
{
	public:
	LotsoWindow(WNDPROC messageHandler, LPCTSTR title, int x, int y, int width, int height, LPTSTR name);
	~LotsoWindow(void);

	HWND getHandle(void);
	LPTSTR getName(void);

	void show(void);
	void setSize(int width, int height);

	private:
	WNDCLASS windowClass;
	HWND lotsoWindow;
	LPTSTR name;
};
#endif

