#ifndef __Kernel_h__
#define __Kernel_h__

#include "Scenemanager.h"
#include "Windowmanager.h"
#include "RendererDirectX.h"
#include "Resourcemanager.h"
#include "Inputmanager.h"
#include <map>
#include <iostream>

class Kernel
{
private:
	std::map<eWindow*, Scene*> windowSceneBind;
	RendererDirectX* directX;
	Windowmanager windowmanager;
	Scenemanager scenemanager;
	Resourcemanager resourcemanager;
	Inputmanager inputmanager;

public:
	Kernel(void);
	~Kernel(void);
	void addWindowToScene();
	void addRendererToScene();
	void bindWindowScene(eWindow* argWindow, Scene* argScene);
};

#endif