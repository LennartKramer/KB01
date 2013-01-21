#include "EntityCamera.h"
#include <iostream>


EntityCamera::EntityCamera()
{
	// Set attributes for the view matrix
    //D3DXVECTOR3 vEyePt = D3DXVECTOR3( -1.0f, -2.0f,-5.0f );
    //D3DXVECTOR3 vLookatPt = D3DXVECTOR3( 1.0f, 1.0f, 1.0f );

	D3DXVECTOR3 vEyePt = D3DXVECTOR3( 0.5f, 0.5f, 0.5f );
    D3DXVECTOR3 vLookatPt = D3DXVECTOR3(  -0.5f, 0.5f, 0.5f );

	// Setup the view matrix
    SetViewParams( &vEyePt, &vLookatPt );

	 // Setup the projection matrix
    SetProjParams( D3DX_PI / 4, 1.0f, 1.0f, 1000.0f );

    m_fCameraYawAngle = 0.0f;
    m_fCameraPitchAngle = 0.0f;

    SetRect( &m_rcDrag, LONG_MIN, LONG_MIN, LONG_MAX, LONG_MAX );
    m_vVelocity = D3DXVECTOR3( 0, 0, 0 );
    //m_bMovementDrag = false;
    m_vVelocityDrag = D3DXVECTOR3( 0, 0, 0 );
    m_fDragTimer = 0.0f;
    m_fTotalDragTimeToZero = 0.25;
    m_vRotVelocity = D3DXVECTOR2( 0, 0 );

    m_fRotationScaler = 0.01f;
    m_fMoveScaler = 5.0f;

    m_bInvertPitch = false;
    m_bEnableYAxisMovement = true;
    m_bEnablePositionMovement = true;

    m_vMouseDelta = D3DXVECTOR2( 0, 0 );
	m_fFramesToSmoothMouseData = 2.0f;
    m_bClipToBoundary = false;
    m_vMinBoundary = D3DXVECTOR3( -1, -1, -1 );
    m_vMaxBoundary = D3DXVECTOR3( 1, 1, 1 );

    m_bResetCursorAfterMove = false;
	
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

//--------------------------------------------------------------------------------------
// Figure out the velocity based on keyboard input & drag if any
//--------------------------------------------------------------------------------------
void EntityCamera::GetInput(bool bGetMouseInput)
{
	/*
    m_vKeyboardDirection = D3DXVECTOR3( 0, 0, 0 );
    if( bGetKeyboardInput )
    {
        // Update acceleration vector based on keyboard state
        if(IsKeyDown( m_aKeys[CAM_MOVE_FORWARD]) )
			
            m_vKeyboardDirection.z += 1.0f;
        if(IsKeyDown( m_aKeys[CAM_MOVE_BACKWARD])) 
            m_vKeyboardDirection.z -= 1.0f;
        if( m_bEnableYAxisMovement )
        {
            if( IsKeyDown( m_aKeys[CAM_MOVE_UP] ) )
                m_vKeyboardDirection.y += 1.0f;
            if( IsKeyDown( m_aKeys[CAM_MOVE_DOWN] ) )
                m_vKeyboardDirection.y -= 1.0f;		    
        }
        if(IsKeyDown( m_aKeys[CAM_STRAFE_RIGHT]) ) 
            m_vKeyboardDirection.x += 1.0f;
        if(IsKeyDown( m_aKeys[CAM_STRAFE_LEFT] )) 
            m_vKeyboardDirection.x -= 1.0f;
    }
	*/
	
    if( bGetMouseInput )
    {
     //   UpdateMouseDelta();
    }
	
}

//--------------------------------------------------------------------------------------
// Figure out the mouse delta based on mouse movement
//--------------------------------------------------------------------------------------

void EntityCamera::UpdateMouseDelta(POINT CurMousePos)
{	
    POINT ptCurMouseDelta;
    POINT ptCurMousePos;

    // Get current position of mouse
	ptCurMousePos = CurMousePos;


    // Calc how far it's moved since last frame
	ptCurMouseDelta.x = ptCurMousePos.x;
    ptCurMouseDelta.y = ptCurMousePos.y;

    // Record current position for next time
    //m_ptLastMousePosition = ptCurMousePos;

	
  
    // Smooth the relative mouse data over a few frames so it isn't 
    // jerky when moving slowly at low frame rates.
    float fPercentOfNew = 1.0f / m_fFramesToSmoothMouseData;
    float fPercentOfOld = 1.0f - fPercentOfNew;
    m_vMouseDelta.x = m_vMouseDelta.x * fPercentOfOld + ptCurMouseDelta.x * fPercentOfNew;
    m_vMouseDelta.y = m_vMouseDelta.y * fPercentOfOld + ptCurMouseDelta.y * fPercentOfNew;

    m_vRotVelocity = m_vMouseDelta * m_fRotationScaler;

}


//--------------------------------------------------------------------------------------
// Figure out the velocity based on keyboard input & drag if any
//--------------------------------------------------------------------------------------


void EntityCamera::UpdateVelocity( )
{
    D3DXMATRIX mRotDelta;
   
    m_vRotVelocity = m_vMouseDelta * m_fRotationScaler ;

   // D3DXVECTOR3 vAccel = m_vKeyboardDirection;

    // Normalize vector so if moving 2 dirs (left & forward), 
    // the camera doesn't move faster than if moving in 1 dir
    //D3DXVec3Normalize( &vAccel, &vAccel );

    // Scale the acceleration vector
    //vAccel *= m_fMoveScaler;
	/*
    if( m_bMovementDrag )
    {
        // Is there any acceleration this frame?
        if( D3DXVec3LengthSq( &vAccel ) > 0 )
        {
            // If so, then this means the user has pressed a movement key\
            // so change the velocity immediately to acceleration 
            // upon keyboard input.  This isn't normal physics
            // but it will give a quick response to keyboard input
            m_vVelocity = vAccel;
            m_fDragTimer = m_fTotalDragTimeToZero;
            m_vVelocityDrag = vAccel / m_fDragTimer;
        }
        else
        {
            // If no key being pressed, then slowly decrease velocity to 0
            if( m_fDragTimer > 0 )
            {
                // Drag until timer is <= 0
                m_vVelocity -= m_vVelocityDrag * fElapsedTime;
                m_fDragTimer -= fElapsedTime;
            }
            else
            {
                // Zero velocity
                m_vVelocity = D3DXVECTOR3( 0, 0, 0 );
            }
        }
    }
    else
    {
        // No drag, so immediately change the velocity
        m_vVelocity = vAccel;
    }*/
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
	
    //if( DXUTGetGlobalTimer()->IsStopped() ) {
    //    if (DXUTGetFPS() == 0.0f) fElapsedTime = 0;
    //    else fElapsedTime = 1.0f / DXUTGetFPS();
    //}

    //if( IsKeyDown( m_aKeys[CAM_RESET] ) )
    //    Reset();
	
    // Get keyboard/mouse/gamepad input
    //GetInput( );
	UpdateMouseDelta(CurMousePos);

    //// Get the mouse movement (if any) if the mouse button are down
    //if( (m_nActiveButtonMask & m_nCurrentButtonMask) || m_bRotateWithoutButtonDown )
    //    UpdateMouseDelta( fElapsedTime );

    // Get amount of velocity based on the keyboard input and drag (if any)
      UpdateVelocity();

    // Simple euler method to calculate position delta
	 D3DXVECTOR3 vPosDelta = D3DXVECTOR3(0,0,0) ;
	
    // If rotating the camera 
    if( MouseButtonPressed)
    {
        // Update the pitch & yaw angle based on mouse movement
        float fYawDelta = m_vRotVelocity.x;
        float fPitchDelta = m_vRotVelocity.y;
	
        // Invert pitch if requested
        if( m_bInvertPitch )
            fPitchDelta = -fPitchDelta;
	
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

    // Transform the position delta by the camera's rotation 
    D3DXVECTOR3 vPosDeltaWorld;
    if( !m_bEnableYAxisMovement )
    {
        // If restricting Y movement, do not include pitch
        // when transforming position delta vector.
        D3DXMatrixRotationYawPitchRoll( &mCameraRot, m_fCameraYawAngle, 0.0f, 0.0f );
    }
    D3DXVec3TransformCoord( &vPosDeltaWorld, &vPosDelta, &mCameraRot );
    // Move the eye position 
    m_vEye += vPosDeltaWorld;
    if( m_bClipToBoundary )
        ConstrainToBoundary( &m_vEye );

    // Update the lookAt position based on the eye position 
    m_vLookAt = m_vEye + vWorldAhead;

    // Update the view matrix
    D3DXMatrixLookAtLH( &m_mView, &m_vEye, &m_vLookAt, &vWorldUp );

    D3DXMatrixInverse( &m_mCameraWorld, NULL, &m_mView );
}



