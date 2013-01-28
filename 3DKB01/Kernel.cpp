#include "Kernel.h"
#include <Windows.h>

LRESULT CALLBACK messageHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

Kernel::Kernel(void)
{
}

Kernel::Kernel(bool sandboxinterface)
{
	if(!sandboxinterface)
	{
		Logger::clearLog();
		Logger::message("----program started----");

		// create all managers
		windowmanager = new Windowmanager();
		resourcemanager = new Resourcemanager();
		scenemanager = new Scenemanager(resourcemanager);
		inputmanager = new Inputmanager();
		RendererInterface* directX = new RendererDirectX();	
	}
}



Kernel::~Kernel(void)
{
	// Leave this empty for now.
}

void Kernel::createManagers(Windowmanager* argWindowmanager, Resourcemanager* argResourcemanager, Scenemanager* argScenemanager, Inputmanager* argInputmanager, RendererInterface* argRendererInterface)
{
	windowmanager = argWindowmanager;
	resourcemanager = argResourcemanager;
	scenemanager = argScenemanager;
	inputmanager = argInputmanager;
	renderer = argRendererInterface;
}

Scenemanager* Kernel::getScenemanager()
{
	return scenemanager;
}

Windowmanager* Kernel::getWindowmanager()
{
	return windowmanager;
}

RendererInterface* Kernel::getRenderer()
{
	return renderer;
}

Resourcemanager* Kernel::getResourcemanager()
{
	return resourcemanager;
}

Inputmanager* Kernel::getInputmanager()
{
	return inputmanager;
}

void Kernel::sandBoxInterface() {
	/*
	std::cout << "Welcome to the Sandbox Interface. Choose an option:" << std::endl;
	std::cout << "Choose 1 to create a window." << std::endl;
	std::cout << "Choose 2 to create a scene." << std::endl;
	std::cout << "Choose 3 to choose your textures." << std::endl;
	std::cout << "Choose 4 to choose your meshes." << std::endl;
	std::cout << "Choose 5 to initialize." << std::endl;

	int option;
	std::cin >> option;
	switch(option)
	{
		case 1: 
	}
	*/
}

void Kernel::noobinterface()
{
	initialize();
}

void Kernel::initialize()
{
	Logger::message("----start initializing----");
	HRESULT result;
	// create all managers

	//windowmanager = Windowmanager();
	//
	//scenemanager = Scenemanager();
	//resourcemanager = Resourcemanager();
	//inputmanager = Inputmanager();

	// create and show first window
	windowmanager->createWindow(messageHandler, TEXT("window1"), 100, 100, 600, 600, TEXT("window1"));
	//windowmanager.createWindow(messageHandler, TEXT("window2"), 100, 100, 600, 600, TEXT("window2"));
	windowmanager->getWindow("window1")->show();
	//windowmanager.getWindow("window2")->show();
	/*
	/ LPCSTR bitmap - A long string used to open a bitmapfile.
	/ initializeDimensions - Find the value for the offset, width
	/ height of the bitmap file and store them into the SceneHeightmap
	/ class.
	*/

	/*
	/ Create a Renderer from DirectX
	/ First initialize the device which will be used to add
	/ objects to. Then initialize the vertices, vertexes, indexes,
	/ matrices and geometry used to draw to a scene.
	*/

	renderer = new RendererDirectX();
	renderer->initD3D(windowmanager->getWindow("window1")->getHandle());
	//Logger::message(result, "initialize direct3d...");

	resourcemanager->setDevice(renderer->getDevice());

	//LPDIRECT3DSURFACE9 pBackBuffer = NULL;
	//directX->getSwapChain("swap1")->GetBackBuffer(0, D3DBACKBUFFER_TYPE_MONO, &pBackBuffer);
	//directX->getDevice()->SetRenderTarget(0, pBackBuffer);
	
	//int swapping;
	//std::cin >> swapping;

	//directX->getSwapChain("swap2")->GetBackBuffer(0, D3DBACKBUFFER_TYPE_MONO, &pBackBuffer);
	//directX->getDevice()->SetRenderTarget(0, pBackBuffer);

	inputmanager->CreateKeyboard(windowmanager->getWindow("window1")->getHandle());
	inputmanager->CreateMouse(windowmanager->getWindow("window1")->getHandle());

	Logger::message("----start creating scene----");
	scenemanager->createSceneFromFile("level1.llf", renderer);

	Logger::message("----start the programLoop----");
	programLoop();

	Logger::message("----start cleaning up----");
	cleanup();
}

//void Kernel::bindWindowScene(LotsoWindow* argWindow, Scene* argScene)
//{
	//windowSceneBind[argWindow] = argScene;
	//windowSceneBind.insert(std::pair<eWindow*, Scene*>(argWindow, argScene));
//}

// -------------------------------------------------
/* programLoop */
// This is what the program will do in idle time.
// -------------------------------------------------
void Kernel::programLoop() 
{
	Scene* focusedScene = scenemanager->getScene("level1.llf");

	// So, let's process those messages.
	MSG msg;
	ZeroMemory(&msg, sizeof(msg)); // Just incase there's something there.

	// Basically, we loop as long as we don't get the QUIT message.
	while (msg.message != WM_QUIT) {
		// Move the camera position when one of the following cases exists.
		// Using a CASE statement.

		// Are there any messages waiting to be processed?
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			// Translate it and send it off for processing.
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		} 
		else
		{
			//Reading input from keyboard and mouse.
			int keyboardInput = inputmanager->getKeyboard()->ReadKeyboard();
			inputmanager->getMouse()->ReadMouse();

			//std::cout <<"   SKey is " << inputmanager.getKeyboard()->iskeySPressed() ;
			scenemanager->drawScene(focusedScene,inputmanager->getMouse()->getCoordMouse(),inputmanager->getMouse()->IsMouseRButtonDown(), inputmanager->getKeyboard()->getKey());

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
	windowmanager->cleanup();
}

RendererInterface* Kernel::getDirectX(void)
{
	return renderer;
};
