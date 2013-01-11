#include "EntityModel.h"


EntityModel::EntityModel(Vector argPosition , Vector argOrientation, ResourceModel* argModel, ResourceTexture* argTexture)
{
	position = argPosition;
	orientation = argOrientation;
	model = argModel;
	texture = argTexture;
}


EntityModel::~EntityModel(void)
{
}

void EntityModel::drawEntityModel()
{
	
}
