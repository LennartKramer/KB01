#ifndef __Mouse_h__
#define __Mouse_h__

#include <d3dx9.h>
#include <dinput.h> 
#include <Windows.h>

class Mouse
{
public:
	Mouse(HWND argWindow);
	~Mouse(void);
	bool InitializeMouse();
	bool GoAcquire();
	void SaveReleaseDevice();
	bool IsDown(int button);
	bool IsUp(int button);
	int GetWheel();
	int ReadMouse();
	int getXcoord();
	int getYcoord();
	POINT getCoordMouse();
	void setCoordMouse(POINT Coord);

	bool IsMouseLButtonDown();
	bool IsMouseRButtonDown();

private:	
	POINT				 absoluteMouse;
	DIMOUSESTATE2		 mousestate;
	HWND				 hwnd;	
	HRESULT				 hr;
	LPDIRECTINPUT8		 p_dx_MouseObject;
	LPDIRECTINPUTDEVICE8 p_dx_MouseDevice;

};
#endif