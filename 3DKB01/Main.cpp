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
void programLoop();

int main() {
	Logger::clearLog();

	Logger::message("----program started----");
	Kernel kernel;
	Logger::message("----start initializing----");
	kernel.initialize();
	kernel.noobinterface();
	Logger::message("----start creating scene----");
	//kernel.createSingleScene();
	kernel.loadLevelFile("level1.llf");
	Logger::message("----start the programLoop----");
	kernel.programLoop();
	Logger::message("----start cleaning up----");
	kernel.cleanup();
	return 0;
}
*/