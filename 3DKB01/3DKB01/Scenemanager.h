#ifndef __SCENEMANAGER_H__
#define __SCENEMANAGER_H__

#include "Scene.h"

class Scenemanager
{
private:
	Scene scene;

public:
	Scenemanager(void);
	~Scenemanager(void);
	void addWindow();
};

#endif