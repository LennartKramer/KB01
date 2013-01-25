#include "EntityCamera.h"
#include <iostream>


EntityCamera::EntityCamera()
{

	// Set attributes for the view matrix
	D3DXVECTOR3 vEyePt = D3DXVECTOR3( 5.0f, 5.0f, 5.0f );
    D3DXVECTOR3 vLookatPt = D3DXVECTOR3(  0.0f, 0.0f, 0.0f );

	// Setup the view matrix
    SetViewParams( &vEyePt, &vLookatPt );

	 // Setup the projection matrix
    SetProjParams( D3DX_PI / 4, 1.0f, 1.0f, 1000.0f );

    m_fCameraYawAngle = 0.0f;
    m_fCameraPitchAngle = 0.0f;

    m_vVelocity = D3DXVECTOR3( 0, 0, 0 );
    m_vRotVelocity = D3DXVECTOR2( 0, 0 );
    m_fRotationScaler = 0.01f;
 
    m_bEnableYAxisMovement = true;
    m_bEnablePositionMovement = true;

    m_vMouseDelta = D3DXVECTOR2( 0, 0 );
	m_fFramesToSmoothMouseData = 2.0f;
    m_bClipToBoundary = false;
    m_vMinBoundary = D3DXVECTOR3( -1, -1, -1 );
    m_vMaxBoundary = D3DXVECTOR3( 1, 1, 1 );	
}


EntityCamera::~EntityCamera(void)
{
}


//--------------------------------------------------------------------------------------
// Client can call this to change the position and direction of camera
//--------------------------------------------------------------------------------------

VOID EntityCamera::SetViewParams( D3DXVECTOR3* pvEyePt, D3DXVECTOR3* pvLookatPt )
{
    if( NULL == pvEyePt || NULL == pvLookatPt )
        return;

    m_vDefaultEye = m_vEye = *pvEyePt;
    m_vDefaultLookAt = m_vLookAt = *pvLookatPt;

    // Calc the view matrix
    D3DXVECTOR3 vUp( 0,1,0 );
    D3DXMatrixLookAtLH( &m_mView, pvEyePt, pvLookatPt, &vUp );

    D3DXMATRIX mInvView;
    D3DXMatrixInverse( &mInvView, NULL, &m_mView );

    // The axis basis vectors and camera position are stored inside the 
    // position matrix in the 4 rows of the camera's world matrix.
    // To figure out the yaw/pitch of the camera, we just need the Z basis vector
    D3DXVECTOR3* pZBasis = ( D3DXVECTOR3* )&mInvView._31;

    m_fCameraYawAngle = atan2f( pZBasis->x, pZBasis->z );
    float fLen = sqrtf( pZBasis->z * pZBasis->z + pZBasis->x * pZBasis->x );
    m_fCameraPitchAngle = -atan2f( pZBasis->y, fLen );
}


//--------------------------------------------------------------------------------------
// Calculates the projection matrix based on input params
//--------------------------------------------------------------------------------------
VOID EntityCamera::SetProjParams( FLOAT fFOV, FLOAT fAspect, FLOAT fNearPlane,
                                 FLOAT fFarPlane )
{
    // Set attributes for the projection matrix
    m_fFOV = fFOV;
    m_fAspect = fAspect;
    m_fNearPlane = fNearPlane;
    m_fFarPlane = fFarPlane;

    D3DXMatrixPerspectiveFovLH( &m_mProj, fFOV, fAspect, fNearPlane, fFarPlane );
}

/*
void EntityCamera::rotate(float argRelativeX, float argRelativeY)
{
	D3DXVECTOR3 vDirection,vRotAxis;
D3DXMATRIX matRotAxis,matRotZ;


D3DXVec3Normalize(&vDirection,
                  &(direction - position)); //create direction vector

D3DXVec3Cross(&vRotAxis,&vDirection,&up); //strafe vector
D3DXVec3Normalize(&vRotAxis,&vRotAxis);

//create rotation matrices
D3DXMatrixRotationAxis(&matRotAxis,
                       &vRotAxis,
                       argRelativeY / -360);

D3DXMatrixRotationZ(&matRotZ, argRelativeX / -360);

//rotate direction
D3DXVec3TransformCoord(&vDirection,&vDirection,&(matRotAxis * matRotZ));
//rotate up vector
D3DXVec3TransformCoord(&up,&up,&(matRotAxis * matRotZ));
//translate up vector
direction = vDirection + position;
} //Rotate

void EntityCamera::update(float argRelativeX, float argRelativeY)
{
	rotate(argRelativeX, argRelativeY);
//Move();

//create view matrix
//D3DXMatrixLookAtLH(&m_matView,&m_vEyePt,&m_vLookAtPt,&m_vUp);
//set view matrix
//g_App.GetDevice()->SetTransform(D3DTS_VIEW,&m_matView);
}
*/
//void EntityCamera::changePosition(int value)

