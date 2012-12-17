#ifndef __Keyboard_h__
#define __Keyboard_h__

#include <d3d9.h>
#include <dinput.h> 
#include <Windows.h>

class Keyboard
{
public:
	Keyboard(HWND argWindow);
	~Keyboard(void);
	LPDIRECTINPUTDEVICE8 InitializeKeyboard(HWND argWindow);
	void Aquire();
	void SaveReleaseDevice();
	void ReadKeyboard(LPDIRECTINPUTDEVICE8 p_Keyb);
//	bool ProcessKBInput(byte argKeyIsPressed);
private:
	HRESULT				 hr;
	LPDIRECTINPUT8		 p_dx_KeybObject;
	LPDIRECTINPUTDEVICE8 p_dx_KeybDevice;
};

#endif