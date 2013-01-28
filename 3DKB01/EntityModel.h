#ifndef __E_MODEL__
#define __E_MODEL__

#include "Entity.h"

class EntityModel : Entity
{
public:
	EntityModel(Vector, Vector, ResourceModel*, ResourceTexture*);
	~EntityModel(void);
	void drawEntityModel(void); // draw itself using d3d
	ResourceModel* getModel(void);
	ResourceTexture* getTexture(void);
	Vector getOrientation(void);
	Vector getPosition(void);
	void setPosition(Vector argPosition);
private:
	Vector orientation; 	// the orientation of the entity
	ResourceModel* model;
	ResourceTexture* texture;
};

#endif

