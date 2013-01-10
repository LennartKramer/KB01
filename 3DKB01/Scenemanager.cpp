#include "Scenemanager.h"
#include <string>

Scenemanager::Scenemanager(void)
{
}
Scenemanager::~Scenemanager(void)
{
}

// Creates a scene
void Scenemanager::createScene(std::string argName, RendererDirectX* argDirectX)
{
	Scene* scene = new Scene(argName, argDirectX);
	addScene(scene);
}

// Adds scene to list
void Scenemanager::addScene(Scene* argScene)
{
	scenes.push_back(argScene);
}

// Get scene from list
Scene* Scenemanager::getScene(std::string argSceneName)
{
	std::list<Scene*>::iterator Iterator;
	for(Iterator = scenes.begin(); Iterator != scenes.end(); ++Iterator)
	{
		if((*Iterator)->getName() == argSceneName)
		{
			return (*Iterator);
		}
	}
}

void Scenemanager::drawScene(Scene *argScene)
{
	argScene->setView(); // set the view   ...(camera)
	argScene->renderScene();
}


