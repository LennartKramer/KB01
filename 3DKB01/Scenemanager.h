#ifndef __SCENEMANAGER_H__
#define __SCENEMANAGER_H__

#include "Scene.h"
#include <list>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include "Resourcemanager.h"

class Scenemanager
{
private:
	std::list<Scene*> scenes;
public:
	Scenemanager(void);
	~Scenemanager(void);
	void createScene(std::string, RendererInterface*);
	void createSceneFromFile(std::string, RendererInterface*, Resourcemanager*);
	void addScene(Scene* argScene);
	Scene* getScene(std::string argSceneName);
	void drawScene(Scene *argScene,POINT mouse, bool isMouseRPressed, int keyboardInput);
};

#endif