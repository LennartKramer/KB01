#include "Scene.h"
#include "EntityModel.h"

Scene::Scene(std::string argName)
{
	name = argName;
}
Scene::~Scene()
{
}

std::string Scene::getName()
{
	return name;
}

void Scene::drawEntities()
{

	std::list<EntityModel*>::iterator Iterator;
		for(Iterator = entityModelList.begin(); Iterator != entityModelList.end(); ++Iterator)
		{
			// get the model and the texture from the entity (the iterator)

			directX.renderEntityModel(); // put the model and texture into the renderer using the renderEntityModel method
		}
}