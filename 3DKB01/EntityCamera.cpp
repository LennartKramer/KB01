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

void EntityCamera::changePosition(int value)
{
	double x, y, z;
	x = position.getX();
	y = position.getY();
	z = position.getZ();
	Vector cameraPosition;
	if(value == 3) { cameraPosition = Vector(x, y, z + 0.01); }
	else if(value == 5) { cameraPosition = Vector(x - 0.01, y, z); }
	else if(value == 4) { cameraPosition = Vector(x, y, z - 0.01); }
	else if(value == 6) { cameraPosition = Vector(x + 0.01, y, z); }
	position = cameraPosition;
}