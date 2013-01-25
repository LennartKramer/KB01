/*
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
	Kernel kernel = Kernel(true);

	Logger::message("----start initializing----");
	HRESULT result;
	//create and show first window
	kernel.getWindowmanager()->createWindow(messageHandler, TEXT("window1"), 100, 100, 600, 600, TEXT("window1"));
	kernel.getWindowmanager()->getWindow("window1")->show();

	result = kernel.getRenderer()->initD3D(kernel.getWindowmanager()->getWindow("window1")->getHandle());
	Logger::message(result, "initialize direct3d...");

	kernel.getResourcemanager()->setDevice(kernel.getRenderer()->getDevice());

	kernel.getInputmanager()->CreateKeyboard(kernel.getWindowmanager()->getWindow("window1")->getHandle());
	kernel.getInputmanager()->CreateMouse(kernel.getWindowmanager()->getWindow("window1")->getHandle());

	Logger::message("----start creating scene----");
	kernel.loadLevelFile("level1.llf");

	Logger::message("----start the programLoop----");
	kernel.programLoop();

	Logger::message("----start cleaning up----");
	kernel.cleanup();

	return 0;
	
}





*/