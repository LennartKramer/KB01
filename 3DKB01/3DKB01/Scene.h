#ifndef __SCENE_H__
#define __SCENE_H__

#include "eWindow.h"
#include "RendererInterface.h"
#include <list>
#include <iostream>

class Scene
{
private:
RendererInterface* sceneRenderer;

public:
	Scene(void);
	~Scene(void);
	void addRenderer(RendererInterface* argRendererInterface);
};

#endif