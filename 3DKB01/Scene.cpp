#include "Scene.h"
#include "EntityModel.h"

Scene::Scene(std::string argName, RendererInterface* argDirectX)
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

void Scene::addEntityModel(Vector argPosition , Vector argOrientation, ResourceModel* argModel, ResourceTexture* argTexture)
{
	EntityModel* entityModel = new EntityModel(argPosition, argOrientation, argModel, argTexture);
	entityModelList.push_back(entityModel);
}

void Scene::addEntityCamera(Vector argPosition, Vector argDirection, Vector argUp)
{
	entityCamera = new EntityCamera(argPosition, argDirection, argUp);
}

void Scene::setView()
{
	directX->setupCamera(entityCamera->getPosition(), entityCamera->getDirection(), entityCamera->getUp());
}

void Scene::createSkybox()
{
	skybox = new SceneSkybox(directX);
}

void Scene::renderScene(float argTerSide, float argTerFront, float argTerUp,  int argWidth, int argHeight)
{
	// Clear the backbuffer to a purple color
	directX->clear();
	directX->beginScene();
	
	directX->setStreamSource();
	directX->setFvf();
	directX->setIndices();

	
	directX->drawPrimitive(argTerSide, argTerFront, argTerUp, argWidth, argHeight);

	drawEntities(argTerSide, argTerFront, argTerUp);

//	skybox->Render();
	
	

	directX->endScene();
	directX->present();
}

void Scene::drawEntities(float argTerSide,float argTerFront,float argTerUp)
{
	Vector oldPosition;

	std::list<EntityModel*>::iterator Iterator;
		for(Iterator = entityModelList.begin(); Iterator != entityModelList.end(); ++Iterator)
		{
			oldPosition = (*Iterator)->getPosition();
			float currentX = oldPosition.getX();
			float currentY = oldPosition.getY();
			float currentZ = oldPosition.getZ();

			float newPositionX = argTerSide + currentX;
			float newPositionY = argTerFront + currentY;
			float newPositionZ = -argTerUp + currentZ;

			Vector newPosition = Vector(newPositionX, newPositionY, newPositionZ);
			(*Iterator)->setPosition(newPosition);
			
			// get the model and the texture from the entity (the iterator)
			directX->setupWorldMatrix((*Iterator)->getPosition(), (*Iterator)->getOrientation());
			//directX->render(
			LPD3DXMESH mesh = (*Iterator)->getModel()->getMesh() ;
			
			directX->setTexture((*Iterator)->getTexture());
			mesh->DrawSubset(0);

		}
}