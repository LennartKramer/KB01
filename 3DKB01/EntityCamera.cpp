#include "EntityCamera.h"


EntityCamera::EntityCamera(Vector argPosition, Vector argDirection, Vector argUp)
{
	position = argPosition;
	direction = argDirection;
	up = argUp;
}


Vector EntityCamera::getDirection()
{
	return direction;
}

Vector EntityCamera::getUp()
{
	return up;
}

EntityCamera::~EntityCamera(void)
{
}

Vector EntityCamera::getPosition()
{
	return position;
}