#include "EntityCamera.h"


EntityCamera::EntityCamera(D3DXVECTOR3 argPosition, D3DXVECTOR3 argDirection, D3DXVECTOR3 argUp)
{
	position = argPosition;
	direction = argDirection;
	up = argUp;
}


D3DXVECTOR3 EntityCamera::getDirection()
{
	return direction;
}

D3DXVECTOR3 EntityCamera::getUp()
{
	return up;
}

EntityCamera::~EntityCamera(void)
{
}

D3DXVECTOR3 EntityCamera::getPosition()
{
	return position;
}