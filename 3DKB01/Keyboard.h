#ifndef __Keyboard_h__
#define __Keyboard_h__

#include <d3d9.h>
#include <dinput.h> 
#include <Windows.h>

class Keyboard
{
public:
	Keyboard(HWND argWindow);
	~Keyboard();
	bool InitializeKeyboard();
	bool GoAcquire();
	void SaveReleaseDevice();
	int ReadKeyboard();
	bool IsEscapePressed();
private:
	bool				 escapePressed;
	HRESULT				 hr;
	HWND				 hwnd;
	LPDIRECTINPUT8		 p_dx_KeybObject;
	LPDIRECTINPUTDEVICE8 p_dx_KeybDevice;
};

#endif