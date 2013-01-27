#include <iostream>
#include "Keyboard.h"


Keyboard::Keyboard(HWND argWindow)
{
	escapePressed = false;
	hwnd = argWindow;	
	InitializeKeyboard();
	changeX = 0;
	changeY = 0;
	changeZ = 0;
}


/*
	Used to fill the keyboard object "p_dx_KeybObject" and inputdevice "p_dx_KeybDevice".
	@param	void
	@return	Returns true if the keyboard device and object are succesfully created.
*/
bool Keyboard::InitializeKeyboard(void)
{
	 //creates the DirectInput Object by giving it the object handle "&p_dx_KeybObject". 
	hr = DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&p_dx_KeybObject, NULL);
	if FAILED( hr ) 
	{
		return false; 
	}
	
	//Creating the keyboard device by giving it the device handle "&p_dx_KeybDevice".
	hr = p_dx_KeybObject->CreateDevice(GUID_SysKeyboard, &p_dx_KeybDevice, NULL);
	if FAILED( hr ) 
	{ 
		SaveReleaseDevice(); 
		return false; 
	}

	//Sets the dataformat of the device to keyboard (joystick and mouse are other possibilities).
	p_dx_KeybDevice->SetDataFormat(&c_dfDIKeyboard);
	if FAILED( hr ) 
	{ 
		SaveReleaseDevice(); 
		return false; 
	} 
	
	//Establishes the cooperative level for this instance of the device. 
	//The cooperative level determines how this instance of the device interacts with other instances of the device and the rest of the system. 
	p_dx_KeybDevice->SetCooperativeLevel(hwnd, DISCL_FOREGROUND|DISCL_NONEXCLUSIVE);
	if FAILED( hr )
	{ 
		SaveReleaseDevice(); 
		return false; 
	} 

	//Acquire the device by using a custom method that tries it multiple times in case of initial failure.
	GoAcquire();

	return true;
 }


/*
	Obtains access to the input device. 
	@param	void
	@return	Returns true if the input device was acquired
*/
 bool Keyboard::GoAcquire(void)
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

/*
	Cleanup method to unacquire and release the device in a safe manner
	@param	void
	@return	Returns true if the input device was acquired
*/
void Keyboard::SaveReleaseDevice(void)
{
	if(p_dx_KeybObject)
	{
		if(p_dx_KeybDevice)
		{
			//Releases access to the device. 
			p_dx_KeybDevice->Unacquire();
			p_dx_KeybDevice->Release();
		}
		p_dx_KeybObject->Release();
	}
}	


/*
	Used to constantly read the keyboard.
	@param	void
	@return	returns a different int based on what key is pressed.
*/
 int Keyboard::ReadKeyboard(void)
 {

	 // So first define a buffer to hold these bytes and then store the keyboard state in it:
	char chr_KeybState[256];


	//The parameters are of course the size of our prepared buffer and the pointer to this buffer. 
	//The standard data format of a keyboard corresponds to an array of 256 bytes, and the size of a char is the same as the size of a byte, 8 bits. 
	//This is why an array of chars is used.
	
	hr = p_dx_KeybDevice->GetDeviceState(sizeof(chr_KeybState),(LPVOID)&chr_KeybState);
	if (FAILED(hr))
	{
		// It's possible that we lost access to the keyboard
		// Here we acquire access to the keyboard again
		GoAcquire();
		return 0;
	}

	//Now a bit of a detailed part, that I have included only to be complete. 
	//For every key, 1 byte is reserved in our buffer. 
	//When a key is pressed and the keyboard state is put into our buffer, only the first bit of the byte corresponding to that key will be turned to ‘1’, 
	//the other 7 bits of that byte are not affected. So what we’re interested in, is only the first bit. 
	//One way to separate this bit from the rest, is to divide the number by 128 (=2^7). So if the result of this division is 1, the key has been pressed.
	if (chr_KeybState[DIK_ESCAPE]/128)
	{
		 return escapePressed =true;
	}
	
	if (chr_KeybState[DIK_W]/128)
	{
		if(changeZ < 1)
		{
			changeZ++;
		}
	}

	if (chr_KeybState[DIK_A]/128)
	{
		if(changeX > -1)
		{
			changeX--;
		}
	}

	if (chr_KeybState[DIK_S]/128)
	{
		if(changeZ > -1)
		{
			changeZ--;
		}
	}

	if (chr_KeybState[DIK_D]/128)
	{
		if(changeX < 1)
		{
			changeX++;
		}
	}

	if (chr_KeybState[DIK_UP]/128)
	{
		if(changeY < 1)
		{
			changeY++;
		}
	}

	if (chr_KeybState[DIK_DOWN]/128)
	{
		if(changeY > -1)
		{
		changeY--;
		}
	}	
	return 1;
 }

/*
	
	@param	void
	@return	
*/
 bool Keyboard::IsEscapePressed(void)
 {
	 return escapePressed;
 }
 

 Vector Keyboard::getKey()
 {
	 Vector changedPosition = Vector(changeX, changeY, changeZ);
	 changeX = 0;
	 changeY = 0;
	 changeZ = 0;
	 return changedPosition;
 }


