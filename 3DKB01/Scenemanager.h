#ifndef __SCENEMANAGER_H__
#define __SCENEMANAGER_H__

#include "Scene.h"
#include <list>
#include <iostream>

class Scenemanager
{
private:
	std::list<Scene*> scenes;
public:
	Scenemanager(void);
	~Scenemanager(void);
	void createScene(std::string, RendererInterface*);
	void addScene(Scene* argScene);
	Scene* getScene(std::string argSceneName);
	void drawScene(Scene *argScene,float,float, int , int);
};

#endif