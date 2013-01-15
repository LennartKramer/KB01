#include "Entity.h"


Entity::Entity(void)
{
}


Entity::~Entity(void)
{
}

void Entity::setPosition(Vector argPosition)
{
	position = argPosition;
}

Vector Entity::getPosition()
{
	return position;
}