#ifndef __ENTITYCAMERA_H__
#define __ENTITYCAMERA_H__

#include "Entity.h"


class EntityCamera : Entity
{
public:
	EntityCamera(RendererInterface*);  //constructor
	~EntityCamera(void); //destructor
	void moveCamera(float, float,bool MouseButtonPressed);  // Fucntion to move Camera


private:
	RendererInterface*			renderer;
   
	void                        updateMouseDelta(float, float); // Function to updateMouseposition.
   
    Vector eyePt;                 // Camera eye position
    Vector lookatPt;              // LookAt position
    
	float mouseDeltaX;          // Mouse relative delta smoothed over a few frames
	float mouseDeltaY;
	float framesToSmoothMouseData; // Number of frames to smooth mouse data over

    float cameraYawAngle;      // Yaw angle of camera
    float cameraPitchAngle;    // Pitch angle of camera

    Vector velocity;            // Velocity of camera

	float rotVelocityX;				//rotation Velocity X
	float rotVelocityY;				//rotation Velocity Y
    float rotationScaler;      // Scaler for rotation

};

#endif