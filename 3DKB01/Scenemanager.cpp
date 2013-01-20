#include "Scenemanager.h"
#include <string>

Scenemanager::Scenemanager(void)
{
}
Scenemanager::~Scenemanager(void)
{
}

// Creates a scene
void Scenemanager::createScene(std::string argName, RendererInterface* argDirectX)
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
	return NULL;
}

void Scenemanager::drawScene(Scene *argScene, POINT mouse, bool isMouseRPressed,float argTerSide,float argTerFront,float argTerUp)
{
	//argScene->drawEntities(argTerSide,argTerFront,argTerUp);
	argScene->setView(mouse,isMouseRPressed); // set the view   ...(camera)
	argScene->renderScene(argTerSide,argTerFront,argTerUp);
}


