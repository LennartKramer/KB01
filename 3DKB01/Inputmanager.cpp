#include "Inputmanager.h"


Inputmanager::Inputmanager(void)
{
}

Inputmanager::~Inputmanager(void)
{
}

void Inputmanager::CreateMouse(HWND argWindow)
{
	mouse = new Mouse(argWindow);
}

void Inputmanager::CreateKeyboard(HWND argWindow)
{
	keyboard = new Keyboard(argWindow);
}

Mouse* Inputmanager::getMouse()
{
	return mouse;
}
	
Keyboard* Inputmanager::getKeyboard()
{
	return keyboard;
}