#ifndef __SCENE_H__
#define __SCENE_H__

#include "eWindow.h"
#include <hash_map>

class Scene// : public SceneInterface
{
private:
	eWindow* window;
public:
	Scene(void);
	~Scene(void);
	void testMethode();
};

#endif