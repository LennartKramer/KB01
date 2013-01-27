#ifndef __Kernel_h__
#define __Kernel_h__

#include "Scenemanager.h"
#include "Windowmanager.h"
#include "RendererDirectX.h"
#include "Resourcemanager.h"
#include "Inputmanager.h"
#include "SceneHeightmap.h"
//#include "Logger.h"
#include <map>
#include <iostream>
#include <Windows.h>
#include "Logger.h"


class Kernel
{
private:
	std::map<LotsoWindow*, Scene*> windowSceneBind;
	RendererInterface* renderer;
	Windowmanager* windowmanager;
	Scenemanager* scenemanager;
	Resourcemanager* resourcemanager;
	Inputmanager* inputmanager;
	//LRESULT CALLBACK messageHandler(HWND window, UINT msg, WPARAM wParam, LPARAM lParam);
public:
	Kernel(void);
	Kernel(bool);
	~Kernel(void);
	void initialize();
	void Kernel::createManagers(Windowmanager*, Resourcemanager*, Scenemanager*, Inputmanager*, RendererInterface*);
	Scenemanager* getScenemanager();
	Windowmanager* getWindowmanager();
	RendererInterface* getRenderer();
	Resourcemanager* getResourcemanager();
	Inputmanager* getInputmanager();
	void noobinterface();
	void programLoop();
	void addWindowToScene();
	void sandBoxInterface();
	//void addRendererToScene();
	void createSingleScene();
	//void bindWindowScene(LotsoWindow* argWindow, Scene* argScene);
	void cleanup();
	RendererInterface* getDirectX(void);
	void loadLevelFile(std::string);
};

#endif