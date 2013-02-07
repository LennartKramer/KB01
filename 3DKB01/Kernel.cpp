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

RendererInterface* Kernel::getRenderer2()
{
	return renderer2;
}

Resourcemanager* Kernel::getResourcemanager()
{
	return resourcemanager;
}

Inputmanager* Kernel::getInputmanager()
{
	return inputmanager;
}

void Kernel::initialize(std::string argsceneName)
{
	Logger::message("----start initializing----");
	HRESULT result;


		windowmanager->createWindow(messageHandler, TEXT("window1"), 100, 100, 600, 600, TEXT("window1"));

	//Show all the windows, available in the list.
	windowmanager->showWindows();

	/*
	/ Create a Renderer from DirectX
	/ First initialize the device which will be used to add
	/ objects to. Then initialize the vertices, vertexes, indexes,
	/ matrices and geometry used to draw to a scene.
	*/
	renderer = new RendererDirectX();
	renderer->initD3D(windowmanager->getWindow("window1")->getHandle());

	resourcemanager->setDevice(renderer->getDevice());

	inputmanager->CreateKeyboard(windowmanager->getWindow("window1")->getHandle());
	inputmanager->CreateMouse(windowmanager->getWindow("window1")->getHandle());

	Logger::message("----start creating scene----");
	scenemanager->createSceneFromFile("level1.llf", renderer);

	Logger::message("----start the programLoop----");
	programLoop(argsceneName);

	Logger::message("----start cleaning up----");
	cleanup();
}

// -------------------------------------------------
/* programLoop */
// This is what the program will do in idle time.
// -------------------------------------------------
void Kernel::programLoop(std::string argsceneName) 
{
	Scene* focusedScene = scenemanager->getScene(argsceneName);
	// Basically, we loop as long as we don't get the QUIT message.
	while (windowmanager->update()) 
	{
			//Reading input from keyboard and mouse.
			int keyboardInput = inputmanager->getKeyboard()->ReadKeyboard();
			inputmanager->getMouse()->ReadMouse();
			std::stringstream ss;
			for(int i = 1; i <= windowmanager->getWindowAmount(); i++)
			{
				ss << i;
				std::string currentWindow = "window" + ss.str();
				scenemanager->drawScene(focusedScene,inputmanager->getMouse()->getXcoord(),inputmanager->getMouse()->getYcoord() ,inputmanager->getMouse()->IsMouseRButtonDown(), inputmanager->getKeyboard()->getKey(), getWindowmanager()->getWindow(currentWindow)->getHandle());
				ss.str("");
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
