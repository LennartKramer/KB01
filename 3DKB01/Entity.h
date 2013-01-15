#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "ResourceModel.h"
#include "ResourceTexture.h"
#include "RendererInterface.h"

class Entity
{
public:
	Entity(void);
	~Entity(void);
	Vector getPosition();
	void setPosition(Vector);
protected:
	Vector position; //position (translation) of the entity
};

#endif