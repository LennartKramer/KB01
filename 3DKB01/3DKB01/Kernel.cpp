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

void Kernel::bindWindowScene(eWindow* argWindow, Scene* argScene)
{
	windowSceneBind[argWindow] = argScene;
	//windowSceneBind.insert(std::pair<eWindow*, Scene*>(argWindow, argScene));
}