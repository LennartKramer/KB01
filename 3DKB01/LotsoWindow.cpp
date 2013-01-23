#include "LotsoWindow.h"
#include <Windows.h>

// -------------------------------------------------
/* Constructor */
// -------------------------------------------------
LotsoWindow::LotsoWindow(WNDPROC messageHandler, LPCTSTR title, int x, int y, int width, int height, LPTSTR argName) 
{

	// UINT style - The style of the window.
	windowClass.style = NULL;

	// WNDPROC lpfnWndProc - The message handler to use.
	windowClass.lpfnWndProc = messageHandler;

	// int cbClsExtra & cbWndExtra - Extra bytes to assign.
	windowClass.cbClsExtra = 0;
	windowClass.cbWndExtra = 0;

	// HINSTANCE hInstance - The thread where this window will be created.
	windowClass.hInstance = GetModuleHandle(NULL);

	// HICON hIcon - The big icon for this window class.
	windowClass.hIcon = NULL;

	// HCURSOR hCursor - The mouse cursor to show in this window.
	windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);

	// HRBUSH hbrBackground - The background colour.
	windowClass.hbrBackground = NULL;

	// LPCTSTR lpszMenuName - The menu resource to use.
	windowClass.lpszMenuName = NULL;

	// LPCTSTR lpszClassName - What name to define to this new window class.
	windowClass.lpszClassName = title;

	RegisterClass(&windowClass);

	lotsoWindow = CreateWindow(title, title, WS_OVERLAPPEDWINDOW, x, y, width, height, GetDesktopWindow(), NULL, windowClass.hInstance, NULL);

	name = argName;
}

// -------------------------------------------------
/* Destructor */
// -------------------------------------------------
LotsoWindow::~LotsoWindow() { 
// We'll unregister the window now, using the parameters saved in windowClass.
UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);

// And we'll destroy the window too, just to be safe.
if (lotsoWindow != NULL) { DestroyWindow(lotsoWindow); lotsoWindow = NULL; }
}
