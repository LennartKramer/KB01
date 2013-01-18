#ifndef __SCENE_H__
#define __SCENE_H__

#include "LotsoWindow.h"
#include "RendererInterface.h"
#include <list>
#include <iostream>
#include "Entity.h"
#include "EntityModel.h"
#include "EntityCamera.h"
#include "SceneSkybox.h"
#include "SceneHeightmap.h"

class Scene
{
private:
	std::string					name;
	std::list<EntityModel*>		entityModelList;
	EntityCamera*				entityCamera;
	RendererInterface*			renderer;
	SceneSkybox*				skybox;
	SceneHeightmap*				terrain;
public:

	Scene(std::string argName, RendererInterface*);
	~Scene(void);

	std::string getName();

	void addTerrain(ResourceTexture*);
	void addSkybox(ResourceTexture*);
	void addEntityModel(Vector, Vector, ResourceModel*, ResourceTexture*); 
	void addEntityCamera(Vector, Vector, Vector);
	EntityCamera* getCamera() { return entityCamera; } // inlined


	void renderScene();
	void drawEntities(float, float, float); // draw all the entities in the scene
	void setView(); // set the view matrices, depends on the position and orientation of the camera


};

#endif