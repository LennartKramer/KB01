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

	void addTerrain(std::string, ResourceTexture*);
	void addSkybox(ResourceTexture*);
	void addEntityModel(Vector, Vector, ResourceModel*, ResourceTexture*); 
	void addEntityCamera();
	EntityCamera* getCamera() { return entityCamera; } // inlined

	void moveScene(int argKeyboardInput);
	void renderScene(int argKeyboardInput);
	void drawEntities(); // draw all the entities in the scene
	void setView(POINT mouse, bool isMouseRPressed); // set the view matrices, depends on the position and orientation of the camera
	EntityCamera* getEntityCamera();
};

#endif