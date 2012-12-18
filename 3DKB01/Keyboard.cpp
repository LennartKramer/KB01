#include <iostream>
#include "Keyboard.h"

Keyboard::~Keyboard()
{
}

Keyboard::Keyboard(HWND argWindow)
{
	p_dx_KeybObject		= NULL; 
	p_dx_KeybDevice		= NULL; 
	hwnd				= argWindow;	

	if (InitializeKeyboard())
	{
		std::cout << "Initialize Keyboard Method Succes";
	}
	else
	{
		std::cout << "Initialize Keyboard Method Failed";
	}
}

LPDIRECTINPUTDEVICE8 Keyboard::getKeybDevice()
{
	return p_dx_KeybDevice;
}

bool Keyboard::InitializeKeyboard()
{
	 //creates the DirectInput Object. 
	hr = DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&p_dx_KeybObject, NULL);
	if FAILED( hr ) 
	{
		return false; 
	}
	//You need to pass a handle to the current application, the DirectX version, an interface ID, the pointer to the stucture we want to be initialised, and a pointer that can be used for more advanced stuff. 
	
	//Now your IDE has been set up to use DirectInput, let�s create the keyboard device. This must be done by the CreateDevice method of your keyboard Object:
	hr = p_dx_KeybObject->CreateDevice(GUID_SysKeyboard, &p_dx_KeybDevice, NULL);
	if FAILED( hr ) 
	{ 
		SaveReleaseDevice(); 
		return false; 
	}

	p_dx_KeybDevice->SetDataFormat(&c_dfDIKeyboard);
	if FAILED( hr ) 
	{ 
		SaveReleaseDevice(); 
		return false; 
	} 
	
	p_dx_KeybDevice->SetCooperativeLevel(hwnd, DISCL_FOREGROUND|DISCL_NONEXCLUSIVE);
	if FAILED( hr )
	{ 
		SaveReleaseDevice(); 
		return false; 
	} 

	GoAcquire();

	return true;
 }

 bool Keyboard::GoAcquire()
 {
	 //try and aquire 5 times in case initial aquire fails.
	 for(int i = 0; i < 5 ; ++i)
	 {
		if( SUCCEEDED( p_dx_KeybDevice->Acquire() ) )
		{
			return true;
		}
	 }
	 return false;
 }

void Keyboard::SaveReleaseDevice()
{
	if(p_dx_KeybObject)
	{
		if(p_dx_KeybDevice)
		{
			p_dx_KeybDevice->Unacquire();
			p_dx_KeybDevice->Release();
		}
		p_dx_KeybObject->Release();
	}
}	

 void Keyboard::ReadKeyboard(LPDIRECTINPUTDEVICE8 p_Keyb)
 {
	 // So first define a buffer to hold these bytes and then store the keyboard state in it:
	char chr_KeybState[256];

	//The parameters are of course the size of our prepared buffer and the pointer to this buffer. 
	//The standard data format of a keyboard corresponds to an array of 256 bytes, and the size of a char is the same as the size of a byte, 8 bits. 
	//This is why an array of chars is used.
	
	hr = p_Keyb->GetDeviceState(sizeof(chr_KeybState),(LPVOID)&chr_KeybState);
	if (FAILED(hr))
	{
		// It's possible that we lost access to the keyboard
		// Here we acquire access to the keyboard again
		GoAcquire();
		return;
	}


	//Now a bit of a detailed part, that I have included only to be complete. 
	//For every key, 1 byte is reserved in our buffer. 
	//When a key is pressed and the keyboard state is put into our buffer, only the first bit of the byte corresponding to that key will be turned to �1�, 
	//the other 7 bits of that byte are not affected. So what we�re interested in, is only the first bit. 
	//One way to separate this bit from the rest, is to divide the number by 128 (=2^7). So if the result of this division is 1, the key has been pressed.

	if (chr_KeybState[DIK_ESCAPE]/128)
	{
		std::cout << "Escape Button Pressed.";
	}

	 if (chr_KeybState[DIK_DELETE]/128)
	{
		std::cout << "Delete Button Pressed.";
	}

 }
