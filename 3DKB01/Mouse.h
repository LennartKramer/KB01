#ifndef __Mouse_h__
#define __Mouse_h__

#include <d3d9.h>
#include <dinput.h> 
#include <Windows.h>
#include "BufferedMouse.h"

class Mouse
{
public:
	Mouse();
	Mouse(HWND argWindow);
	~Mouse(void);
	bool InitializeMouse();
	bool GoAcquire();
	void SaveReleaseDevice();
	void SetMouseBuffer(); 
	void ResetMouseStruct();
	bool IsDown(int button);
	bool IsUp(int button);
	void GetCoords(int* x, int* y);
	int GetWheel();
	void Activate();
	void Deactivate();
	int ReadMouse();
	//BufferedMouse GetMouseInput();
private:	
//	BufferedMouse		 bufferedMouse;
	DIMOUSESTATE2		 mousestate;
	bool				 active;
	HWND				 hwnd;	
	HRESULT				 hr;
	LPDIRECTINPUT8		 p_dx_MouseObject;
	LPDIRECTINPUTDEVICE8 p_dx_MouseDevice;
};



#endif