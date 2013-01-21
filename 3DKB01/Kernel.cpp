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

	/*
	/ Create a Renderer from DirectX
	/ First initialize the device which will be used to add
	/ objects to. Then initialize the vertices, vertexes, indexes,
	/ matrices and geometry used to draw to a scene.
	*/

	directX = new RendererDirectX();
	directX->initD3D(windowmanager.getWindow("window1")->getHandle());
	resourcemanager.setDevice(directX->getDevice());

	inputmanager.CreateKeyboard(windowmanager.getWindow("window1")->getHandle());
	inputmanager.CreateMouse(windowmanager.getWindow("window1")->getHandle());
}

void Kernel::createSingleScene()
{
	/*
	/ loadMaterials
	/ Initialize a Material Buffer and a Texture Buffer,
	/ used to draw to the scene.
	*/	
	resourcemanager.loadTexture("textures/terrain.bmp");
	resourcemanager.loadTexture("textures/skybox.png");
	resourcemanager.loadMesh("meshes/tiger.x");
	scenemanager.createScene("scene1", directX);

	Vector modelPosition = Vector(0.0, 0.0, 1.0);
	Vector modelOrientation = Vector(0.0, 0.0, 0.0);

	ResourceModel* resourcemodel = resourcemanager.getResourceModel("meshes/tiger.x");
	ResourceTexture* resourcetexture  = resourcemanager.getResourceTexture("tiger.bmp");

	scenemanager.getScene("scene1")->addEntityModel(modelPosition , modelOrientation, resourcemodel, resourcetexture);

	modelPosition = Vector(0.0, 0.0, 0.0);
	modelOrientation = Vector(0.0, D3DX_PI/2, 0.0);

	resourcemodel = resourcemanager.getResourceModel("meshes/tiger.x");
	resourcetexture  = resourcemanager.getResourceTexture("tiger.bmp");

	scenemanager.getScene("scene1")->addEntityModel(modelPosition , modelOrientation, resourcemodel, resourcetexture);

	//Vector cameraPosition = Vector(0.5, 40, -60);
	//Vector cameraPosition = Vector(0.5, 0.5, 0.5);
	//Vector cameraDirection = Vector(-0.5, 0.5, 0.5);
	//Vector cameraUp = Vector(0.0, 1.0, 0.0);

	resourcetexture  = resourcemanager.getResourceTexture("textures/skybox.png");
	scenemanager.getScene("scene1")->addSkybox(resourcetexture);
	
	resourcetexture  = resourcemanager.getResourceTexture("textures/terrain.bmp");
	scenemanager.getScene("scene1")->addTerrain(resourcetexture);

	scenemanager.getScene("scene1")->addEntityCamera();
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
void Kernel::programLoop() {
	Scene* focusedScene = scenemanager.getScene("scene1");

	// So, let's process those messages.
	MSG msg;
	ZeroMemory(&msg, sizeof(msg)); // Just incase there's something there.

	// Basically, we loop as long as we don't get the QUIT message.
	while (msg.message != WM_QUIT) {
		//Reading input from keyboard and mouse.
		inputmanager.getKeyboard()->reset();
		int keyboardinput = inputmanager.getKeyboard()->ReadKeyboard();
		inputmanager.getMouse()->ReadMouse();

		//Exit program when escape is pushed.

		
		// Move the camera position when one of the following cases exists.
		// Using a CASE statement.
		/*
		if(inputmanager.getKeyboard()->ReadKeyboard() == 3)
		{
			focusedScene->getCamera()->changePosition(3);
		} else if(inputmanager.getKeyboard()->ReadKeyboard() == 4)
		{
			focusedScene->getCamera()->changePosition(4);
		} else if(inputmanager.getKeyboard()->ReadKeyboard() == 5)
		{
			focusedScene->getCamera()->changePosition(5);
		} else if(inputmanager.getKeyboard()->ReadKeyboard() == 6)
		{
			focusedScene->getCamera()->changePosition(6);
		}
		*/
		// Are there any messages waiting to be processed?
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			// Translate it and send it off for processing.
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		} 
		else
		{
			//std::cout <<"   SKey is " << inputmanager.getKeyboard()->iskeySPressed() ;
			scenemanager.drawScene(scenemanager.getScene("scene1"),inputmanager.getMouse()->getCoordMouse(),inputmanager.getMouse()->IsMouseRButtonDown(),
				inputmanager.getKeyboard()->getargTerSide(),inputmanager.getKeyboard()->getargTerFront(),inputmanager.getKeyboard()->getargTerUp());
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

RendererInterface* Kernel::getDirectX(void)
{
	return directX;
};
