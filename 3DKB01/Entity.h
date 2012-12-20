#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "ResourceModel.h"
#include "ResourceTexture.h"

class Entity
{
public:
	Entity(void);
	~Entity(void);
	D3DXVECTOR3 getPosition();
protected:
	D3DXVECTOR3 position; //position (translation) of the entity
};

#endif