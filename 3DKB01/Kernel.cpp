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

void Kernel::initialize()
{
	HRESULT result;
	// create all managers
	windowmanager = Windowmanager();
	
	scenemanager = Scenemanager();
	resourcemanager = Resourcemanager();
	inputmanager = Inputmanager();
	// create and show first window
	windowmanager.createWindow(messageHandler, TEXT("window1"), 100, 100, 600, 600, TEXT("window1"));
	//windowmanager.createWindow(messageHandler, TEXT("window2"), 100, 100, 600, 600, TEXT("window2"));
	windowmanager.getWindow("window1")->show();
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

	directX = new RendererDirectX();
	result = directX->initD3D(windowmanager.getWindow("window1")->getHandle());
	Logger::message(result, "initialize direct3d...");

	resourcemanager.setDevice(directX->getDevice());

	//LPDIRECT3DSURFACE9 pBackBuffer = NULL;
	//directX->getSwapChain("swap1")->GetBackBuffer(0, D3DBACKBUFFER_TYPE_MONO, &pBackBuffer);
	//directX->getDevice()->SetRenderTarget(0, pBackBuffer);
	
	//int swapping;
	//std::cin >> swapping;

	//directX->getSwapChain("swap2")->GetBackBuffer(0, D3DBACKBUFFER_TYPE_MONO, &pBackBuffer);
	//directX->getDevice()->SetRenderTarget(0, pBackBuffer);

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
	resourcemanager.loadTexture("textures/skybox.png");
	resourcemanager.loadTexture("textures/terrain.bmp");
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


	resourcetexture  = resourcemanager.getResourceTexture("textures/skybox.png");
	scenemanager.getScene("scene1")->addSkybox(resourcetexture);
	
	resourcetexture  = resourcemanager.getResourceTexture("textures/terrain.bmp");
	//scenemanager.getScene("scene1")->addTerrain(resourcetexture);

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
	Scene* focusedScene = scenemanager.getScene("level1.llf");

	// So, let's process those messages.
	MSG msg;
	ZeroMemory(&msg, sizeof(msg)); // Just incase there's something there.

	// Basically, we loop as long as we don't get the QUIT message.
	while (msg.message != WM_QUIT) {
		//Reading input from keyboard and mouse.
		inputmanager.getKeyboard()->reset();
		int keyboardinput = inputmanager.getKeyboard()->ReadKeyboard();
		inputmanager.getMouse()->ReadMouse();

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

			//std::cout <<"   SKey is " << inputmanager.getKeyboard()->iskeySPressed() ;
			scenemanager.drawScene(focusedScene,inputmanager.getMouse()->getCoordMouse(),inputmanager.getMouse()->IsMouseRButtonDown(),
				inputmanager.getKeyboard()->getargTerSide(),inputmanager.getKeyboard()->getargTerFront(),inputmanager.getKeyboard()->getargTerUp());

		}
	}

}

void Kernel::loadLevelFile(std::string argLevelfile)
{
	std::string line;
	std::ifstream infile;
	infile.open (argLevelfile);
	getline(infile,line);
	while(line != "meshes:") // skip lines until meshes is found.
        {
	        getline(infile,line); // Saves the line in "line".
        }
    getline(infile,line); // Saves the line in "line".
	while(line != "end") // load meshes from the lines until end is found
        {
			resourcemanager.loadMesh(line);
			getline(infile,line); // Saves the line in "line".
        }
	while(line != "textures:") // skip lines until textures is found.
        {
	        getline(infile,line); // Saves the line in "line".
        }
	getline(infile,line); // Saves the line in "line".
	while(line != "end") // load textures from the lines until end is found
        {
			resourcemanager.loadTexture(line);
			getline(infile,line); // Saves the line in "line".
        }
	while(line != "heightmap:") // skip lines until heightmap is found.
        {
	        getline(infile,line); // Saves the line in "line".
        }
	    getline(infile,line); // Saves the line in "line".
		getline(infile,line); // Saves the line in "line".
		resourcemanager.loadTexture(line); 
	while(line != "skybox:") // skip lines until skybox is found.
        {
	        getline(infile,line); // Saves the line in "line".
        }
		getline(infile,line); // Saves the line in "line".
	while(line != "end") // load skybox from the lines until end is found
        {
			resourcemanager.loadTexture(line);
			getline(infile,line); // Saves the line in "line".
        }
	Resourcemanager* resources = &resourcemanager;
	scenemanager.createSceneFromFile(argLevelfile, directX, resources);
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
