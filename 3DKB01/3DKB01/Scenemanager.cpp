#include "Scenemanager.h"


Scenemanager::Scenemanager(void)
{
}
Scenemanager::~Scenemanager(void)
{
}

// Creates a scene
void Scenemanager::createScene()
{
	Scene* scene = new Scene();
	addScene(scene);
}

// Adds scene to list
void Scenemanager::addScene(Scene* argScene)
{
	scenes.push_back(argScene);
}