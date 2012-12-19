#include "Entity.h"

class EntityCamera : Entity
{
public:
	EntityCamera(void);
	~EntityCamera(void);
private:
	float dX, dY, dZ;	// the direction the camera is looking at
	float uX, uY, dZ;   // wich direction is up?
};

