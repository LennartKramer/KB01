#ifndef __ENTITYCAMERA_H__
#define __ENTITYCAMERA_H__

#include "Entity.h"

class EntityCamera : Entity
{
public:
	EntityCamera(D3DXVECTOR3, D3DXVECTOR3, D3DXVECTOR3);
	~EntityCamera(void);
	D3DXVECTOR3 getDirection(); 
	D3DXVECTOR3 getUp();
	D3DXVECTOR3 getPosition();
private:
	D3DXVECTOR3 direction;	// the direction the camera is looking at
	D3DXVECTOR3 up;   // wich direction is up?
};

#endif