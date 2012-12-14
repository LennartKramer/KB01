#include "Kernel.h"
#include <Windows.h>

LRESULT CALLBACK messageHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

Kernel::Kernel(void)
{
	directX = new RendererDirectX();
	windowmanager = Windowmanager();
	scenemanager = Scenemanager();
	resourcemanager = Resourcemanager();
	inputmanager = Inputmanager();
}


Kernel::~Kernel(void)
{
	// Leave this empty for now.
}

void Kernel::initialize()
{
	// create all managers
	windowmanager = Windowmanager();
	scenemanager = Scenemanager();
	resourcemanager = Resourcemanager();
	// create and show first window
	windowmanager.createWindow(messageHandler, TEXT("window1"), 100, 100, 600, 600, TEXT("window1"));
	windowmanager.getWindow("window1")->show();
	resourcemanager.retrieveTexturesAndModels();
	// initialize direct3d
	directX = new RendererDirectX();
	directX->initD3D(windowmanager.getWindow("window1")->getHandle());
	directX->initGeometry();
}

void Kernel::bindWindowScene(LotsoWindow* argWindow, Scene* argScene)
{
	windowSceneBind[argWindow] = argScene;
	//windowSceneBind.insert(std::pair<eWindow*, Scene*>(argWindow, argScene));
}

// -------------------------------------------------
/* programLoop */
// This is what the program will do in idle time.
// -------------------------------------------------
void Kernel::programLoop() {
	// So, let's process those messages.
	MSG msg;
	ZeroMemory(&msg, sizeof(msg)); // Just incase there's something there.

	// Basically, we loop as long as we don't get the QUIT message.
	while (msg.message != WM_QUIT) {
		// Are there any messages waiting to be processed?
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			// Translate it and send it off for processing.
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		} 
		else
		{
			directX->render();
		}
	}

}

//-----------------------------------------------------------------------------
/* messageHandler */
// This will manage incoming messages from the window.
//-----------------------------------------------------------------------------
LRESULT CALLBACK messageHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch(msg) {
		case WM_DESTROY:
		PostQuitMessage(EXIT_SUCCESS);
		return 0;
	}

// If we don't catch it, let the default message handler get it. That's this function.
return DefWindowProc(hwnd, msg, wParam, lParam);
}

void Kernel::cleanup() 
{
	windowmanager.cleanup();
}
