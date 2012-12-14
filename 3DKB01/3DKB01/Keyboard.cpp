#include "Keyboard.h"

Keyboard::Keyboard(HWND argWindow)
{
	InitializeKeyboard(argWindow);
}


Keyboard::~Keyboard(void)
{
}


 LPDIRECTINPUTDEVICE8 Keyboard::InitializeKeyboard(HWND argWindow)
 {
	
	 //creates the DirectInput Object. 
	DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&p_dx_KeybObject, NULL);
	//You need to pass a handle to the current application, the DirectX version, an interface ID, the pointer to the stucture we want to be initialised, and a pointer that can be used for more advanced stuff. 
	
	//Now your IDE has been set up to use DirectInput, let’s create the keyboard device. This must be done by the CreateDevice method of your keyboard Object:
	 p_dx_KeybObject->CreateDevice(GUID_SysKeyboard, &p_dx_KeybDevice, NULL);

	 p_dx_KeybDevice->SetDataFormat(&c_dfDIKeyboard);
	 p_dx_KeybDevice->SetCooperativeLevel(argWindow, DISCL_FOREGROUND|DISCL_NONEXCLUSIVE);
	
	 //call aquire method
	 Aquire();

	return p_dx_KeybDevice;
 }

 void Keyboard::Aquire()
 {
	 //try and aquire 5 times in case initial aquire fails.
	 for(int i = 0; i < 5 ; ++i)
	 {
		p_dx_KeybDevice->Acquire();
	 }
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
	p_Keyb->GetDeviceState(sizeof(chr_KeybState),(LPVOID)&chr_KeybState);

	//Now a bit of a detailed part, that I have included only to be complete. 
	//For every key, 1 byte is reserved in our buffer. 
	//When a key is pressed and the keyboard state is put into our buffer, only the first bit of the byte corresponding to that key will be turned to ‘1’, 
	//the other 7 bits of that byte are not affected. So what we’re interested in, is only the first bit. 
	//One way to separate this bit from the rest, is to divide the number by 128 (=2^7). So if the result of this division is 1, the key has been pressed.

	if (chr_KeybState[DIK_ESCAPE]/128)
	{
		// Open menu
	}
 }

