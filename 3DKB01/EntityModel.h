#ifndef __E_MODEL__
#define __E_MODEL__

#include "Entity.h"

class EntityModel : Entity
{
public:
	EntityModel(void);
	~EntityModel(void);
	void drawEntityModel(); // draw itself using d3d
	ResourceModel getModel() { return model }
	ResourceTexture getTexture() { return texture }
private:
	float oX, oY, oZ; 	// the orientation of the entity
	ResourceModel model;
	ResourceTexture texture;
};

#endif

