#include "Windowmanager.h"
#include "RendererDirectX.h"
#include "LotsoWindow.h"
#include <Windows.h>
#include "Kernel.h"

//*** Fields ***


void cleanup();
void quitWithError(LPCTSTR error);
void programLoop();

int main() {
	Kernel kernel;
	kernel.initialize();
	kernel.createSingleScene();
	kernel.programLoop();
	kernel.cleanup();
	return 0;
}