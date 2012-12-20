#include "Scene.h"
#include "EntityModel.h"

Scene::Scene(std::string argName, RendererDirectX* argDirectX)
{
	name = argName;
	directX = argDirectX;
}

Scene::~Scene()
{
}

std::string Scene::getName()
{
	return name;
}

void Scene::addEntityModel(D3DXVECTOR3 argPosition , D3DXVECTOR3 argOrientation, ResourceModel* argModel, ResourceTexture* argTexture)
{
	EntityModel* entityModel = new EntityModel(argPosition, argOrientation, argModel, argTexture);
	entityModelList.push_back(entityModel);
}

void Scene::addEntityCamera(D3DXVECTOR3 argPosition, D3DXVECTOR3 argDirection, D3DXVECTOR3 argUp)
{
	entityCamera = new EntityCamera(argPosition, argDirection, argUp);
}

void Scene::setView()
{
	directX->setupMatrices(entityCamera->getPosition(), entityCamera->getDirection(), entityCamera->getUp());
}

void Scene::drawEntities()
{

	std::list<EntityModel*>::iterator Iterator;
		for(Iterator = entityModelList.begin(); Iterator != entityModelList.end(); ++Iterator)
		{

			// get the model and the texture from the entity (the iterator)
			directX->setupWorldMatrix((*Iterator)->getPosition(), (*Iterator)->getOrientation());
			directX->render((*Iterator)->getTexture()->getMeshTextures(), (*Iterator)->getModel()->getMesh(), 0, 0); // put the model and texture into the renderer using the renderEntityModel method

		}
}