#ifndef _WINDOW_H
#define _WINDOW_H
#include <Windows.h>
#include <string>

class LotsoWindow
{
	public:
	LotsoWindow(WNDPROC messageHandler, LPCTSTR title, int x, int y, int width, int height, std::string name);
	~LotsoWindow(void);

	HWND getHandle(void);
	std::string getName(void);

	void show(void);
	void setSize(int width, int height);

	private:
	WNDCLASS windowClass;
	HWND lotsoWindow;
	std::string name;
};
#endif

