#ifndef __Mouse_h__
#define __Mouse_h__

#include <d3d9.h>
#include <dinput.h> 
#include <Windows.h>
#include "BufferedMouse.h"

class Mouse
{
public:
	Mouse(HWND argWindow);
	~Mouse(void);
	bool InitializeMouse();
	bool GoAcquire();
	void SaveReleaseDevice();
	void ReadMouse(LPDIRECTINPUTDEVICE8);
	void setMouseBuffer(); 
	void ResetMouseStruct();
	LPDIRECTINPUTDEVICE8 getMouseDevice();
//	bool ProcessKBInput(byte argKeyIsPressed);
private:	
	BufferedMouse		 bufferedMouse;
	HWND				 hwnd;	
	HRESULT				 hr;
	LPDIRECTINPUT8		 p_dx_MouseObject;
	LPDIRECTINPUTDEVICE8 p_dx_MouseDevice;
};

#endif