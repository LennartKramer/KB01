#ifndef __E_MODEL__
#define __E_MODEL__

#include "Entity.h"

class EntityModel : Entity
{
public:
	EntityModel(D3DXVECTOR3, D3DXVECTOR3, ResourceModel*, ResourceTexture*);
	~EntityModel();
	void drawEntityModel(); // draw itself using d3d
	ResourceModel* getModel() { return model; }
	ResourceTexture* getTexture() { return texture; }
	D3DXVECTOR3 getOrientation() { return orientation; }
	D3DXVECTOR3 getPosition() { return position; }
private:
	D3DXVECTOR3 orientation; 	// the orientation of the entity
	ResourceModel* model;
	ResourceTexture* texture;
};

#endif

