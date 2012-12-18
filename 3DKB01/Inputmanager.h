#ifndef __Inputmanager_h__
#define __Inputmanagar_h__

#include <iostream>
#include <Windows.h>
#include "Mouse.h"
#include "Keyboard.h"

class Inputmanager
{
public:
	Inputmanager(void);
	~Inputmanager(void);
	void CreateMouse(HWND argWindow);
	void CreateKeyboard(HWND argWindow);
	Mouse* getMouse();
	Keyboard* getKeyboard();
private:
	Mouse* mouse;
	Keyboard* keyboard;
};

#endif