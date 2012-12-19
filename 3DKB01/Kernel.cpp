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
	sceneHeightmap = SceneHeightmap();
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
	inputmanager = Inputmanager();
	// create and show first window
	windowmanager.createWindow(messageHandler, TEXT("window1"), 100, 100, 600, 600, TEXT("window1"));
	windowmanager.getWindow("window1")->show();
	/*
	/ LPCSTR bitmap - A long string used to open a bitmapfile.
	/ initializeDimensions - Find the value for the offset, width
	/ height of the bitmap file and store them into the SceneHeightmap
	/ class.
	*/
	LPCSTR bitmap = "heightmap.bmp";
	sceneHeightmap.initializeDimensions(bitmap);
	/*
	/ Create a Renderer from DirectX
	/ First initialize the device which will be used to add
	/ objects to. Then initialize the vertices, vertexes, indexes,
	/ matrices and geometry used to draw to a scene.
	*/

	directX = new RendererDirectX();
	directX->initD3D(windowmanager.getWindow("window1")->getHandle());
	std::cout << "stap1" << std::endl;
	directX->setupMatrices();
	std::cout << "stap2" << std::endl;

	/*
	directX->initializeIndices(windowmanager.getWindow("window1")->getHandle(), directX->getDevice(),
		sceneHeightmap.getBitmapWidth(), sceneHeightmap.getBitmapHeight());
	std::cout << "stap3" << std::endl;
	directX->initializeVertices(windowmanager.getWindow("window1")->getHandle(), directX->getDevice(),
		sceneHeightmap.getBitmapOffset() ,sceneHeightmap.getBitmapWidth(), sceneHeightmap.getBitmapHeight());
	std::cout << "stap4" << std::endl;
	*/
	// directX->initGeometry(); - Drawing a landscape instead of a triangle now.
	/*
	/ loadMaterials
	/ Initialize a Material Buffer and a Texture Buffer,
	/ used to draw to the scene.
	*/
	resourcemanager.loadMaterials(directX->getDevice());

	inputmanager.CreateKeyboard(windowmanager.getWindow("window1")->getHandle());
	inputmanager.CreateMouse(windowmanager.getWindow("window1")->getHandle());
}

void Kernel::createSingleScene()
{
	scenemanager.createScene();
	addRendererToScene();
	scenemanager.getScene("scene1")->addEntityModel();
	scenemanager.getScene("scene1")->addEntityCamera();
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
		//Reading input from keyboard and mouse.
		inputmanager.getKeyboard()->ReadKeyboard();
		inputmanager.getMouse()->ReadMouse();

		//Exit program when escape is pushed.
		if (inputmanager.getKeyboard()->IsEscapePressed())
		{
			msg.message = WM_QUIT;
		}


		// Are there any messages waiting to be processed?
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			// Translate it and send it off for processing.
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		} 
		else
		{
			directX->render(resourcemanager.getMeshMaterials(), 
				resourcemanager.getMeshTextures(), resourcemanager.getDwNumMaterials(),
				resourcemanager.getMesh(), sceneHeightmap.getBitmapWidth(), sceneHeightmap.getBitmapHeight());
			std::cout << ".";
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

RendererDirectX* Kernel::getDirectX(void)
{
	return directX;
};
