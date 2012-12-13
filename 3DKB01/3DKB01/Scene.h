#ifndef __SCENE_H__
#define __SCENE_H__

#include "eWindow.h"
#include "RendererInterface.h"
#include <list>
#include <iostream>

class Scene
{
private:
	std::string name;
public:
	Scene(void);
	~Scene(void);
	std::string getName();
};

#endif