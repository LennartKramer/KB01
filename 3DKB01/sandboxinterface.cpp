#include "Windowmanager.h"
#include "RendererDirectX.h"
#include "LotsoWindow.h"
#include <Windows.h>
#include "Kernel.h"
#include "Logger.h"
#include <sstream>
#include <iostream>
#include <string>
#include <vector>

//*** Fields ***


void cleanup();
void quitWithError(LPCTSTR error);

LRESULT CALLBACK messageHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

int main() {
	
	Logger::clearLog();
	Logger::message("----program started----");

	// create all managers
	Kernel kernel = Kernel(true);
	Windowmanager* windowmanager = new Windowmanager();
	Resourcemanager* resourcemanager = new Resourcemanager();
	Scenemanager* scenemanager = new Scenemanager(resourcemanager);
	Inputmanager* inputmanager = new Inputmanager();
	RendererInterface* renderer = new RendererDirectX();
	kernel.createManagers(windowmanager, resourcemanager, scenemanager, inputmanager, renderer);

	Logger::message("----start initializing----");
	HRESULT result;

	//create and show window
	kernel.getWindowmanager()->createWindow(messageHandler, TEXT("window1"), 100, 100, 600, 600, TEXT("window1"));
	kernel.getWindowmanager()->getWindow("window1")->show();

	result = kernel.getRenderer()->initD3D(kernel.getWindowmanager()->getWindow("window1")->getHandle());
	Logger::message(result, "initialize direct3d...");

	kernel.getResourcemanager()->setDevice(kernel.getRenderer()->getDevice());

	//Create keyboard and mouse
	kernel.getInputmanager()->CreateKeyboard(kernel.getWindowmanager()->getWindow("window1")->getHandle());
	kernel.getInputmanager()->CreateMouse(kernel.getWindowmanager()->getWindow("window1")->getHandle());

	//create scene and load resources through levelFile
	Logger::message("----start creating scene----");
	kernel.loadLevelFile("level1.llf");

	//Load resources
	kernel.getResourcemanager()->loadTexture("textures/skybox.png");
	kernel.getResourcemanager()->loadMesh("meshes/tiger.x");

	Vector modelPosition = Vector(0.0, 0.0, 1.0);
	Vector modelOrientation = Vector(0.0, 0.0, 0.0);

	ResourceModel* resourcemodel = kernel.getResourcemanager()->getResourceModel("meshes/tiger.x");
	ResourceTexture* resourcetexture  = kernel.getResourcemanager()->getResourceTexture("tiger.bmp");

	//Add entity to to scene
	kernel.getScenemanager()->getScene("level1.llf")->addEntityModel(modelPosition , modelOrientation, resourcemodel, resourcetexture);

	resourcetexture  = resourcemanager->getResourceTexture("textures/skybox.png");
	scenemanager->getScene("level1.llf")->addSkybox(resourcetexture);

	//Run the programLoop
	Logger::message("----start the programLoop----");
	kernel.programLoop();

	//Removes all windows
	Logger::message("----start cleaning up----");
	kernel.cleanup();

	return 0;
	
}





