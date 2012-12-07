#include <iostream>
#include "Kernel.h"



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
}
