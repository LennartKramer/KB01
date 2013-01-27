#include "EntityCamera.h"
#include <iostream>



EntityCamera::EntityCamera(RendererInterface* argRenderer)
{
	renderer = argRenderer;

	// Set attributes for the view matrix
	eyePt = Vector( 5.0f, 5.0f, 5.0f );
    lookatPt = Vector(0.0f, 0.0f, 0.0f );

	// Setup the view matrix
	renderer->setupViewMatrix(eyePt,lookatPt);
	// Setup the projection matrix
	renderer->setupProjectionMatrix(D3DX_PI / 4, 1.0f, 1.0f, 1000.0f );

	//Set attributes for the angles of Camera
    cameraYawAngle = 0.0f;
    cameraPitchAngle = 0.0f;
	
	//Set attributes for calculating Mouse movement
    velocity = Vector( 0, 0, 0 );
	rotVelocityX = 0;
	rotVelocityY = 0;
    rotationScaler = 0.01f;
	mouseDelta.x = 0;
	mouseDelta.y = 0;
	framesToSmoothMouseData = 2.0f;
}


EntityCamera::~EntityCamera(void)
{

}



//--------------------------------------------------------------------------------------
// Figure out the mouse delta based on mouse movement
//--------------------------------------------------------------------------------------

void EntityCamera::updateMouseDelta(POINT mousePos)
{	
  
    // Smooth the relative mouse data over a few frames so it isn't 
    // jerky when moving slowly at low frame rates.
    float fPercentOfNew = 1.0f / framesToSmoothMouseData;
    float fPercentOfOld = 1.0f - fPercentOfNew;
    mouseDelta.x = mouseDelta.x * fPercentOfOld + mousePos.x * fPercentOfNew;
    mouseDelta.y = mouseDelta.y * fPercentOfOld + mousePos.y * fPercentOfNew;

	rotVelocityX = mouseDelta.x * rotationScaler;
	rotVelocityY = mouseDelta.y * rotationScaler;
}




//--------------------------------------------------------------------------------------
// Update the view matrix based on user input & elapsed time
//--------------------------------------------------------------------------------------
VOID EntityCamera::moveCamera(POINT curMousePos, bool mouseButtonPressed)
{

	updateMouseDelta(curMousePos);

    // If mouse button is pressed rotating the camera 
    if(mouseButtonPressed)
    {
        // Update the pitch & yaw angle based on mouse movement
        float yawDelta = rotVelocityX;
        float pitchDelta = rotVelocityY;
	
        cameraPitchAngle += pitchDelta;
        cameraYawAngle += yawDelta;
	
        // Limit pitch to straight up or straight down
       // cameraPitchAngle = __max( -D3DX_PI / 2.0f, m_fCameraPitchAngle );
       // cameraPitchAngle = __min( +D3DX_PI / 2.0f, m_fCameraPitchAngle );
    } 
	renderer->updateCamera(&eyePt,&lookatPt,cameraYawAngle,cameraPitchAngle);
   
}



