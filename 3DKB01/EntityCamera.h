#ifndef __ENTITYCAMERA_H__
#define __ENTITYCAMERA_H__

#include "Entity.h"

class EntityCamera : Entity
{
public:
	EntityCamera(Vector, Vector, Vector);
	~EntityCamera(void);
	Vector getDirection(); 
	Vector getUp();
	Vector getPosition();
	void changePosition(int);
private:
	Vector direction;	// the direction the camera is looking at
	Vector up;   // wich direction is up?
	Vector position;
};

#endif