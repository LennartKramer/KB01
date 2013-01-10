#include "Scene.h"
#include "EntityModel.h"

Scene::Scene(std::string argName, RendererDirectX* argDirectX)
{
	name = argName;
	directX = argDirectX;
	createSkybox();
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

void Scene::createSkybox()
{
	skybox = new SceneSkybox(directX);
}

void Scene::renderScene()
{
    // Clear the backbuffer to a purple color
	directX->getDevice()->Clear( 0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, D3DCOLOR_XRGB( 122, 50, 202 ), 1.0f, 0 );
	directX->getDevice()->BeginScene();

	
	drawEntities();
	skybox->Render();
	
	directX->getDevice()->EndScene();
	directX->getDevice()->Present(NULL, NULL, NULL, NULL);
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