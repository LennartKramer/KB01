#include "EntityModel.h"


EntityModel::EntityModel(D3DXVECTOR3 argPosition , D3DXVECTOR3 argOrientation, ResourceModel* argModel, ResourceTexture* argTexture)
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
