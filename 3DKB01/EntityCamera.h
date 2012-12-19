#ifndef __ENTITYCAMERA_H__
#define __ENTITYCAMERA_H__

#include "Entity.h"

class EntityCamera : Entity
{
public:
	EntityCamera(void);
	~EntityCamera(void);
private:
	float dX, dY, dZ;	// the direction the camera is looking at
	float uX, uY, uZ;   // wich direction is up?
};

#endif