#ifndef __SCENE_H__
#define __SCENE_H__

#include "LotsoWindow.h"
#include "RendererInterface.h"

#include <list>
#include <iostream>
#include "RendererDirectX.h"
#include "Entity.h"
#include "EntityModel.h"
#include "EntityCamera.h"
#include "SceneSKybox.h"

class Scene
{
private:
	std::string name;
	std::list<EntityModel*> entityModelList;
	EntityCamera* entityCamera;
	RendererInterface* directX;
	SceneSkybox* skybox;
public:

	Scene(std::string argName, RendererInterface*);
	~Scene(void);

	std::string getName();

	void addEntityModel(Vector, Vector, ResourceModel*, ResourceTexture*); 
	void addEntityCamera(Vector, Vector, Vector);

	void createSkybox();
	void renderScene(float, float, int, int);
	void drawEntities(); // draw all the entities in the scene
	void setView(); // set the view matrices, depends on the position and orientation of the camera


};

#endif