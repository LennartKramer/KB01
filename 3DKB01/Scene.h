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

class Scene
{
private:
	std::string name;
	std::list<EntityModel*> entityModelList;
	EntityCamera* entityCamera;
	RendererDirectX* directX;
public:

	Scene(std::string argName, RendererDirectX*);
	~Scene(void);

	std::string getName();

	void addEntityModel(D3DXVECTOR3, D3DXVECTOR3, ResourceModel*, ResourceTexture*); 
	void addEntityCamera(D3DXVECTOR3, D3DXVECTOR3, D3DXVECTOR3);


	void drawEntities(); // draw all the entities in the scene
	void setView(); // set the view matrices, depends on the position and orientation of the camera


};

#endif