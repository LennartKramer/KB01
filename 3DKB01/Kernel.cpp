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
	LPCTSTR bitmap = "heightmap.bmp";
	sceneHeightmap.initializeDimensions(bitmap, windowmanager.getWindow("window1")->getHandle());
	/*
	/ Create a Renderer from DirectX
	/ First initialize the device which will be used to add
	/ objects to. Then initialize the vertices, vertexes, indexes,
	/ matrices and geometry used to draw to a scene.
	*/

	directX = new RendererDirectX();
	directX->initD3D(windowmanager.getWindow("window1")->getHandle());


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

	resourcemanager.setDevice(directX->getDevice());
	resourcemanager.loadMesh("meshes/tiger.x");
	//resourcemanager.loadMaterials(directX->getDevice());

	//ResourceModel* resourcemodel = resourcemanager.getResourceModel("meshes/tiger.x");
	//ResourceTexture* resourcetexture  = resourcemanager.getResourceTexture("tiger.bmp");

	inputmanager.CreateKeyboard(windowmanager.getWindow("window1")->getHandle());
	inputmanager.CreateMouse(windowmanager.getWindow("window1")->getHandle());
}

void Kernel::createSingleScene()
{
	scenemanager.createScene("scene1", directX);

	Vector modelPosition = Vector(2.0, 0.0, 0.0);
	Vector modelOrientation = Vector(0.0, 0.0, 0.0);

	ResourceModel* resourcemodel = resourcemanager.getResourceModel("meshes/tiger.x");
	ResourceTexture* resourcetexture  = resourcemanager.getResourceTexture("tiger.bmp");

	scenemanager.getScene("scene1")->addEntityModel(modelPosition , modelOrientation, resourcemodel, resourcetexture);

	modelPosition = Vector(-2.0, 0.0, 0.0);
	modelOrientation = Vector(0.0, D3DX_PI/2, 0.0);

	resourcemodel = resourcemanager.getResourceModel("meshes/tiger.x");
	resourcetexture  = resourcemanager.getResourceTexture("tiger.bmp");

	scenemanager.getScene("scene1")->addEntityModel(modelPosition , modelOrientation, resourcemodel, resourcetexture);

	Vector cameraPosition = Vector(0.0, 5.0, -8.0);
	Vector cameraDirection = Vector(0.0, 0.0, 0.0);
	Vector cameraUp = Vector(0.0, 1.0, 0.0);

	
	scenemanager.getScene("scene1")->addEntityCamera(cameraPosition, cameraDirection, cameraUp);
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
	// So, let's process those messages.
	MSG msg;
	ZeroMemory(&msg, sizeof(msg)); // Just incase there's something there.

	// Basically, we loop as long as we don't get the QUIT message.
	while (msg.message != WM_QUIT) {
		//Reading input from keyboard and mouse.
		int keyboardinput = inputmanager.getKeyboard()->ReadKeyboard();
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
			/*
			ResourceModel* resourcemodel = resourcemanager.getResourceModel("meshes/tiger.x");
			ResourceTexture* resourcetexture  = resourcemanager.getResourceTexture("tiger.bmp");

			directX->render(			
				resourcetexture->getMeshTextures(), 
				resourcemodel->getMesh(), 
				sceneHeightmap.getBitmapWidth(), 
				sceneHeightmap.getBitmapHeight());
			*/	

			scenemanager.drawScene(scenemanager.getScene("scene1"));

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
