#include "Scene.h"

Scene::Scene(std::string argName, RendererInterface* argRenderer)
{
	name = argName;
	renderer = argRenderer;
}

Scene::~Scene()
{
}

std::string Scene::getName()
{
	return name;
}

// Adds an entityModel to scene.
void Scene::addEntityModel(Vector argPosition , Vector argOrientation, ResourceModel* argModel, ResourceTexture* argTexture)
{
	EntityModel* entityModel = new EntityModel(argPosition, argOrientation, argModel, argTexture);
	entityModelList.push_back(entityModel);
}
// Adds a camera to the scene.
void Scene::addEntityCamera(RendererInterface* argRenderer)
{
	entityCamera = new EntityCamera(argRenderer);
}

// Sets the view orientation of the camera.
void Scene::setView(float argMouseX, float argMouseY, bool isMouseRPressed)
{
	entityCamera->moveCamera(argMouseX, argMouseY,isMouseRPressed);
}

// Adds a skybox to the scene
void Scene::addSkybox(ResourceTexture* argTexture)
{
	skybox = new SceneSkybox(renderer, argTexture);
}

// Adds a terrain to the scene. Heightmap contains the data for the height. The texture will be drawn on the heightmap.
void Scene::addTerrain(std::string argHeightmap, ResourceTexture* argTexture)
{
	terrain = new SceneHeightmap(renderer, argHeightmap, argTexture);
}

// Renders a scene.
// Draws it on the screen
void Scene::renderScene(Vector changedPosition, HWND hWnd)
{
	renderer->clear(); // clear the backbuffer
	renderer->beginScene(); // must be called before rendering
	

	moveScene(changedPosition);



	skybox->render();
	terrain->render();
	drawEntities();

	renderer->endScene(); // must be called after rendering
	renderer->present(hWnd); // present the scene to the screen
}


// Draws all entities on the screen.
void Scene::drawEntities()
{
	Vector oldPosition;

	std::list<EntityModel*>::iterator Iterator;
		for(Iterator = entityModelList.begin(); Iterator != entityModelList.end(); ++Iterator) // iterate trough all entities
		{		

			// get the model and the texture from the entity (the iterator)
			renderer->moveMatrix((*Iterator)->getOrientation(), (*Iterator)->getPosition());


			LPD3DXMESH mesh = (*Iterator)->getModel()->getMesh() ; 
			
			renderer->setTexture((*Iterator)->getTexture());
			mesh->DrawSubset(0);
		}
}

EntityCamera* Scene::getEntityCamera()
{
	return entityCamera;
}

void Scene::moveScene(Vector changedPosition)
{
	Vector oldPosition;
	

	//Move Entities
	std::list<EntityModel*>::iterator Iterator;
	for(Iterator = entityModelList.begin(); Iterator != entityModelList.end(); ++Iterator)
	{		
		oldPosition = (*Iterator)->getPosition();
		float currentX = oldPosition.getX();
		float currentY = oldPosition.getY();
		float currentZ = oldPosition.getZ();

		float newPositionX = changedPosition.getX() + currentX;
		float newPositionY = changedPosition.getY() + currentY;
		float newPositionZ = changedPosition.getZ() + currentZ;

		Vector newPosition = Vector(newPositionX, newPositionY, newPositionZ);
		(*Iterator)->setPosition(newPosition);
	}

	//Move Terrain
	oldPosition = terrain->getPosition();
	float currentX = oldPosition.getX();
	float currentY = oldPosition.getY();
	float currentZ = oldPosition.getZ();
	
	float newPositionX = changedPosition.getX() + currentX;
	float newPositionY = changedPosition.getY() + currentY;
	float newPositionZ = changedPosition.getZ() + currentZ;

	Vector newPosition = Vector(newPositionX, newPositionY, newPositionZ);

	terrain->setPosition(newPosition);

}

EntityCamera* Scene::getCamera() 
{ 
	return entityCamera; 
} 