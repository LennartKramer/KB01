#ifndef __VECTOR_H__
#define __VECTOR_H__

class Vector
{
public:
	Vector(void){}
	Vector(float argX, float argY, float argZ){x = argX, y = argY, z = argZ;}
	float getX(){return x;}
	float getY(){return y;}
	float getZ(){return z;}
private:
	float x,y,z;
};

#endif