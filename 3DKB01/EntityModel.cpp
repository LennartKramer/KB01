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

void EntityModel::setPosition(Vector argPosition)
{
	position = argPosition;
}

void EntityModel::drawEntityModel()
{
	
}

ResourceModel* EntityModel::getModel() 
{ 
	return model; 
}

ResourceTexture* EntityModel::getTexture() 
{ 
	return texture; 
}

Vector EntityModel::getOrientation() 
{ 
	return orientation; 
}

Vector EntityModel::getPosition() 
{ 
	return position; 
}