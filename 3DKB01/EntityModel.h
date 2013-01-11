#ifndef __E_MODEL__
#define __E_MODEL__

#include "Entity.h"

class EntityModel : Entity
{
public:
	EntityModel(Vector, Vector, ResourceModel*, ResourceTexture*);
	~EntityModel();
	void drawEntityModel(); // draw itself using d3d
	ResourceModel* getModel() { return model; }
	ResourceTexture* getTexture() { return texture; }
	Vector getOrientation() { return orientation; }
	Vector getPosition() { return position; }
private:
	Vector orientation; 	// the orientation of the entity
	ResourceModel* model;
	ResourceTexture* texture;
};

#endif

