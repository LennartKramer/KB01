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
	EntityCamera entityCamera;
	RendererDirectX directX;
public:
	Scene(void);
	~Scene(void);

	void setDirectX(RendererDirectX argDirectX) { directX = argDirectX; }

	std::string getName();

	void addEntityModel(D3DXVECTOR3 position , D3DXVECTOR3 orientation, ResourceModel model, ResourceTexture texture); 
	void addEntityCamera(D3DXVECTOR3 position, D3DXVECTOR3 direction, D3DXVECTOR3 up);


	void drawEntities(); // draw all the entities in the scene
	void setView(); // set the view matrices, depends on the position and orientation of the camera


};

#endif