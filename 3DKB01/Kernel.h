#ifndef __Kernel_h__
#define __Kernel_h__

#include "Scenemanager.h"
#include "Windowmanager.h"
#include "RendererDirectX.h"
#include "Resourcemanager.h"
#include "Inputmanager.h"
#include "SceneHeightmap.h"
#include <map>
#include <iostream>
#include <Windows.h>
#include "Logger.h"
#include <sstream>


class Kernel
{
private:
	std::map<LotsoWindow*, Scene*> windowSceneBind;
	RendererInterface* renderer;
	RendererInterface* renderer2;
	Windowmanager* windowmanager;
	Scenemanager* scenemanager;
	Resourcemanager* resourcemanager;
	Inputmanager* inputmanager;
public:
	Kernel(void);
	Kernel(bool);
	~Kernel(void);
	void initialize(std::string);
	void Kernel::createManagers(Windowmanager*, Resourcemanager*, Scenemanager*, Inputmanager*, RendererInterface*);
	Scenemanager* getScenemanager();
	Windowmanager* getWindowmanager();
	RendererInterface* getRenderer();
	RendererInterface* getRenderer2();
	Resourcemanager* getResourcemanager();
	Inputmanager* getInputmanager();

	void programLoop(std::string);
	void addWindowToScene();

	void cleanup();
	RendererInterface* getDirectX(void);
	void loadLevelFile(std::string);
};

#endif