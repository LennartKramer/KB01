#include <iostream>
#include "Kernel.h"


RendererDirectX* directX;
Scenemanager* scenemanager;
Windowmanager windowmanager;

Kernel::Kernel(void)
{
	directX = RendererDirectX();
	scenemanager = Scenemanager(&directX);
}


Kernel::~Kernel(void)
{
}
