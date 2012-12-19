#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "ResourceModel.h"
#include "ResourceTexture.h"

class Entity
{
public:
	Entity(void);
	~Entity(void);
private:
	float x, y, z;
};

#endif