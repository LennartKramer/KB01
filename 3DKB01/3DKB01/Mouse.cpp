#include "Mouse.h"
#include <iostream>

Mouse::Mouse(HWND argWindow)
{
	const int MOUSEBUFFER = 8;
	DIPROPDWORD  dipdw; 
	dipdw.diph.dwSize			= sizeof(DIPROPDWORD);
	dipdw.diph.dwHeaderSize		= sizeof(DIPROPHEADER);
	dipdw.diph.dwObj			= 0;
	dipdw.diph.dwHow			= DIPH_DEVICE;
	dipdw.dwData				= MOUSEBUFFER;
	hwnd						= argWindow;
	
	ResetMouseStruct();
	//InitializeMouse(argWindow);
}

Mouse::~Mouse(void)
{
}

bool Mouse::InitializeMouse()
 {
	DIPROPDWORD  dipdw; 
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
	 
	result = p_dx_MouseDevice->SetDataFormat(&c_dfDIMouse);
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
	 
	result = p_dx_MouseDevice->SetProperty( DIPROP_BUFFERSIZE, &dipdw.diph );
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

void Mouse::setMouseBuffer()
{
	DIDEVICEOBJECTDATA od;
	DWORD elements = 1;

	HRESULT hr = p_dx_MouseDevice->GetDeviceData( sizeof(DIDEVICEOBJECTDATA), &od, &elements, 0 );
	//&elements = number of elements in deviceData. 
	
	if (FAILED(hr))
	{
	// It's possible that we lost access to the keyboard
	// Here we acquire access to the keyboard again
	GoAcquire();
	return;
	}


	// Switch case to get the data from the mouse
	switch (od.dwOfs) 
	{
		// Mouse horizontal motion
		case DIMOFS_X:
			bufferedMouse.positionX += static_cast<long>(od.dwData);
			break;

		// Mouse vertical motion
		case DIMOFS_Y:
			bufferedMouse.positionY += static_cast<long>(od.dwData);
			break;

		// Mouse left button
		case DIMOFS_BUTTON0:
			if ( (long)od.dwData == 0 )
			{
				bufferedMouse.button0 = false;
			}
			else
			{
				bufferedMouse.button0 = true;
			}
			break;

		// Mouse left button
		case DIMOFS_BUTTON1:
			if ( static_cast<long>(od.dwData) == 0 )
			{
				bufferedMouse.button1 = false;
			}
			else
			{
				bufferedMouse.button1 = true;
			}
			break;

		// Mousewheel button
		case DIMOFS_BUTTON2:
			if ( static_cast<long>(od.dwData) == 0 )
			{
				bufferedMouse.button2 = false;
			}
			else
			{
				bufferedMouse.button2 = true;
			}
			break;
		
		// Button 3
		case DIMOFS_BUTTON3:
			if ( static_cast<long>(od.dwData) == 0 )
			{
				bufferedMouse.button3 = false;
			}
			else
			{
				bufferedMouse.button3 = true;
			}
			break;

		// Button 4
		case DIMOFS_BUTTON4:
			if ( static_cast<long>(od.dwData) == 0 )
			{
				bufferedMouse.button4 = false;
			}
			else
			{
				bufferedMouse.button4 = true;
			}
			break;

		// Button 5
		case DIMOFS_BUTTON5:
			if ( static_cast<long>(od.dwData) == 0 )
			{
				bufferedMouse.button5 = false;
			}
			else
			{
				bufferedMouse.button5 = true;
			}
			break;

		// Button 6
		case DIMOFS_BUTTON6:
			if ( static_cast<long>(od.dwData) == 0 )
			{
				bufferedMouse.button6 = false;
			}
			else
			{
				bufferedMouse.button6 = true;
			}
			break;

		// Button 7
		case DIMOFS_BUTTON7:
			if ( static_cast<long>(od.dwData) == 0 )
			{
				bufferedMouse.button7 = false;
			}
			else
			{
				bufferedMouse.button7 = true;
			}
			break;

		// Mouse wheel
		case DIMOFS_Z:
			bufferedMouse.z += static_cast<long>(od.dwData);
			break;
	}
}

void Mouse::ResetMouseStruct()
{
	bufferedMouse.positionX = 0;
	bufferedMouse.positionY = 0;
	bufferedMouse.z = 0;
	bufferedMouse.button0 = false;
	bufferedMouse.button1 = false;
	bufferedMouse.button2 = false;
	bufferedMouse.button3 = false;
	bufferedMouse.button4 = false;
	bufferedMouse.button5 = false;
	bufferedMouse.button6 = false;
	bufferedMouse.button7 = false;	
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

LPDIRECTINPUTDEVICE8 Mouse::getMouseDevice()
{
	return p_dx_MouseDevice;
}

void Mouse::ReadMouse(LPDIRECTINPUTDEVICE8 argMouseDevice)
{
	
}