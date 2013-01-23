#include "Scene.h"
#include "EntityModel.h"

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
void Scene::addEntityCamera()
{
	entityCamera = new EntityCamera();
}

// Sets the view orientation of the camera.
void Scene::setView(POINT mouse, bool isMouseRPressed)
{
	entityCamera->Move(mouse,isMouseRPressed);
	renderer->setupCamera(entityCamera->GetEyePt(), entityCamera->GetLookAtPt());
}


void Scene::addSkybox(ResourceTexture* argTexture)
{
	skybox = new SceneSkybox(renderer, argTexture);
}

void Scene::addTerrain(std::string argHeightmap, ResourceTexture* argTexture)
{
	terrain = new SceneHeightmap(renderer, argHeightmap, argTexture);
}

// Renders a scene.
// Draws it on the screen
void Scene::renderScene(float argTerSide,float argTerFront,float argTerUp)
{
	// Clear the backbuffer to a purple color
	renderer->clear();
	renderer->beginScene();
	
	skybox->Render();

	terrain->render(argTerSide, argTerFront, argTerUp);
	drawEntities(argTerSide, argTerFront, argTerUp);
	

	renderer->endScene();
	renderer->present();
}


// Draws all entities on the screen.

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
			float newPositionY = argTerUp + currentY;
			float newPositionZ = argTerFront + currentZ;

			Vector newPosition = Vector(newPositionX, newPositionY, newPositionZ);
			(*Iterator)->setPosition(newPosition);
			
			// get the model and the texture from the entity (the iterator)
			renderer->setupWorldMatrix((*Iterator)->getPosition(), (*Iterator)->getOrientation());

			LPD3DXMESH mesh = (*Iterator)->getModel()->getMesh() ;
			
			renderer->setTexture((*Iterator)->getTexture());
			mesh->DrawSubset(0);
		}
}
EntityCamera* Scene::getEntityCamera()
	{
		return entityCamera;
	}
