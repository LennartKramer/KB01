#ifndef __Keyboard_h__
#define __Keyboard_h__

#include <d3d9.h>
#include <dinput.h> 
#include <Windows.h>
#include "VECTOR.h"




class Keyboard
{
public:
	Keyboard(HWND argWindow);
	~Keyboard(void);
	bool InitializeKeyboard(void);
	bool GoAcquire(void);
	void SaveReleaseDevice(void);
	int ReadKeyboard(void);
	bool IsEscapePressed(void);
	Vector getKey();
private:
	float				 changeX;
	float				 changeY;
	float				 changeZ;
	bool				 escapePressed;
	HRESULT				 hr;
	HWND				 hwnd;
	LPDIRECTINPUT8		 p_dx_KeybObject;
	LPDIRECTINPUTDEVICE8 p_dx_KeybDevice;


};

#endif