//--------------------------------------------------------------------------------------
// Figure out the mouse delta based on mouse movement
//--------------------------------------------------------------------------------------

void EntityCamera::UpdateMouseDelta(POINT CurMousePos)
{	
    POINT ptCurMouseDelta;

    // Get current position of mouse
	ptCurMouseDelta = CurMousePos;

  
    // Smooth the relative mouse data over a few frames so it isn't 
    // jerky when moving slowly at low frame rates.
    float fPercentOfNew = 1.0f / m_fFramesToSmoothMouseData;
    float fPercentOfOld = 1.0f - fPercentOfNew;
    m_vMouseDelta.x = m_vMouseDelta.x * fPercentOfOld + ptCurMouseDelta.x * fPercentOfNew;
    m_vMouseDelta.y = m_vMouseDelta.y * fPercentOfOld + ptCurMouseDelta.y * fPercentOfNew;

    m_vRotVelocity = m_vMouseDelta * m_fRotationScaler;
}



//--------------------------------------------------------------------------------------
// Clamps pV to lie inside m_vMinBoundary & m_vMaxBoundary
//--------------------------------------------------------------------------------------


void EntityCamera::ConstrainToBoundary( D3DXVECTOR3* pV )
{
    // Constrain vector to a bounding box 
    pV->x = __max( pV->x, m_vMinBoundary.x );
    pV->y = __max( pV->y, m_vMinBoundary.y );
    pV->z = __max( pV->z, m_vMinBoundary.z );

    pV->x = __min( pV->x, m_vMaxBoundary.x );
    pV->y = __min( pV->y, m_vMaxBoundary.y );
    pV->z = __min( pV->z, m_vMaxBoundary.z );
}



VOID EntityCamera::Reset()
{
    SetViewParams( &m_vDefaultEye, &m_vDefaultLookAt );
}



//--------------------------------------------------------------------------------------
// Update the view matrix based on user input & elapsed time
//--------------------------------------------------------------------------------------
VOID EntityCamera::Move(POINT CurMousePos, bool MouseButtonPressed)
{
    //if( IsKeyDown( m_aKeys[CAM_RESET] ) )
    //    Reset();

	UpdateMouseDelta(CurMousePos);

    // Get amount of velocity based on the keyboard input and drag (if any)
    m_vRotVelocity = m_vMouseDelta * m_fRotationScaler ; 

    // Simple euler method to calculate position delta
	 D3DXVECTOR3 vPosDelta = D3DXVECTOR3(0,0,0) ;
	
    // If rotating the camera 
    if(MouseButtonPressed)
    {
        // Update the pitch & yaw angle based on mouse movement
        float fYawDelta = m_vRotVelocity.x;
        float fPitchDelta = m_vRotVelocity.y;
	
        m_fCameraPitchAngle += fPitchDelta;
        m_fCameraYawAngle += fYawDelta;
	
        // Limit pitch to straight up or straight down
        m_fCameraPitchAngle = __max( -D3DX_PI / 2.0f, m_fCameraPitchAngle );
        m_fCameraPitchAngle = __min( +D3DX_PI / 2.0f, m_fCameraPitchAngle );
    } 

    // Make a rotation matrix based on the camera's yaw & pitch
    D3DXMATRIX mCameraRot;
    D3DXMatrixRotationYawPitchRoll( &mCameraRot, m_fCameraYawAngle, m_fCameraPitchAngle, 0 );

    // Transform vectors based on camera's rotation matrix
    D3DXVECTOR3 vWorldUp, vWorldAhead;
    D3DXVECTOR3 vLocalUp = D3DXVECTOR3( 0, 1, 0 );
    D3DXVECTOR3 vLocalAhead = D3DXVECTOR3( 0, 0, 1 );
    D3DXVec3TransformCoord( &vWorldUp, &vLocalUp, &mCameraRot );
    D3DXVec3TransformCoord( &vWorldAhead, &vLocalAhead, &mCameraRot );

    if( m_bClipToBoundary )
        ConstrainToBoundary( &m_vEye );

    // Update the lookAt position based on the eye position 
    m_vLookAt = m_vEye + vWorldAhead;

    // Update the view matrix
    D3DXMatrixLookAtLH( &m_mView, &m_vEye, &m_vLookAt, &vWorldUp );
}



