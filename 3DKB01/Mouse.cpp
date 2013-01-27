#include "Mouse.h"

Mouse::Mouse(HWND argWindow)
{
	hwnd = argWindow;
	InitializeMouse();
}

Mouse::~Mouse(void)
{
}

bool Mouse::IsDown(int button)
{
	if(mousestate.rgbButtons[button] & 0x80)
	{
		return true;
	}
	return false;
}

bool Mouse::IsUp(int button)
{
	return((mousestate.rgbButtons[button] & 0x80)!=0?false:true);
}

int Mouse::getXcoord()
{
	return mousestate.lX;
}

int Mouse::getYcoord()
{
	return mousestate.lY;
}

int Mouse::GetWheel()
{
	return(mousestate.lZ);
}

bool Mouse::InitializeMouse()
 {
	 //creates the DirectInput Object. 
	HRESULT result = DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&p_dx_MouseObject, NULL);
	if( FAILED( result ) )
	{
		return false;
	} 
	//You need to pass a handle to the current application, the DirectX version, an interface ID, the pointer to the stucture we want to be initialised, and a pointer that can be used for more advanced stuff. 
	
	//Now your IDE has been set up to use DirectInput, let’s create the keyboard device. This must be done by the CreateDevice method of your keyboard Object:
	result = p_dx_MouseObject->CreateDevice(GUID_SysMouse, &p_dx_MouseDevice, NULL);
	if( FAILED( result ) )
	{
		SaveReleaseDevice();
		return false;
	}
	 
	result = p_dx_MouseDevice->SetDataFormat(&c_dfDIMouse2);
	if( FAILED( result ) )
	{
		SaveReleaseDevice();
		return false;
	}

	result = p_dx_MouseDevice->SetCooperativeLevel(hwnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
	if( FAILED( result ) )
	{
		SaveReleaseDevice(); 
		return false;
	}
	 
	GoAcquire();
	return true;
 }

void Mouse::SaveReleaseDevice()
{
	if(p_dx_MouseObject)
	{
		if(p_dx_MouseDevice)
		{
			p_dx_MouseDevice->Unacquire();
			p_dx_MouseDevice->Release();
		}
		p_dx_MouseObject->Release();
	}
}	

bool Mouse::GoAcquire()
 {
	 //try and aquire 5 times in case initial aquire fails.
	 for(int i = 0; i < 5 ; ++i)
	 {
		if( SUCCEEDED( p_dx_MouseDevice->Acquire() ) )
		{
			return true;
		}
	 }
	 return false;
 }

int Mouse::ReadMouse()
{
	hr = p_dx_MouseDevice->GetDeviceState(sizeof(DIMOUSESTATE2), &mousestate);
	if(FAILED(hr))
	{
		if(hr = DIERR_INPUTLOST)
		{
			hr = p_dx_MouseDevice->Acquire();
			if(FAILED(hr))
			{
				if(hr==DIERR_OTHERAPPHASPRIO)
					return 2;
				else
					return 0;
			}
			p_dx_MouseDevice->GetDeviceState(sizeof(DIMOUSESTATE2), &mousestate);
		}
		else
		{
			return 0;
		}
	return 1;
	}
 }

void Mouse::setCoordMouse()
{
	if(mousestate.rgbButtons[1] & 0x80)
	{
		absoluteMouse.x = mousestate.lX;
		absoluteMouse.y = mousestate.lY;
	}

}


POINT Mouse::getCoordMouse()
{
	POINT coordMouse;
	coordMouse.x = mousestate.lX;
	coordMouse.y = mousestate.lY;

	mousestate.lX = absoluteMouse.x;
	mousestate.lY = absoluteMouse.y;

	return coordMouse;
}



bool Mouse::IsMouseLButtonDown()
{
	if(mousestate.rgbButtons[0] & 0x80)
 {
 return true;
 }

return false;

}

bool Mouse::IsMouseRButtonDown()
{
	if(mousestate.rgbButtons[1] & 0x80)
 {
 return true;
 }

return false;

}
