#ifndef __Kernel_h__
#define __Kernel_h__

#include "Scenemanager.h"
#include "Windowmanager.h"
#include "RendererDirectX.h"
#include "Resourcemanager.h"
#include "Inputmanager.h"
#include "ResourceInterface.h"
#include <map>
#include <iostream>
#include <Windows.h>

class Kernel
{
private:
	std::map<LotsoWindow*, Scene*> windowSceneBind;
	RendererDirectX* directX;
	Windowmanager windowmanager;
	Scenemanager scenemanager;
	Resourcemanager resourcemanager;
	Inputmanager inputmanager;
	//LRESULT CALLBACK messageHandler(HWND window, UINT msg, WPARAM wParam, LPARAM lParam);
    

public:
	Kernel(void);
	~Kernel(void);
	void initialize();
	void programLoop();
	void addWindowToScene();
	void addRendererToScene();
	void bindWindowScene(LotsoWindow* argWindow, Scene* argScene);
	void cleanup();
};

#endif